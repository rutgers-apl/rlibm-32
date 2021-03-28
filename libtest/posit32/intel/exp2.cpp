#define MPFR_PREC 200
#include "LibTestHelper.h"

posit32_t MpfrCalculate(posit32_t x) {
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_exp2(mval, mval, MPFR_RNDN);
    if (mpfr_inf_p(mval)) return castP32(0x7FFFFFFF);
    if (mpfr_zero_p(mval)) return castP32(0x00000001);
    return FromMPFR(mval);
    /*
    switch (x.v) {
        case 176288406 :
            return castP32(1073798791);
        
        case 254933602 :
            return castP32(1074032431);
        
        case 348625710 :
            return castP32(1074613135);
        
        case 363412220:
            return castP32(1074774415);

        case 550665663:
            return castP32(1080309613);

        case 594157902:
            return castP32(1082299907);

        case 636870466:
            return castP32(1084281903);

        case 670759455:
            return castP32(1085874015);

        case 792836773:
            return castP32(1097857101);

        case 1006078383:
            return castP32(1164927497);

        case 3488551774:
            return castP32(1030709769);

        case 3556025406:
            return castP32(1040913299);

        case 3764822393:
            return castP32(1062919705);

        case 3769926861:
            return castP32(1063344493);

        case 3820976999:
            return castP32(1067631551);

        case 3920533977:
            return castP32(1071455611);

        case 3944921309:
            return castP32(1071979879);

        case 3988086641:
            return castP32(1072601059);

        case 4176931067:
            return castP32(1073718305);

        case 4202328459:
            return castP32(1073733183);

        case 4267613754:
            return castP32(1073741757);
        default :
            double res = exp2(convertP32ToDouble(x));
            if (res == 0.0) {
                return castP32(0x00000001);
            } else if (res == 1.0/0.0) {
                return castP32(0x7FFFFFFF);
            }
            return convertDoubleToP32(res);
    }
    */
}

posit32_t dMlibTest(posit32_t x) {
    double result = exp2(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_exp2(x);
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Exp2", argv[1]);
    
    return 0;
}
