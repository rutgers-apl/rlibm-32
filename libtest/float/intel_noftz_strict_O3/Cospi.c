#define MPFR_PREC 400
#include "LibTestHelper.h"

float MpfrCalculate(float x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, (double)x, MPFR_RNDN);
    mpfr_cos(mval, mval, MPFR_RNDN);
    return ToMPFR(mval);
}

float fMlibTest(float x) {
    float result = cospif(x);
    return result;
}

float dMlibTest(float x) {
    double dx = (double)x;
    double result = cospi(dx);
    float res = (float)result;
    if (result == dx) return x;
    return res;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Float - Sinpi", argv[1]);
    return 0;
}
