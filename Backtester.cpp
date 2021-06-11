#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "Estimator.h"
#include "csv.h"
#include "Backtester.h"

using namespace std;


double string_to_double( const std::string& s );
void get_whole_return_matrix_from_csv();



vector < vector<double> > BackTest::sliceReturns(int index1, int index2){
    int window = index2-index1;
    vector< vector<double> > slicedMatrix(numberAssets, vector<double>(window));
    for(int i=0; i<numberAssets;i++){
        for(int j=0; j<window;j++){
            int index1_forward = j+index1;
        slicedMatrix[i][j] = returnMatrix[i][index1_forward];

        }
    }
    return slicedMatrix;
}


vector <vector<double> > BackTest::run(int inSampleWindow, int outOfSampleWindow, vector<double> targets){
    int inSampleStart = 0;
    int maxIter = 600, startIter = 0; // 600 because 100 days are training days -> 700-100 = 600
    vector <vector<double> > outOfSamplePortfolioReturns(targets.size(), vector<double>(maxIter));
    while(startIter < maxIter){
        int inSampleEnd = inSampleStart + inSampleWindow;
        int outOfSampleStart = inSampleEnd + 1 ;
        int outOfSampleEnd = outOfSampleStart + outOfSampleWindow;
        vector <vector<double> > inSampleReturns = sliceReturns(inSampleStart, inSampleEnd);
        vector <vector<double> > portfolioWeights = fit(inSampleReturns, targets);
        vector <vector<double> > outOfSampleReturns = sliceReturns(outOfSampleStart, outOfSampleEnd);
        eval(outOfSamplePortfolioReturns,portfolioWeights,
                outOfSampleReturns,targets, outOfSampleStart);

        startIter += outOfSampleWindow; // 50 Iterations -> 12 *50
        int inSampleStart = inSampleStart + outOfSampleWindow;

    }
    return outOfSamplePortfolioReturns;

}

vector <vector<double> > BackTest::fit(vector < vector<double> > returnMatrix,
                               vector<double> targets){
    MeanVariance estimator;
    estimator.setReturnMatrix(returnMatrix);
    ConjugateGradientOptimizer optimizer;
    optimizer.setEstimator(estimator);
    vector<vector<double> > weightOfWeights(targets.size(), vector<double>(numberAssets));
    for(int i = 0; i <targets.size();i++){
        vector<double> weights =  optimizer.getWeights(targets[i]);
        for(int j = 0; j < weights.size();j++){
        double weight = weights[j];
        weightOfWeights[i][j] = weight;
        }
    }
    return weightOfWeights;

}

void BackTest::eval(
        vector < vector<double> > &outOfSamplePortfolioReturns,
        vector < vector<double> > weightOfWeights,
        vector < vector<double> > returnMatrix,
        vector<double> targets,
        int outOfSampleStart){
    for(int i = 0; i <targets.size();i++){
            for (int j=0; j<returnMatrix[i].size();j++){
                outOfSamplePortfolioReturns[i][j+outOfSampleStart] +=  returnMatrix[i][j] * weightOfWeights[i][j];
            }
        }
    }



vector < vector<double> > BackTest::get_return_matrix_from_csv() {
    vector < vector<double> > Matrix(numberAssets, vector<double>(numberReturns));
    char tmp[20];
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;
    if (file.is_open()) {
        char tmp[20];
        ifstream file(strcpy(tmp, fileName.c_str()));
        Csv csv(file);
        string line;
        if (file.is_open()) {
            int i = 0;
            while (csv.getline(line) != 0) {
                for (int j = 0; j < csv.getnfield(); j++) {
                    double temp = string_to_double(csv.getfield(j));
                    Matrix[j][i] = temp;
                }
                i++;
            }
            file.close();
        } else {
            cout << fileName << " missing\n";
            exit(0);
        }
    }
    return Matrix;
}

double string_to_double( const std::string& s ){
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}