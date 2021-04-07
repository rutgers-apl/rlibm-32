#pragma once
#define SOPLEX_WITH_GMP
#include "IntervalRange.hpp"
#include "soplex.h"

using namespace std;
using namespace soplex;

class Poly {
    public :
    int termSize;
    double xlb;
    double xub;
    int lowIndex;
    int highIndex;
    
    // TODO: Vector of pairs: for power and coeffs
    vector<int> power;
    vector<double> coeffs;
    
    Poly(int, vector<int>&);
    void PrintPolyInfo();
};

class PolyFinder {
    private :
    vector<unique_ptr<Poly>> piecewise;
    int li;
    int ui;
    
    unique_ptr<Poly> SolveForOnePoint(int);
    unique_ptr<Poly> LinearSolve(int, int, vector<int>&);
    bool ValidateAndFixIntervals(unique_ptr<Poly>&);
    
    unique_ptr<Poly> RetrieveOnePolynomialHelper(int, int, int, int, int,
                                                 vector<int>&);
    unique_ptr<Poly> RetrieveOnePolynomial(int, int, vector<int>&);
    vector<unique_ptr<Poly>> RetrievePolynomials(int, int, vector<int>&);
    
    public :
    shared_ptr<IntervalRange> intervalInfo;
    PolyFinder(shared_ptr<IntervalRange>&);
    
    void ResetPiecewise();
        
    int FindPolynomialOnce(vector<int>&);
    int FindPolynomials(vector<int>&);
    int FindPolynomialsUntil(vector<int>&, int);
    int FindPolynomialsUntilBefore(vector<int>&, double);
    
    double PolyEval(double);
    double PolyEval(double, unique_ptr<Poly>&);
    
    void PrintPiecewiseInfo();
};





