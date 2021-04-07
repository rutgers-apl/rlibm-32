#include "IntervalGen/IntGenForFloatOneApprox.h"
#include "luts.h"
#include "math.h"

float IntervalGenerator::MpfrCalculateFunction(float x) {
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_exp(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator::ComputeSpecialCase(float x, float& res) {
    floatX fx;
    fx.f = x;
    
    // If x is less than this value, e^x rounds to 0
    if (fx.f <= -103.97283935546875) {
        res = 0.0;
        return true;
    }
    
    // If x is between these values, e^x rounds to 1
    if (-2.98023223876953125e-08 <= fx.f &&
        fx.f <= 5.9604641222676946199499070644378662109375e-08) {
        res = 1.0;
        return true;
    }
    
    // If x is greater than this value, e^x rounds to infinity
    if (88.72283935546875 <= fx.f) {
        res = 1.0/0.0;
        return true;
    }
    
    // If x is NaN, e^x is NaN
    if ((fx.x & 0x7FFFFFFF) > 0x7F800000) {
        res = 0.0/0.0;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(float x) {
    double xp = x * 92.332482616893656768297660164535045623779296875;
    int N = (int)xp;
    
    return x - N *
    0.01083042469624914509729318723429969395510852336883544921875;
}
    
double IntervalGenerator::OutputCompensation(float x, double yp) {
    double xp = x * 92.332482616893656768297660164535045623779296875;
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
    tempYp.d = exp(xp);
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
    
    IntervalGenerator ExpIntGen;
    ExpIntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
