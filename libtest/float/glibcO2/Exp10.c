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

float MpfrCalculate(float x) {
    mpfr_set_d(mval, (float)x, MPFR_RNDN);
    mpfr_exp10(mval, mval, MPFR_RNDN);
    return ToMPFR(mval);
}

float fMlibTest(float x) {
    float result = exp10fFunc(x);
    return result;
}

float dMlibTest(float x) {
    double dx = (double)x;
    double result = exp10Func(dx);
    float res = (float)result;
    if (result == dx) return x;
    return res;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Float - Exp10", argv[1]);
    return 0;
}
