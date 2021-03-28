#define MPFR_PREC 200
#include "LibTestHelper.h"

posit32_t MpfrCalculate(posit32_t x) {
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_exp(mval, mval, MPFR_RNDN);
    if (mpfr_inf_p(mval)) return castP32(0x7FFFFFFF);
    if (mpfr_zero_p(mval)) return castP32(0x00000001);
    return FromMPFR(mval);
}

posit32_t dMlibTest(posit32_t x) {
    double result = exp(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_exp(x);
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Exp", argv[1]);
    
    return 0;
}
