#include "mpfr.h"
#include "posit32_math.h"
#include "softposit.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

mpfr_t mval;

posit32_t MpfrCalculate(posit32_t x);
posit32_t rlibmTest(posit32_t x);

posit32_t FromMPFR(mpfr_t _mval) {
    posit32_t rv;
    // Check for Really special cases
    if (mpfr_nan_p(_mval) != 0) { return castP32(0x80000000); }
    if (mpfr_inf_p(_mval) != 0) { return castP32(0x80000000); }
    if (mpfr_cmp_d(_mval, 0.0) == 0) { return castP32(0); }
    
    // Check for values without fraction bits:
    if (mpfr_cmp_d(_mval, 0) > 0) {
        if (mpfr_cmp_d(_mval, ldexp(1.75, 107)) >= 0) { //1.75 * 2^107
            if (mpfr_cmp_d(_mval, ldexp(1.0, 118)) > 0) { return castP32(0x7FFFFFFF); }
            if (mpfr_cmp_d(_mval, ldexp(1.0, 115)) >= 0) { return castP32(0x7FFFFFFE); }
            if (mpfr_cmp_d(_mval, ldexp(1.0, 113)) > 0) { return castP32(0x7FFFFFFD); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 111)) >= 0) { return castP32(0x7FFFFFFC); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 110)) > 0) { return castP32(0x7FFFFFFB); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 109)) >= 0) { return castP32(0x7FFFFFFA); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 108)) > 0) { return castP32(0x7FFFFFF9); }
            return castP32(0x7FFFFFF8);
        }
        if (mpfr_cmp_d(_mval, ldexp(1.25, -108)) <= 0) {
            if (mpfr_cmp_d(_mval, ldexp(1.0, -118)) < 0) { return castP32(0x00000001); }
            if (mpfr_cmp_d(_mval, ldexp(1.0, -115)) <= 0) { return castP32(0x00000002); }
            if (mpfr_cmp_d(_mval, ldexp(1.0, -113)) < 0) { return castP32(0x00000003); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -112)) <= 0) { return castP32(0x00000004); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -111)) < 0) { return castP32(0x00000005); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -110)) <= 0) { return castP32(0x00000006); }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -109)) < 0) { return castP32(0x00000007); }
            return castP32(0x00000008);
        }
    } else {
        if (mpfr_cmp_d(_mval, ldexp(-1.75, 107)) <= 0) { //1.75 * 2^107
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 118)) < 0) { return castP32(0x80000001); }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 115)) <= 0) { return castP32(0x80000002); }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 113)) < 0) { return castP32(0x80000003); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 111)) <= 0) { return castP32(0x80000004); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 110)) < 0) { return castP32(0x80000005); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 109)) <= 0) { return castP32(0x80000006); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 108)) < 0) { return castP32(0x80000007); }
            return castP32(0x80000008);
        }
        
        if (mpfr_cmp_d(_mval, ldexp(-1.25, -108)) >= 0) {
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -118)) > 0) { return castP32(0xFFFFFFFF); }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -115)) >= 0) { return castP32(0xFFFFFFFE); }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -113)) > 0) { return castP32(0xFFFFFFFD); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -112)) >= 0) { return castP32(0xFFFFFFFC); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -111)) > 0) { return castP32(0xFFFFFFFB); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -110)) >= 0) { return castP32(0xFFFFFFFA); }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -109)) > 0) { return castP32(0xFFFFFFF9); }
            return castP32(0xFFFFFFF8);
        }
    }
    
    long exp;
    double fr = mpfr_get_d_2exp(&exp, _mval, MPFR_RNDN);
    long origExp = exp;
    fr *= 2;
    exp--;
    
    if (exp < 0) {
        exp *= -1;
        exp--;
    }
    
    exp >>= 2; //(#regime - 1)
    long p = 28 - exp;
    mpfr_t r;
    mpfr_init2(r, p);
    mpfr_set(r, _mval, MPFR_RNDN);
    double retVal = mpfr_get_d(r, MPFR_RNDN);
    mpfr_clear(r);
    return convertDoubleToP32(retVal);
}

unsigned int m_ulpf(posit32_t x, posit32_t y) {
    if (x.v > y.v) return x.v - y.v;
    return y.v - x.v;
}

void RunCorrectnessTest(char const* FunctionName, char* resFileName) {
    int printcount = 0;
    mpfr_init2(mval, MPFR_PREC);

    unsigned long wrongRlibmCount = 0;
    unsigned long count = 0;
    
    unsigned int maxUlpRlibm = 0;
    unsigned int maxUlpDMlib = 0;
    posit32_t maxXRlibm;
    posit32_t maxXDMlib;

    posit32_t x;
    for (count = 0; count < 0x100000000; count++) {
        x.v = count;
        
        posit32_t bmy = MpfrCalculate(x);
        posit32_t bres = rlibmTest(x);
        
        // Otherwise check if the output is correct
        if (!p32_eq(bres, bmy)) {
            
            if (printcount < 10) {
                fprintf(f, "count = %lu\n", count);
                fprintf(f, "bres = %.100e\n", convertP32ToDouble(bres));
                fprintf(f, "bmy  = %.100e\n", convertP32ToDouble(bmy));
                printcount++;
            }
            wrongRlibmCount++;
            unsigned int error = m_ulpf(bres, bmy);
            if (error > maxUlpRlibm) {
                maxUlpRlibm = error;
                maxXRlibm = x;
            }
        }
    }
    
    FILE* f = fopen(resFileName, "w");
    
    fprintf(f, "\n\n%s TEST RESULT:\n", FunctionName);
    if (wrongRlibmCount == 0) {
        fprintf(f, "RLIBM returns correct result for all inputs\n");
    } else {
        fprintf(f, "RLIBM: Found %lu/%lu inputs with wrong result\n", wrongRlibmCount, count);
        fprintf(f, "RLIBM's max ulp error: %u\n", maxUlpRlibm);
        fprintf(f, "RLIBM max ulp error at: %.100e\n", convertP32ToDouble(maxXRlibm));
    }
    
    fclose(f);
    mpfr_clear(mval);
}
