#include "PolyGenSampling.hpp"

Poly::Poly(int _termSize, std::vector<int>& _power, FILE* _log) {
    log = _log;
    termSize = _termSize;
    power = _power;
}

void Poly::PrintPolyInfo() {
    if (termSize == 0) {
        fprintf(log, "How can a polynomial have no terms?\n");
        exit(0);
    }
    
    fprintf(log, "Polynomial: \n");
    fprintf(log, "\ty = %.70e x^(%d)\n", coeffs[0], power[0]);
    for (int j = 1; j < termSize; j++) {
        fprintf(log, "\t  + %.70e x^(%d)\n", coeffs[j], power[j]);
    }
    fprintf(log, "\n");
}

/*############################################################################
 PolyFinder
 #############################################################################*/

PolyFinder::PolyFinder(FILE* _log) {
    log = _log;
}

// If I have a single point left to create a polynomial for, just use a single
// value constant function.
unique_ptr<Poly> PolyFinder::SolveForOnePoint(std::map<double, MapData>& intervals) {
    std::map<double, MapData>::iterator it;
    it = intervals.begin();
    
    vector<int> power = {0};
    unique_ptr<Poly> onePiece = make_unique<Poly>(1, power, log);
    
    onePiece->xlb = it->first;
    onePiece->xub = it->first;
    double average = it->second.lb;
    average += it->second.ub;
    average /= 2.0;
    onePiece->coeffs.push_back(average);
        
    return onePiece;
}

// Given a list of interval already in intervalInfo, attempt to create a
// polynomial with terms "power" that fits the interval from interval[lb] ~
// interval[ub].
// If successful, returns a pointer to Poly. If unsuccessful, returns NULL.
unique_ptr<Poly> PolyFinder::LinearSolve(std::map<double, MapData>& intervals,
                                         vector<int>& power,
                                         int termSize) {
    //if (intervals.size() == 1) return SolveForOnePoint(intervals);
    // Settings for soplex.
    SoPlex mysoplex;
    mysoplex.setBoolParam(SoPlex::RATFACJUMP, true);
    mysoplex.setIntParam(SoPlex::SOLVEMODE, 2);
    mysoplex.setIntParam(SoPlex::CHECKMODE, 2);
    mysoplex.setIntParam(SoPlex::SYNCMODE, 1);
    mysoplex.setIntParam(SoPlex::READMODE, 1);
    mysoplex.setRealParam(SoPlex::FEASTOL, 0.0);
    mysoplex.setRealParam(SoPlex::OPTTOL, 0.0);
    mysoplex.setRealParam(SoPlex::EPSILON_ZERO, 0.0);
    mysoplex.setRealParam(SoPlex::EPSILON_FACTORIZATION, 0.0);
    mysoplex.setRealParam(SoPlex::EPSILON_UPDATE, 0.0);
    mysoplex.setRealParam(SoPlex::EPSILON_PIVOT, 0.0);
    //mysoplex.setRealParam(SoPlex::FPFEASTOL, 0.0);
    //mysoplex.setRealParam(SoPlex::FPOPTTOL, 0.0);
    mysoplex.setIntParam(SoPlex::VERBOSITY, 0);
    mysoplex.setRealParam(SoPlex::TIMELIMIT, 5 * 60);
    
    //int termSize = power.size();
    
    while (true) {
        if (termSize == 1) break;
        if (power[termSize - 1] >= intervals.size()) {
            termSize--;
            continue;
        }
        break;
    }
    
    /* we first add objective variables */
    DSVectorRational dummycol(0);
    for (int i = 0; i < termSize; i++) {
        auto column = LPColRational(1.0, dummycol, infinity, -infinity);
        mysoplex.addColRational(column);
    }
    
    /* then add constraints one by one */
    std::map<double, MapData>::iterator it;
    for (it = intervals.begin(); it != intervals.end(); it++) {
        Rational xValR(it->first);
        DSVectorRational row1(termSize);
        
        for (int j = 0; j < termSize; j++) {
            Rational toAdd(1.0);
            for (int k = 0; k < power[j]; k++) toAdd *= xValR;
            row1.add(j, toAdd);
        }
        
        // LPRow: low bound, row, upper bound
        double lbnd = it->second.lb;
        double ubnd = it->second.ub;
        mysoplex.addRowRational(LPRowRational(lbnd, row1, ubnd));
    }
    
    /* solve LP */
    SPxSolver::Status stat;
    stat = mysoplex.optimize();

    /* get solution */
    if(stat == SPxSolver::OPTIMAL)
    {
        DVectorRational prim(termSize);
        mysoplex.getPrimalRational(prim);
        
        unique_ptr<Poly> onePiece = make_unique<Poly>(termSize, power, log);
        
        for (int i = 0; i < termSize; i++) {
            onePiece->coeffs.push_back(mpq_get_d(*(prim[i].getMpqPtr_w())));
        }
        return onePiece;
    } else if (stat == SPxSolver::UNBOUNDED) {
        unique_ptr<Poly> onePiece = make_unique<Poly>(termSize, power, log);
        
        for (int i = 0; i < termSize; i++) {
            onePiece->coeffs.push_back(0.0);
        }
        return onePiece;
    }
    
    return unique_ptr<Poly>();
}

