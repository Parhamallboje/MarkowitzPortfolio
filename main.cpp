#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include<vector>
#include "csv.h"
#include "Estimator.h"
#include "Optimizer.h"
#include "Backtester.h"

// g++ -c main.cpp Estimator.cpp Optimizer.cpp csv.cpp Backtester.cpp;
// g++ -o PortfolioSolver main.o Estimator.o Optimizer.o csv.o Backtester.o
// ./PortfolioSolver
int  main ()
{
    int numberAssets=83;
    int numberReturns=700;
    int nPortfolios = 20;
    vector<double> target(nPortfolios,0.005);
    for(int i=1; i <nPortfolios;i++){
        target[i] = target[i-1] + 0.005;
    }
    string fileName="asset_returns.csv";
    BackTest backTest = BackTest(numberAssets,numberReturns,fileName);
    vector <vector<double> > outOfSamplePortfolioReturns = backTest.run(
            100,12, target) ;

	return 0;
}


