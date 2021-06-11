#ifndef Estimator_h
#define Estimator_h

#include<vector>
using namespace std;

class Estimator
{
public:
    int rows, columns;
    vector <vector<double> > returnMatrix;
    void setReturnMatrix(vector < vector<double> > returnMatrix_){
        returnMatrix = returnMatrix_;
    };
    void setRows(){rows = returnMatrix[0].size();}
    void setColumns(){columns = returnMatrix.size();}
};

class MeanVariance: public Estimator
{
public:
    double getMean(vector<double> ri);
    double getCovariance(vector<double> ri, double riMean, vector<double> rj, double rjMean);
    vector<double> getMeanVector();
    vector<vector<double> > getCovarianceMatrix();

};

#endif