bool PolyFinder::ValidateAndFixIntervals(std::map<double, MapData>& intervals,
                                         unique_ptr<Poly>& onePiece) {
    bool returnVal = true;
    std::map<double, MapData>::iterator it;
    
    for (it = intervals.begin(); it != intervals.end(); it++) {
        double y = PolyEval(it->first, onePiece);
        if (y < it->second.origLb) {
            returnVal = false;
            doubleX lbX;
            lbX.d = it->second.lb;
            if (lbX.d >= 0) lbX.x += 1;
            else lbX.x -= 1;
            it->second.lb = lbX.d;
        } else if (y > it->second.origUb) {
            returnVal = false;
            doubleX ubX;
            ubX.d = it->second.ub;
            if (ubX.d >= 0) ubX.x -= 1;
            else ubX.x += 1;
            it->second.ub = ubX.d;
        }
    }
    
    return returnVal;
}

unique_ptr<Poly> PolyFinder::SolvePolynomialHelper(std::map<double, MapData>& intervals,
                                             vector<int>& power, int termSize) {
    while (true) {
      fflush(log);
        auto onePiece = LinearSolve(intervals, power, termSize);
        // If we can't find one, then return Null;
        if (!onePiece) return unique_ptr<Poly>();

        // Validate that this polynomial does evaluate to the correct output
        if (ValidateAndFixIntervals(intervals, onePiece)) {
            return onePiece;
        }

        // Otherwise, create polynomial again.
        fprintf(log, "Validation failed. Intervals narrowed and retrying now.\n");
    }
}

unique_ptr<Poly> PolyFinder::SolvePolynomial(std::map<double, MapData>& intervals,
                                             vector<int>& power, int& lastTried) {
    auto onePiece = SolvePolynomialHelper(intervals, power, lastTried);
    if (onePiece) {
        return onePiece;
    }
    return unique_ptr<Poly>();
}

void PolyFinder::PrintPiecewiseInfo() {
    fprintf(log, "PIECEWISE POLYNOMIAL\n");
    for (auto const& poly : piecewise) {
        poly->PrintPolyInfo();
        fprintf(log, "\n");
    }
}

// Evaluate polynomial stored in piecewise with the input x.
double PolyFinder::PolyEval(double x) {
    for (int p = 0; p < piecewise.size(); p++) {
        auto& poly = piecewise[p];
        
        // If the piecewise polynomial is in the range.
        double pub = (p < piecewise.size() - 1) ? piecewise[p+1]->xlb : 1.0/0.0;
        if (poly->xlb <= x && x < pub) return PolyEval(x, poly);
    }
    return NAN;
}

// Evaluate polynomial of "poly" using the input x.
double PolyFinder::PolyEval(double x, unique_ptr<Poly>& poly) {
    double retVal = 0;
    
    // Simulate Horner's method.
    for (int i = poly->termSize - 1; i > 0; i--) {
        retVal += poly->coeffs[i];
        double xmul = 1;
        for (int j = 0; j < poly->power[i] - poly->power[i-1]; j++) xmul *= x;
        retVal *= xmul;
    }
    
    retVal += poly->coeffs[0];
    for (int j = 0; j < poly->power[0]; j++) retVal *= x;
    
    return retVal;
}
