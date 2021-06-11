#include "Estimator.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double MeanVariance::getMean(vector<double> ri) {
    double sum = 0;
    int n = ri.size();
    for (int k=0; k< n; k++){
        sum += ri[k];
    }
    return sum/n;
}

double MeanVariance::getCovariance(vector<double> ri,
                                   double riMean,
                                   vector<double> rj,
                                   double rjMean) {
    double sum = 0;
    int n = ri.size();
    for (int k=0; k < n; k++){
        sum += (ri[k]-riMean)*(rj[k]-rjMean);
    }
    return sum/(n-1);
}

vector<double> MeanVariance::getMeanVector() {
    setColumns();
    setRows();
    vector<double> meanVector;
    for (int i =0; i<columns;i++){
        meanVector.push_back(getMean(returnMatrix[i]));
    }

    return meanVector;
}

vector<vector<double> > MeanVariance::getCovarianceMatrix() {
    setColumns();
    setRows();
    vector<vector<double> > covarianceMatrix(columns, vector<double>(columns));
    for (int i = 0; i<columns;i++){
        double riMean = getMean(returnMatrix[i]);
    for (int j = 0; j<columns;j++){
        double rjMean = getMean(returnMatrix[j]);
        covarianceMatrix[i][j] = getCovariance(returnMatrix[i],riMean,
                                               returnMatrix[j],rjMean);}
    }

    return covarianceMatrix;
}