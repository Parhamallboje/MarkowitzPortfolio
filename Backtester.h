#ifndef Backtester_h
#define Backtester_h

#include "Estimator.h"
#include "Optimizer.h"
#include <vector>

using namespace std;

class BackTest
        {
public:
    vector < vector<double> > returnMatrix;

    BackTest(int n_assets_, int n_returns_, string filename_){
        numberAssets = n_assets_;
        numberReturns = n_returns_;
        fileName = filename_;
        returnMatrix = get_return_matrix_from_csv();
    }
    int numberAssets, numberReturns;
    string fileName;

    void setNAssets(int numberAssets_){
        numberAssets = numberAssets_;
    }
    void setNReturns(int numberReturns_){
        numberReturns = numberReturns_;
    }
    void setFileName(string fileName_){
        fileName = fileName_;
    }
    vector < vector<double> > sliceReturns(int index1, int index2);

    vector <vector<double> > fit(vector < vector<double> > returnMatrix, vector<double> targets);

    vector <vector<double> >  run(int inSampleWindow, int outOfSampleWindow, vector<double> targets);

    void eval(
            vector < vector<double> > &outOfSamplePortfolioReturns,
            vector < vector<double> > weightOfWeights,
            vector < vector<double> > returnMatrix,
            vector<double> targets,
            int outOfSampleStart);

    vector < vector<double> > get_return_matrix_from_csv();


};

#endif
