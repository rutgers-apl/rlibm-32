#include "float_math.h"
#include "float_headers/constants.h"
#include "float_headers/Log2_8.h"

float rlibm_log2_8(float x) {
    floatX fix, fit;
    fix.f = x;
    int m = 0;
    
    if (fix.x < 0x800000 || fix.x >= 0x7F800000) {
        if ((fix.x & 0x7FFFFFFF) == 0) { // log(+/-0) = -infty
            fix.x = 0xFF800000;
            return fix.f;
        }
        
        if (fix.x > 0x7FFFFFFF) { // Log(-val) = NaN
            return (x - x) / 0;
            
        }
        
        if (fix.x >= 0x7F800000) {
            return x + x;
        }
        
        fix.f *= 8.388608e+06;
        m -= 23;
    }
    
    m += fix.x >> 23;
    m -= 127;
    fix.x &= 0x007FFFFF;
    fix.x |= 0x3F800000;
    
    fit.x = fix.x & 0x007F0000;
    int FIndex = fit.x >> 16;
    fit.x |= 0x3F800000;
    
    double f = fix.f - fit.f;
    f *= log_oneByF[FIndex];
    
    // Find the index of polynomial coefficients
    doubleX dX;
    dX.d = f;
    unsigned long index = (dX.x & 0x01FFFFFFFFFFFFFFlu) >> 49lu;
    const double* coeff = coeffs8[index];

    double y = coeff[2];
    y *= f;
    y += coeff[1];
    y *= f;
    y += coeff[0];
    y *= f;
    
    return y + log2_lut[FIndex] + m;
}
