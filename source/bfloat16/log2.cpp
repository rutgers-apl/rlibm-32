#include "bfloat16_math.hpp"

bfloat16 rlibm_log2(bfloat16 x) {
    // If x == 0, then it should be -inf
    if (x.val == 0x0 || x.val == 0x8000) {
        x.val = 0xFF80;
        return x;
    }

    // If x == inf, then it should be infinity
    if (x.val == 0x7f80) {
        return x;
    }
    
    // If x == NaN or negative, then it should be NaN
    if (x.val > 0x7F80) {
        x.val = 0xFFFF;
        return x;
    }

    float fInput = (float)x;
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    int m;
    float fx = frexpf(fInput, &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = (double)fx;
    double codyX = (dx - 1) / (dx + 1);
    double codyX2 = codyX * codyX;
    
    // Now compute polynomial
    double y = 7.307375337145580740383365991874597966670989990234375e-01;
    y *= codyX2;
    y += 9.477394346709135941608792563783936202526092529296875e-01;
    y *= codyX2;
    y += 2.885725930059220178947043677908368408679962158203125;
    y *= codyX;
    y += (double)m;
    return y;
}
