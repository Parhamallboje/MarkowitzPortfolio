#ifndef Optimizer_h
#define Optimizer_h

#include "Estimator.h"
#include <vector>

using namespace std;

class Optimizer{
public:
    Estimator estimator;
    void setEstimator(Estimator estimator_){
        estimator = estimator_;
    }
};

class MeanVarianceOptimizer{
public:
    MeanVariance estimator;
    void setEstimator(MeanVariance estimator_){
        estimator = estimator_;
    }
};

class ConjugateGradientOptimizer: public MeanVarianceOptimizer{
public:
    vector<double> solveX(
            vector<vector<double> > Q, vector<double> b, vector<double> x);
    vector<double> makeX();
    vector<double> makeB(double target);
    vector<vector<double> > makeQ();
    vector<double> getWeights(double target);

};
#endif
