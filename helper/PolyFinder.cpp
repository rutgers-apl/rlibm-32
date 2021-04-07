#include "PolyFinder.hpp"

Poly::Poly(int _termSize, std::vector<int>& _power) {
    termSize = _termSize;
    power = _power;
}

void Poly::PrintPolyInfo() {
    printf("For inputs in the range of: \n");
    printf("%.20lf ~ %.20lf\n", xlb, xub);

    if (termSize == 0) {
        printf("How can a polynomial have no terms?\n");
        exit(0);
    }
    
    printf("\ty = %.70e x^(%d)\n", coeffs[0], power[0]);
    for (int j = 1; j < termSize; j++) {
        printf("\t  + %.70e x^(%d)\n", coeffs[j], power[j]);
    }
    printf("\n");
}

/*############################################################################
 PolyFinder
 #############################################################################*/

PolyFinder::PolyFinder(shared_ptr<IntervalRange>& _intervalInfo) {
    intervalInfo = _intervalInfo;
    li = 0;
    ui = intervalInfo->intervals.size() - 1;
}

// If I have a single point left to create a polynomial for, just use a single
// value constant function.
unique_ptr<Poly> PolyFinder::SolveForOnePoint(int index) {
    vector<int> power = {0};
    unique_ptr<Poly> onePiece = make_unique<Poly>(1, power);
    onePiece->xlb = intervalInfo->intervals[index]->xtrans;
    onePiece->xub = intervalInfo->intervals[index]->xtrans;
    onePiece->lowIndex = index;
    onePiece->highIndex = index;
    
    double average = intervalInfo->intervals[index]->lb;
    average += intervalInfo->intervals[index]->ub;
    average /= 2.0;
    onePiece->coeffs.push_back(average);
    
    return onePiece;
}

// Given a list of interval already in intervalInfo, attempt to create a
// polynomial with terms "power" that fits the interval from interval[lb] ~
// interval[ub].
// If successful, returns a pointer to Poly. If unsuccessful, returns NULL.
unique_ptr<Poly> PolyFinder::LinearSolve(int lb, int ub, vector<int>& power) {
    printf("[%d, %d]\r", lb, ub);
    fflush(stdout);
    
    if (lb == ub) return SolveForOnePoint(lb);
    
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
    mysoplex.setIntParam(SoPlex::VERBOSITY, 0);
    
    int termSize = power.size();
    
    /* we first add objective variables */
    DSVectorRational dummycol(0);
    for (int i = 0; i < termSize; i++) {
        auto column = LPColRational(1.0, dummycol, infinity, -infinity);
        mysoplex.addColRational(column);
    }
    
    /* then add constraints one by one */
    for (int i = lb; i <= ub; i++) {
        Rational xValR(intervalInfo->intervals[i]->xtrans);
        DSVectorRational row1(termSize);
        
        for (int j = 0; j < termSize; j++) {
            Rational toAdd(1.0);
            for (int k = 0; k < power[j]; k++) toAdd *= xValR;
            row1.add(j, toAdd);
        }
        
        // LPRow: low bound, row, upper bound
        double lbnd = intervalInfo->intervals[i]->lb;
        double ubnd = intervalInfo->intervals[i]->ub;
        mysoplex.addRowRational(LPRowRational(lbnd, row1, ubnd));
    }
    
    mysoplex.writeFileReal("dump.lp", NULL, NULL, NULL);
    
    /* solve LP */
    SPxSolver::Status stat;
    stat = mysoplex.optimize();

    /* get solution */
    if(stat == SPxSolver::OPTIMAL)
    {
        DVectorRational prim(termSize);
        mysoplex.getPrimalRational(prim);
        
        unique_ptr<Poly> onePiece = make_unique<Poly>(termSize, power);
        onePiece->xlb = intervalInfo->intervals[lb]->xtrans;
        onePiece->xub = intervalInfo->intervals[ub]->xtrans;
        onePiece->lowIndex = lb;
        onePiece->highIndex = ub;
        
        for (int i = 0; i < termSize; i++) {
            onePiece->coeffs.push_back(mpq_get_d(*(prim[i].getMpqPtr_w())));
        }
        return onePiece;
    }
    
    return unique_ptr<Poly>();
}

