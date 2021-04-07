#pragma once
#include "mpfr.h"

using namespace std;

mpfr_t mval;

template <class T>
class Elementary {
    public :
    
    static double RangePropagation(double, double);
    static double ReverseRangePropagation(double, double);
    static bool FlipLbAndUb(double);
        
    static T MpfrCalculateFunction(T);
    static double RangeReduction(T, double&);
    static bool ComputeSpecialCase(T, T&);
    static T FromMPFR(mpfr_t);
};

// Crazy contraption to make sure we do not do double rounding and cause error.
template <>
posit16 Elementary<posit16>::FromMPFR(mpfr_t _mval) {
    posit16 rv;
    // Check for special values
    if (mpfr_nan_p(_mval) != 0) { rv.value = 0x8000; return rv; }
    if (mpfr_inf_p(_mval) != 0) { rv.value = 0x8000; return rv; }
    if (mpfr_cmp_d(_mval, 0.0) == 0) { rv.value = 0; return rv; }
    
    if (mpfr_cmp_d(_mval, 0) > 0) {
        if (mpfr_cmp_d(_mval, pow(2, 27)) > 0)  { rv.value = 0x7fff; return rv; }
        if (mpfr_cmp_d(_mval, 1.5 * pow(2, 25)) >= 0) { rv.value = 0x7ffe; return rv; }
        if (mpfr_cmp_d(_mval, 1.5 * pow(2, 24)) > 0) { rv.value = 0x7ffd; return rv; }
        if (mpfr_cmp_d(_mval, pow(2, 24)) >= 0) { rv.value = 0x7ffc; return rv; }
        
        if (mpfr_cmp_d(_mval, pow(2, -27)) < 0) { rv.value = 0x0001; return rv; }
        if (mpfr_cmp_d(_mval, 1.5 * pow(2, -26)) <= 0) { rv.value = 0x0002; return rv; }
        if (mpfr_cmp_d(_mval, 1.5 * pow(2, -25)) < 0) { rv.value = 0x0003; return rv; }
        if (mpfr_cmp_d(_mval, pow(2, -24)) <= 0) { rv.value = 0x0004; return rv; }
    } else {
        if (mpfr_cmp_d(_mval, -pow(2, 27)) < 0) { rv.value = 0x8001; return rv; }
        if (mpfr_cmp_d(_mval, -1.5 * pow(2, 25)) <= 0) { rv.value = 0x8002; return rv; }
        if (mpfr_cmp_d(_mval, -1.5 * pow(2, 24)) < 0) { rv.value = 0x8003; return rv; }
        if (mpfr_cmp_d(_mval, -pow(2, 24)) <= 0) { rv.value = 0x8004; return rv; }
        
        if (mpfr_cmp_d(_mval, -pow(2, -27)) > 0) { rv.value = 0xffff; return rv; }
        if (mpfr_cmp_d(_mval, -1.5 * pow(2, -26)) >= 0) { rv.value = 0xfffe; return rv; }
        if (mpfr_cmp_d(_mval, -1.5 * pow(2, -25)) > 0) { rv.value = 0xfffd; return rv; }
        if (mpfr_cmp_d(_mval, -pow(2, -24)) >= 0) { rv.value = 0xfffc; return rv; }
    }
    
    long exp;
    double fr = mpfr_get_d_2exp(&exp, _mval, MPFR_RNDN);
    long origExp = exp;
    fr *= 2;
    exp--;
    if (exp < 0) {
        exp *= -1;
        exp--;;
    }
    exp >>= 1;
    long p = 13 - exp;
    mpfr_t r;
    mpfr_init2(r, p);
    mpfr_set(r, _mval, MPFR_RNDN);
    double retVal = mpfr_get_d(r, MPFR_RNDN);
    mpfr_clear(r);
    rv = retVal;
    return rv;
}

template <>
bfloat16 Elementary<bfloat16>::FromMPFR(mpfr_t _mval) {
        double retVal = mpfr_get_d(_mval, MPFR_RNDN);

        if (retVal == 0) return 0.0;
        if (retVal != retVal) {
            return retVal;
        }
        
        if (mpfr_cmp_d(_mval, pow(2, -134)) <= 0 &&
            mpfr_cmp_d(_mval, -pow(2, -134)) >= 0) {
            return 0.0;
        }

        long exp;
        double fr = mpfr_get_d_2exp(&exp, _mval, MPFR_RNDN);
        fr *= 2;
        exp--;
        
        if (mpfr_cmp_d(_mval, 0.0) > 0) {
            if (mpfr_cmp_d(_mval, 1.5 * pow(2, -133)) < 0) return pow(2, -133);
            if (mpfr_cmp_d(_mval, pow(2, -132)) < 0) return pow(2, -132);
        } else {
            if (mpfr_cmp_d(_mval, -1.5 * pow(2, -133)) > 0) return -pow(2, -133);
            if (mpfr_cmp_d(_mval, -pow(2, -132)) > 0) return -pow(2, -132);
        }
        
        if (exp >= -132 && exp <= -127) {
            int prec = 134 + exp;
            mpfr_t r;
            mpfr_init2(r, prec);
            mpfr_set(r, _mval, MPFR_RNDN);
            retVal = mpfr_get_d(r, MPFR_RNDN);
            mpfr_clear(r);
            return retVal;
        } else {
            mpfr_t r;
            mpfr_init2(r, 8);
            mpfr_set(r, _mval, MPFR_RNDN);
            retVal = mpfr_get_d(r, MPFR_RNDN);
            mpfr_clear(r);
            return retVal;
        }
    }

template <>
float Elementary<float>::FromMPFR(mpfr_t _mval) {
    double retVal = mpfr_get_d(_mval, MPFR_RNDN);

    if (retVal == 0) return 0.0;
    if (retVal != retVal) {
        return retVal;
    }
    
    if (mpfr_cmp_d(_mval, pow(2, -150)) <= 0 && mpfr_cmp_d(_mval, -pow(2, -150)) >= 0) {
        return 0;
    }

    long exp;
    double fr = mpfr_get_d_2exp(&exp, _mval, MPFR_RNDN);
    fr *= 2;
    exp--;
    
    if (mpfr_cmp_d(_mval, 0.0) > 0) {
        if (mpfr_cmp_d(_mval, 1.5 * pow(2, -149)) < 0) return pow(2, -149);
        if (mpfr_cmp_d(_mval, pow(2, -148)) < 0) return pow(2, -148);

    } else {
        if (mpfr_cmp_d(_mval, -1.5 * pow(2, -149)) > 0) return -pow(2, -149);
        if (mpfr_cmp_d(_mval, -pow(2, -148)) > 0) return -pow(2, -148);
    }
    
    if (exp >= -148 && exp <= -127) {
        int prec = 150 + exp;
        mpfr_t r;
        mpfr_init2(r, prec);
        mpfr_set(r, _mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    } else {
        mpfr_t r;
        mpfr_init2(r, 24);
        mpfr_set(r, _mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    }
}
