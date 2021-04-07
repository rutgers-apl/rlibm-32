#include "IntervalGen/IntGenForFloatOneApprox.h"
#include "luts.h"
#include "math.h"

float IntervalGenerator::MpfrCalculateFunction(float x) {
    
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_log(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator::ComputeSpecialCase(float x, float& res) {
    floatX fx;
    fx.f = x;
    if (x == 0.0) {
        res = -1.0/0.0;
        return true;
    } else if (fx.x == 0x7F800000) {
        res = x;
        return true;
    } else if (fx.x > 0x7F800000) {
        fx.x = 0x7FFFFFFF;
        res = fx.f;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(float x) {
    floatX fix, fit;
    
    int m = 0;
    fix.f = x;
    if (fix.x < 0x800000) {
        fix.f *= pow(2, 23);
        m -= 23;
    }
    m += fix.x >> 23;
    m -= 127;
    fix.x &= 0x007FFFFF;
    fix.x |= 0x3F800000;
    
    fit.x = fix.x & 0x007F0000;
    int FIndex = fit.x >> 16;
    fit.x |= 0x3F800000;
    double F = fit.f;
    
    double f = fix.f - F;
    return f * log2OneByF[FIndex];
}
    
double IntervalGenerator::OutputCompensation(float x, double yp) {
    floatX fix, fit;
    
    int m = 0;
    fix.f = x;
    if (fix.x < 0x800000) {
        fix.f *= pow(2, 23);
        m -= 23;
    }
    m += fix.x >> 23;
    m -= 127;
    fix.x &= 0x007FFFFF;
    fix.x |= 0x3F800000;
    
    fit.x = fix.x & 0x007F0000;
    int FIndex = fit.x >> 16;
    
    return yp + lnLutHIGH[FIndex] + m * LN2HIGH;
}

void IntervalGenerator::GuessInitialLbUb(float x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    doubleX tempYp;
    tempYp.d = log1p(xp);
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
    
    IntervalGenerator LnIntGen;
    LnIntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
