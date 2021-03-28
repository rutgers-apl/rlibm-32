#define MPFR_PREC 200
#include "LibTestHelper.h"

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

posit32_t MpfrCalculate(posit32_t x) {
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_exp10(mval, mval, MPFR_RNDN);
    if (mpfr_inf_p(mval)) return castP32(0x7FFFFFFF);
    if (mpfr_zero_p(mval)) return castP32(0x00000001);
    return FromMPFR(mval);
}

posit32_t dMlibTest(posit32_t x) {
    double result = exp10Func(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_exp10(x);
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Exp2", argv[1]);
    
    return 0;
}
