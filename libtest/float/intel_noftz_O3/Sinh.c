#define MPFR_PREC 200
#include "LibTestHelper.h"

float MpfrCalculate(float x) {
    mpfr_set_d(mval, (float)x, MPFR_RNDN);
    mpfr_sinh(mval, mval, MPFR_RNDN);
    return ToMPFR(mval);
}

float fMlibTest(float x) {
    float result = sinhf(x);
    return result;
}

float dMlibTest(float x) {
    double dx = (double)x;
    double result = sinh(dx);
    float res = (float)result;
    if (result == dx) return x;
    return res;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Float - Sinh", argv[1]);
    return 0;
}
