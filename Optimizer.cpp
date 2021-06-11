#include "Estimator.h"
#include "Optimizer.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using namespace std;

vector<double> MatVecMultiply(
        vector<vector<double> >  Matrix,
        vector<double> Vector);


vector<double> ConjugateGradientOptimizer::makeX(){
    double nAssets = 83;
    vector <double> x(nAssets,0.0);
    double init_weights = 1/nAssets;
    for(int i=0;i < nAssets;i++){
        x[i] = init_weights;
}
    x.push_back(0);
    x.push_back(0);
    return x;
}

vector<double> ConjugateGradientOptimizer::makeB(double target){
    double nAssets = 83;
    vector <double> b(nAssets,0.0);
    b.push_back(-target);
    b.push_back(-1);
    return b;
}
vector<vector<double> > ConjugateGradientOptimizer::makeQ(){
    double N = 83;
    vector<vector<double> > cov = estimator.getCovarianceMatrix();

    vector<double> meanVec = estimator.getMeanVector(), negativeMeanVec(N,0.0), negativeOnes(N,0.0);

    for(int i=0;i<N ;i++){
        negativeMeanVec[i] -=  meanVec[i];
        negativeOnes[i] -=  1;
    }
    cov.push_back(negativeMeanVec);
    cov.push_back(negativeOnes);

    for(int i=0;i<N ;i++){
        double tempVar1 =  0 - meanVec[i];
        double tempVar2 =  0 - 1;
        cov[i].push_back(tempVar1);
        cov[i].push_back(tempVar2);
    }

    cov[N].push_back(0);
    cov[N].push_back(0);
    cov[N+1].push_back(0);
    cov[N+1].push_back(0);
    return cov;
}


vector<double>  ConjugateGradientOptimizer::solveX(
        vector<vector<double> > Q, vector<double> b, vector<double> x) {
    int k =0 ,N = b.size();
    double epsilon = 0.000001 , sTs = 0;
    vector<double> s(N,0.0);
    vector<double> p(N,0.0);
    vector<double> Qx0 = MatVecMultiply(Q,x);
    for(int i=0;i<N;i++){
        p[i] = b[i] - Qx0[i];
        s[i] = b[i] - Qx0[i];
}
    for(int i=0;i<N;i++){
        double s_exp2 = s[i]* s[i];
        sTs += s_exp2;

    }
    while(sTs < epsilon ){
    double sTs = 0.0, pTkQpK = 0.0, skTsk = 0.0, alpha = 0.0, beta = 0.0;
    vector<double> sk(N,0.0);
        for(int i=0;i<N;i++){
            sTs += s[i]* s[i];
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            pTkQpK += Q[i][j]*p[i]*p[j];
    }
    }
    alpha = sTs / pTkQpK;
        for(int i=0;i<N;i++)
        {
            x[i] += alpha * p[i];
            sk[i] = s[i];
            for(int j=0;j<N;j++){
                sk[i] -= alpha*Q[i][j]*p[j];
        }}
        for (int i=0;i<N;i++){
            skTsk += sk[i]*sk[i];
        }
    beta = skTsk/sTs;
    for(int i=0;i<N;i++)
        {
            p[i] = beta*p[i] + sk[i];
            s[i] = sk[i];
        }
    sTs = skTsk;
    k++;
    if (k>10000) break;
    }
    return x;
}


vector<double> MatVecMultiply(
        vector<vector<double> >  Matrix,
              vector<double> Vector)
{
    vector<double>  res(Vector.size(),0.0);

    for (int i = 0; i < Matrix.size(); i++) {
        for (int j = 0; j < Vector.size(); j++) {
            res[j] += Matrix[i][j] * Vector[j];
        }
    }
    return res;
}

vector<double> ConjugateGradientOptimizer::getWeights(double target){
    vector<double> x0 = makeX();
    vector<double> b = makeB(target);
    vector<vector<double> > Q = makeQ();
    vector<double> x = solveX(Q, b, x0);
    x.pop_back();
    x.pop_back();
    return x;

}