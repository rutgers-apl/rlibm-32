#pragma once
#define SOPLEX_WITH_GMP
#include "soplex.h"
#include "IntervalRange.hpp"
#include <map>

using namespace std;
using namespace soplex;

struct MapData {
    double origLb;
    double origUb;
    double lb;
    double ub;
};

class Poly {
    public :
    int termSize;
    double xlb;
    double xub;
    int lowIndex;
    int highIndex;
    
    FILE* log;
    
    vector<int> power;
    vector<double> coeffs;
    
    Poly(int, vector<int>&, FILE*);
    void PrintPolyInfo();
};

class PolyFinder {
    private :
    vector<unique_ptr<Poly>> piecewise;
    
    public :
    
    FILE* log;
    
    PolyFinder(FILE*);
    
    unique_ptr<Poly> SolveForOnePoint(std::map<double, MapData>&);
    unique_ptr<Poly> LinearSolve(std::map<double, MapData>&,
                                 vector<int>&, int);
    bool ValidateAndFixIntervals(std::map<double, MapData>&,
                                 unique_ptr<Poly>&);
    unique_ptr<Poly> SolvePolynomialHelper(std::map<double, MapData>&,
                                     vector<int>&, int);
    unique_ptr<Poly> SolvePolynomial(std::map<double, MapData>&,
                                     vector<int>&, int&);
    
    double PolyEval(double);
    double PolyEval(double, unique_ptr<Poly>&);
    
    void PrintPiecewiseInfo();
};





