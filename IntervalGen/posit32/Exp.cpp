#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    /*
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_exp(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
     */
    
    // If you want to make it run faster, you can try the below code. Run it at
    // your own risk.
    posit32 res;
    switch (x.value) {
        case 8388608 :
            res.value = 1073741825;
            return res;
            
        case 125828352 :
            res.value = 1073766401;
            return res;
            
        case 146394183 :
            res.value = 1073786491;
            return res;
            
        case 232703665 :
            res.value = 1073995703;
            return res;
            
        case 277994243 :
            res.value = 1074342129;
            return res;
            
        case 278268980 :
            res.value = 1074344285;
            return res;
            
        case 315218639 :
            res.value = 1074634561;
            return res;
            
        case 328917479 :
            res.value = 1074742339;
            return res;
            
        case 353233600 :
            res.value = 1075073357;
            return res;
            
        case 435196834 :
            res.value = 1076892373;
            return res;
            
        case 484181783 :
            res.value = 1078935323;
            return res;
            
        case 531981330:
            res.value = 1082073185;
            return res;
            
        case 606416336 :
            res.value = 1087100779;
            return res;
            
        case 695497874 :
            res.value = 1095109715;
            return res;
            
        case 779740549:
            res.value = 1107808141;
            return res;
            
        case 886453498 :
            res.value = 1139983475;
            return res;
            
        case 949274143 :
            res.value = 1168997027;
            return res;
            
        case 1054622425 :
            res.value = 1243621573;
            return res;
            
        case 1116551649 :
            res.value = 1324696961;
            return res;
            
        case 1174121770 :
            res.value = 1400644765;
            return res;
            
        case 1223001644 :
            res.value = 1497292223;
            return res;
            
        case 1240851334 :
            res.value = 1544557361;
            return res;
            
        case 1423867798 :
            res.value = 1919877963;
            return res;
            
        case 1447561583:
            res.value = 1953965929;
            return res;
            
        case 3002068727 :
            res.value = 484623899;
            return res;
            
        case 3014996578 :
            res.value = 502038269;
            return res;
            
        case 3054755927 :
            res.value = 582384405;
            return res;
            
        case 3084961894 :
            res.value = 677822899;
            return res;
            
        case 3128146849 :
            res.value = 734307029;
            return res;
            
        case 3164503295 :
            res.value = 795732033;
            return res;
            
        case 3185007842 :
            res.value = 821882737;
            return res;
            
        case 3201030038 :
            res.value = 841002223;
            return res;
            
        case 3299499163 :
            res.value = 935458709;
            return res;
            
        case 3322101822 :
            res.value = 949103599;
            return res;
            
        case 3326595236 :
            res.value = 951530919;
            return res;
            
        case 3331050605 :
            res.value = 953978139;
            return res;
            
        case 3486306597 :
            res.value = 1013062005;
            return res;
            
        case 3547164607 :
            res.value = 1025865311;
            return res;
            
        case 3623670055 :
            res.value = 1042153809;
            return res;
            
        case 3754660895 :
            res.value = 1057075047;
            return res;
            
        case 3756230542 :
            res.value = 1057259137;
            return res;
            
        case 3932991725 :
            res.value = 1070834553;
            return res;
            
        case 4000125047 :
            res.value = 1072284611;
            return res;
            
        case 4005298404 :
            res.value = 1072365019;
            return res;
            
        case 4023715328 :
            res.value = 1072651461;
            return res;
            
        case 4035724792 :
            res.value = 1072838411;
            return res;
            
        case 4056072201 :
            res.value = 1073155457;
            return res;
            
        case 4093612714 :
            res.value = 1073479589;
            return res;
            
        case 4135957665 :
            res.value = 1073627891;
            return res;
            
        case 4151576335 :
            res.value = 1073658385;
            return res;
            
        case 4226778991 :
            res.value = 1073737465;
            return res;
            
        case 4268064767 :
            res.value = 1073741733;
            return res;
            
        case 4285530112 :
            res.value = 1073741823;
            return res;
        default :
            res = exp(x.toDouble());
            return res;
    }
}

bool IntervalGenerator::ComputeSpecialCase(posit32 x, posit32& res) {
    // If x =< -150, then 2^x rounds to minpos
    if (x.value <= 2531481231 && x.value > 0x80000000) {
        res.value = 0x00000001;
        return true;
    }
    
    // If x is between these values, 2^x rounds to 1.0
    if (x.value >= 4287627264 || x.value <= 8388607) {
        res.value = 0x40000000;
        return true;
    }
    
    // If x >= 128, then 2^x rounds to infinity
    if (x.value >= 1763486065 && x.value < 0x80000000) {
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
    double xp = x * 92.332482616893656768297660164535045623779296875;
    int N = (int)xp;
    
    return x - N *
    0.01083042469624914509729318723429969395510852336883544921875;
}
    
double IntervalGenerator::OutputCompensation(double x, double yp) {
    double xp = x * 92.332482616893656768297660164535045623779296875;
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
    
    IntervalGenerator ExpIntGen;
    ExpIntGen.CreateReducedIntervalFile(argv[1]);

    mpfr_clear(mval);
    return 0;
}