// Given a "Poly" object, validate that the polynomial produces a value in the
// correct range with double computation. If it does not produce a value in the
// interval correctly, then we reduce the interval.
bool PolyFinder::ValidateAndFixIntervals(unique_ptr<Poly>& onePiece) {
    bool returnVal = true;
    for (int i = onePiece->lowIndex; i <= onePiece->highIndex; i++) {
        double y = PolyEval(intervalInfo->intervals[i]->xtrans, onePiece);
        if (y < intervalInfo->intervals[i]->origLb) {
            returnVal = false;
            doubleX lbX;
            lbX.d = intervalInfo->intervals[i]->lb;
            if (lbX.d >= 0) lbX.x++;
            else lbX.x--;
            intervalInfo->intervals[i]->lb = lbX.d;
        } else if (y > intervalInfo->intervals[i]->origUb) {
            returnVal = false;
            doubleX ubX;
            ubX.d = intervalInfo->intervals[i]->ub;
            if (ubX.d >= 0) ubX.x--;
            else ubX.x++;
            intervalInfo->intervals[i]->ub = ubX.d;
        }
    }
    return returnVal;
}

// The helper works like a binary search algorithm.
// We try to create a polynomial from lowIndex~maxIndex.
// If we do not succeed, then we try lowIndex ~ (lowIndex + maxIndex)/2
// And we keep going.
// si, mi = variables that keep track of the startIndex and maxIndex of the
// intervals that we need to solve for. This is absolute minimum/maximum and
// does not change.
// low, high = we use low and high as the lower bound and upper bound in
// computing the next interval to use when doing binary search.
// mid : we are going to try to solve for intervals [si, mid].
unique_ptr<Poly>
PolyFinder::RetrieveOnePolynomialHelper(int si, int mi,
                                        int low, int mid, int high,
                                        vector<int>& power) {
    // First, try solving si ~ mid
    unique_ptr<Poly> onePiece = LinearSolve(si, mid, power);
    if (onePiece) {
        // If we can solve it, compute the nextIndex
        int nextMid = (mid + high) / 2;
        // if nextMid == mid, then we have the best solution
        if (nextMid == mid) return onePiece;
        // Otherwise,  see if we can get include more intervals
        unique_ptr<Poly> maybeBetterPiece =
        RetrieveOnePolynomialHelper(si, mi, mid, nextMid, high, power);
        // If we get something not null, then it's a better solution
        if (maybeBetterPiece) return maybeBetterPiece;
        return onePiece;
    }
    
    // If we can't solve it, then try si ~ (low + mid) / 2
    int nextMid = (low + mid) / 2;
    return RetrieveOnePolynomialHelper(si, mi, low, nextMid, mid, power);
}

// Try to find a single polynomial based on polynomial degree in power argument.
// The inputs are in the intervalInfo. Range is from lowIndex to maxIndex. This
// function finds a polynomial of degree specified in power argument.
// If it is impossible to find a polynomial covering [lowIndex, maxIndex], then
// this function finds a polynomial that covers as much as possible starting
// from lowIndex.
unique_ptr<Poly> PolyFinder::RetrieveOnePolynomial(int lowIndex, int maxIndex,
                                                   vector<int>& power) {
    while (true) {
        auto onePiece = RetrieveOnePolynomialHelper(lowIndex, maxIndex, lowIndex,
                                                    maxIndex, maxIndex, power);
        // If we can't find one, then return Null;
        if (!onePiece) return unique_ptr<Poly>();
        
        printf("Found a polynomial for indices [%d, %d]. Validating...\r",
               onePiece->lowIndex, onePiece->highIndex);
        fflush(stdout);

        // Validate that this polynomial does evaluate to the correct output
        if (ValidateAndFixIntervals(onePiece)) {
            printf("Validation complete.\n");
            return onePiece;
        }

        // Otherwise, create polynomial again.
        printf("Validation failed. Intervals narrowed and retrying now.\n");
        maxIndex = onePiece->highIndex;
    }
}

// Finds a piecewise polynomial function of degree specified in the power
// argument. The piecewise polynomial that is returned is guaranteed to cover
// [lowIndex, maxIndex] if the function returns.
vector<unique_ptr<Poly>>
PolyFinder::RetrievePolynomials(int lowIndex, int maxIndex, vector<int>& power) {
    vector<unique_ptr<Poly>> returnVal;
    while (lowIndex <= maxIndex) {
        // Find a polynomial
        auto onePiece = RetrieveOnePolynomial(lowIndex, maxIndex, power);
        // If we can't solve for all points, at least solve for as many as we can.
        // However, logically this should not be happening.
        if (!onePiece) return returnVal;
        // Update the lowIndex.
        lowIndex = onePiece->highIndex + 1;
        returnVal.push_back(move(onePiece));
    }
    
    return returnVal;
}

