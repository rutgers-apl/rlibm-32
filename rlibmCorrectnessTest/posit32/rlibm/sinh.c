#define MPFR_PREC 200
#include "LibTestHelper.h"

posit32_t MpfrCalculate(posit32_t x) {
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_sinh(mval, mval, MPFR_RNDN);
    if (mpfr_inf_p(mval) != 0) {
        if (mpfr_signbit(mval)) return castP32(0x80000001);
        else return castP32(0x7FFFFFFF);
    }
    return FromMPFR(mval);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_sinh(x);
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Sinh", argv[1]);
    return 0;
}
