#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    /*
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_exp2(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
     */
    
    // If you want to make it run faster, you can try the below code. Run it at
    // your own risk.
    posit32 res;
    switch (x.value) {
        case 176288406 :
            res.value = 1073798791;
            return res;
        
        case 254933602 :
            res.value = 1074032431;
            return res;
        
        case 348625710 :
            res.value = 1074613135;
            return res;
        
        case 363412220:
            res.value = 1074774415;
            return res;

        case 550665663:
            res.value = 1080309613;
            return res;

        case 594157902:
            res.value = 1082299907;
            return res;

        case 636870466:
            res.value = 1084281903;
            return res;

        case 670759455:
            res.value = 1085874015;
            return res;

        case 792836773:
            res.value = 1097857101;
            return res;

        case 1006078383:
            res.value = 1164927497;
            return res;

        case 3488551774:
            res.value = 1030709769;
            return res;

        case 3556025406:
            res.value = 1040913299;
            return res;

        case 3764822393:
            res.value = 1062919705;
            return res;

        case 3769926861:
            res.value = 1063344493;
            return res;

        case 3820976999:
            res.value = 1067631551;
            return res;

        case 3920533977:
            res.value = 1071455611;
            return res;

        case 3944921309:
            res.value = 1071979879;
            return res;

        case 3988086641:
            res.value = 1072601059;
            return res;

        case 4176931067:
            res.value = 1073718305;
            return res;

        case 4202328459:
            res.value = 1073733183;
            return res;

        case 4267613754:
            res.value = 1073741757;
            return res;
        default :
            res = exp2(x.toDouble());
            return res;
    }
}

bool IntervalGenerator::ComputeSpecialCase(posit32 x, posit32& res) {
    // If x =< -150, then 2^x rounds to minpos
    if (x.value <= 2493513727 && x.value > 0x80000000) {
        res.value = 0x00000001;
        return true;
    }
    
    // If x is between these values, 2^x rounds to 1.0
    if (x.value >= 4287163065 || x.value <= 9317006) {
        res.value = 0x40000000;
        return true;
    }
    
    // If x >= 128, then 2^x rounds to infinity
    if (x.value >= 1801453569 && x.value < 0x80000000) {
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
    double xp = x * 64;
    int N = (int)xp;
    return x - N * 0.015625;
}
    
double IntervalGenerator::OutputCompensation(double x, double yp) {
    double xp = x * 64;
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
    
    
    lb = exp2(xp);
    ub = exp2(xp);
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
    
    IntervalGenerator Exp2IntGen;
    Exp2IntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
