#include "mpfr.h"
#include "float_math.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

mpfr_t mval;

float MpfrCalculate(float x);
float rlibmTest(float x);

float ToMPFR(mpfr_t mval) {
    double retVal = mpfr_get_d(mval, MPFR_RNDN);

    if (retVal == 0) return 0.0f;
    if (retVal != retVal) {
        return retVal;
    }
    
    if (mpfr_cmp_d(mval, pow(2, -150)) <= 0 && mpfr_cmp_d(mval, -pow(2, -150)) >= 0) {
        return 0.0f;
    }

    long exp;
    double fr = mpfr_get_d_2exp(&exp, mval, MPFR_RNDN);
    fr *= 2;
    exp--;
    
    if (mpfr_cmp_d(mval, 0.0) > 0) {
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -149)) < 0) return pow(2, -149);
        if (mpfr_cmp_d(mval, pow(2, -148)) < 0) return pow(2, -148);

    } else {
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -149)) > 0) return -pow(2, -149);
        if (mpfr_cmp_d(mval, -pow(2, -148)) > 0) return -pow(2, -148);
    }
    
    if (exp >= -148 && exp <= -127) {
        int prec = 150 + exp;
        mpfr_t r;
        mpfr_init2(r, prec);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    } else {
        mpfr_t r;
        mpfr_init2(r, 24);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    }
}

unsigned int m_ulpf(float x, float y) {
  if (x == 0)
    x = 0; // -0 == 0
  if (y == 0)
    y = 0; // -0 == 0

  if (x != x && y != y) return 0;

  if (x != x)
    return UINT_MAX - 1; // Maximum error
  if (y != y)
    return UINT_MAX - 1; // Maximum error

  int xx = *((int *)&x);
  xx = xx < 0 ? INT_MAX - xx : xx;

  int yy = *((int *)&y);
  yy = yy < 0 ? INT_MAX - yy : yy;
  return xx >= yy ? xx - yy : yy - xx;
}

void RunCorrectnessTest(char const* FunctionName, char* resFileName) {
    int printcount = 0;
    mpfr_init2(mval, MPFR_PREC);

    unsigned long wrongRlibmCount = 0;
    unsigned long count = 0;

    unsigned int maxUlpRlibm = 0;
    float maxXRlibm = 0;
    
    FILE* f = fopen(resFileName, "w");

    float x;
    floatX xbase;
    for (count = 0x0; count < 0x100000000; count++) {
        xbase.x = count;
        x = xbase.f;
        
        float bmy = MpfrCalculate(x);
        float bres = rlibmTest(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bmy != bmy) continue;
        
        // Otherwise check if the output is correct
        if (bres != bmy) {
            
            if (printcount < 10) {
                fprintf(f, "count = %lu\n", count);
                fprintf(f, "bres = %.100e\n", bres);
                fprintf(f, "bmy  = %.100e\n", bmy);
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
    
    fprintf(f, "%s TEST RESULT:\n", FunctionName);
    if (wrongRlibmCount == 0) {
        fprintf(f, "RLIBM returns correct result for all inputs\n");
    } else {
        fprintf(f, "RLIBM: Found %lu/%lu inputs with wrong result\n", wrongRlibmCount, count);
        fprintf(f, "RLIBM's max ulp error: %u\n", maxUlpRlibm);
        fprintf(f, "RLIBM max ulp error at: %.100e\n", maxXRlibm);
    }
    
    fclose(f);
    mpfr_clear(mval);
}
