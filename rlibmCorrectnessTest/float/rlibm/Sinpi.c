#define MPFR_PREC 400
#include "LibTestHelper.h"

float MpfrCalculate(float x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, (double)x, MPFR_RNDN);
    mpfr_sin(mval, mval, MPFR_RNDN);
    return ToMPFR(mval);
}

float rlibmTest(float x) {
    float result = rlibm_sinpi(x);
    return result;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Float - Sinpi", argv[1]);
    return 0;
}
