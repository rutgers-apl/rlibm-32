#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    mpfr_set_d(mval, x.toDouble(), MPFR_RNDN);
    mpfr_log10(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator::ComputeSpecialCase(posit32 x, posit32& res) {
    if (x.value == 0) {
        res.value = 0x80000000;
        return true;
    } else if (x.value >= 0x80000000) {
        res.value = 0x80000000;
        return true;
    } else if (x.value == 0x40000000) {
        res.value = 0.0;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(double x) {
    doubleX fix, fit;
    
    fix.d = x;
    
    int m = fix.x >> 52lu;
    m -= 1023lu;
    fix.x &= 0xFFFFFFFFFFFFFlu;
    fix.x |= 0x3FF0000000000000lu;
    
    fit.x = fix.x & 0xFE00000000000lu;
    int FIndex = fit.x >> 45lu;
    fit.x |= 0x3FF0000000000000lu;
    double F = fit.d;
    double f = fix.d - F;
    
    return f * log2OneByF[FIndex];
}
    
double IntervalGenerator::OutputCompensation(double x, double yp) {
    doubleX fix, fit;
    
    fix.d = x;
    
    int m = fix.x >> 52lu;
    m -= 1023lu;
    fix.x &= 0xFFFFFFFFFFFFFlu;
    fix.x |= 0x3FF0000000000000lu;
    
    fit.x = fix.x & 0xFE00000000000lu;
    int FIndex = fit.x >> 45lu;
    fit.x |= 0x3FF0000000000000lu;
    double F = fit.d;
    double f = fix.d - F;
    //printf("lut[88] = %.100e\n", lut[88]);
    
    return yp + m * LOG102LOW + log10Lut[FIndex] + m * LOG102HIGH;
}

void IntervalGenerator::GuessInitialLbUb(double x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    doubleX tempYp;
    tempYp.d = log1p(xp) / log(10);
    //printf("tempYp     : %.100e\n", tempYp.d);
    double tempY = OutputCompensation(x, tempYp.d);
    //printf("tempY      : %.100e\n", tempY);
    
    if (tempY < roundingLb) {
        // if tempY < roundingLb, then keep increasing tempYp until tempY is
        // >= roundingLb.
        do {
            tempYp.x++;
            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY < roundingLb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY > roundingUb) {
            
            printf("Error during GuessInitialLbUb 1: lb > ub.\n");
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
            tempYp.x--;
            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY > roundingUb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY < roundingLb) {
            printf("Error during GuessInitialLbUb 2: lb > ub.\n");
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

void IntervalGenerator::SpecCaseRedInt(double x,
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
    
    IntervalGenerator Log2IntGen;
    Log2IntGen.CreateReducedIntervalFile(argv[1]);
    
    mpfr_clear(mval);
    return 0;
}
