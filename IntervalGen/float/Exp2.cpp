#include "IntervalGen/IntGenForFloatOneApprox.h"
#include "luts.h"
#include "math.h"

float IntervalGenerator::MpfrCalculateFunction(float x) {
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_exp2(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator::ComputeSpecialCase(float x, float& res) {
    floatX fx;
    fx.f = x;
    
    // If x =< -150, then 2^x rounds to 0
    if (fx.f <= -150) {
        res = 0.0;
        return true;
    }
    
    // If x is between these values, 2^x rounds to 1.0
    if (-4.2995662141720458748750388622283935546875e-08 <= fx.f &&
        fx.f <= 8.59913171780135598964989185333251953125e-08) {
        res = 1.0;
        return true;
    }
    
    // If x >= 128, then 2^x rounds to infinity
    if (128 <= fx.f) {
        res = 1.0/0.0;
        return true;
    }
    
    // NaN ressults in NaN
    if ((fx.x & 0x7FFFFFFF) > 0x7F800000) {
        res = 0.0/0.0;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(float x) {
    double xp = x * 64;
    int N = (int)xp;
    return x - N * 0.015625;
}
    
double IntervalGenerator::OutputCompensation(float x, double yp) {
    double xp = x * 64;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int M = N1 / 64;
    
    return yp * ldexp(exp2JBy64[N2], M);
}

void IntervalGenerator::GuessInitialLbUb(float x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    doubleX tempYp;
    tempYp.d = exp2(xp);
    double tempY = OutputCompensation(x, tempYp.d);
    
    if (tempY < roundingLb) {
        // if tempY < roundingLb, then keep increasing tempYp until tempY is
        // >= roundingLb.
        do {
            if (tempYp.d >= 0) tempYp.x++;
            else tempYp.x--;

            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY < roundingLb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY > roundingUb) {
            printf("Error during GuessInitialLbUb: lb > ub.\n");
            printf("x = %.100e\n", x);
            exit(0);
        }
        lb = tempYp.d;
        ub = tempYp.d;
        return;
    }
    
    if (tempY > roundingUb) {
        // if tempY > roundingUb, then keep decreasing tempYp until tempY is
        // <= roundingUb.
        do {
            if (tempYp.d >= 0) tempYp.x--;
            else tempYp.x++;

            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY > roundingUb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY < roundingLb) {
            printf("Error during GuessInitialLbUb: lb > ub.\n");
            printf("x = %.100e\n", x);
            exit(0);
        }
        lb = tempYp.d;
        ub = tempYp.d;
        return;
    }
    
    lb = tempYp.d;
    ub = tempYp.d;
    return;
}

void IntervalGenerator::SpecCaseRedInt(float x,
                                       double glb, bool& blb, double& slb,
                                       double gub, bool& bub, double& sub) {
    blb = false;
    bub = false;
    return;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 200);
    
    if (argc != 2) {
        printf("Usage: %s <Name of File>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator Exp2IntGen;
    Exp2IntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
