#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

#ifdef __APPLE__
#define exp10fFunc __exp10f
#else
#define exp10fFunc exp10f
#endif

#ifdef __APPLE__
#define exp10Func __exp10
#else
#define exp10Func exp10
#endif

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    // exp10: result should never be 0. result should never be infinity.
    // if mpfr result is 0, then result should be minpos
    // if mpfr result is inf, then result should be maxpos
    mpfr_set_d(mval, x.toDouble(), MPFR_RNDN);
    mpfr_exp10(mval, mval, MPFR_RNDN);
    posit32 retVal = FromMPFR(mval);
    if (retVal.value == 0) {
        retVal.value = 0x00000001;
        return retVal;
    }
    
    if (x.value == 0x80000000) {
        retVal.value = 0x80000000;
        return retVal;
    }
    
    if (retVal.value == 0x80000000) {
        retVal.value = 0x7FFFFFFF;
        return retVal;
    }
    
    return retVal;
}

bool IntervalGenerator::ComputeSpecialCase(posit32 x, posit32& res) {
    // If x =< -150, then 2^x rounds to minpos
    if (x.value <= 2609860492 && x.value > 0x80000000) {
        res.value = 0x00000001;
        return true;
    }
    
    // If x is between these values, 2^x rounds to 1.0
    if (x.value >= 4288951429 || x.value <= 7064443) {
        res.value = 0x40000000;
        return true;
    }
    
    // If x >= 128, then 2^x rounds to infinity
    if (x.value >= 1685106804 && x.value < 0x80000000) {
        res.value = 0x7FFFFFFF;
        return true;
    }
    
    // NaN ressults in NaN
    if (x.value == 0x80000000) {
        res.value = 0x80000000;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(double x) {
    double xp = x * 2.12603398072791179629348334856331348419189453125e+02;
    int N = (int)xp;
    
    return x - N *
    4.703593682249706219022922226713490090332925319671630859375e-03;
}
    
double IntervalGenerator::OutputCompensation(double x, double yp) {
    double xp = x * 2.12603398072791179629348334856331348419189453125e+02;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int M = N1 / 64;
    
    return yp * ldexp(exp2JBy64[N2], M);
}

void IntervalGenerator::GuessInitialLbUb(double x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    doubleX tempYp;
    tempYp.d = exp10Func(xp);
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
    
    IntervalGenerator Exp10IntGen;
    Exp10IntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