// Try to find a single polynomial based on polynomial degree in power argument.
// The inputs are in the intervalInfo. Range is from li to ui. li is not
// necessarily 0 and ui is not necessarily intervalInfo.intervals.size() - 1.

// This function finds a polynomial of degree specified in power argument. If it
// is impossible to find a polynomial covering [li, ui], then this function
// finds a polynomial that covers as much as possible starting from lowIndex.
// Finally the found polynomial is added to piecewise.
int PolyFinder::FindPolynomialOnce(vector<int>& power) {
    // If li is > ui, then there are no more intervals to cover.
    if (li > ui) return -1;
    // Otherwise retrieve a single polynomial starting from li.
    auto poly = RetrieveOnePolynomial(li, ui, power);
    if (!poly) return -2;
    // Update li
    li = poly->highIndex + 1;
    piecewise.push_back(move(poly));
    
    return 0;
}

// Finds a piecewise polynomial function of degree specified in the power
// argument. The piecewise polynomial is guaranteed to cover [li, ui] if the
// function returns. Finally the found polynomials are added to piecewise.
int PolyFinder::FindPolynomials(vector<int>& power) {
    // If li is > ui, then there are no more intervals to cover.
    if (li > ui) return -1;
    // Otherwise retrieve polynomials starting from li to ui.
    auto polys = RetrievePolynomials(li, ui, power);
    // Update li
    li = ui + 1;
    for (auto& ii : polys) piecewise.push_back(move(ii));
    return 0;
}

// Finds a piecewise polynomial function of degree specified in the power
// argument. The piecewise polynomial is guaranteed to cover [li, highIndex] if
// the function returns. Finally the found polynomials are added to piecewise.
int PolyFinder::FindPolynomialsUntil(vector<int>& power, int highIndex) {
    // If highIndex > ui, then we just find polynomials until highIndex.
    if (highIndex > ui) highIndex = ui;
    // If li is > highIndex, then there are no more intervals to cover.
    if (li > highIndex) return -1;
    // Otherwise retrieve polynomials starting from li to highIndex.
    auto polys = RetrievePolynomials(li, highIndex, power);
    // Update li
    li = highIndex + 1;
    for (auto& ii : polys) piecewise.push_back(move(ii));
    return 0;
}

// Finds a piecewise polynomial function of degree specified in the power
// argument. The piecewise polynomial is guaranteed to cover [li, highIndex] if
// the function returns. highIndex is the index of intervalInfo where
// xtrans <= val. Finally the found polynomials are added to piecewise.
int PolyFinder::FindPolynomialsUntilBefore(vector<int>& power, double val) {
    // Find highIndex
    int highIndex = 0;
    for (int i = 0; i < intervalInfo->intervals.size(); i++) {
        if (intervalInfo->intervals[i]->xtrans < val) {
            highIndex = i;
        } else break;
    }
    
    // If highIndex > ui, then we just find polynomials until highIndex.
    if (highIndex > ui) highIndex = ui;
    // If li is > highIndex, then there are no more intervals to cover.
    if (li > highIndex) return -1;
    
    // Otherwise retrieve polynomials starting from li to highIndex.
    auto polys = RetrievePolynomials(li, highIndex, power);
    // Update li
    li = highIndex + 1;
    for (auto& ii : polys) piecewise.push_back(move(ii));
    return 0;
}

void PolyFinder::PrintPiecewiseInfo() {
    printf("PIECEWISE POLYNOMIAL\n");
    for (auto const& poly : piecewise) {
        poly->PrintPolyInfo();
        printf("\n");
    }
}

void PolyFinder::ResetPiecewise() {
    piecewise.clear();
    li = 0;
    ui = intervalInfo->intervals.size() - 1;
    
    // When resetting, we should also reset all the lb/ub.
    for (auto const& inter : intervalInfo->intervals) {
        inter->lb = inter->origLb;
        inter->ub = inter->origUb;
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
