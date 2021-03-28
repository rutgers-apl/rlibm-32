#include "bfloat16_math.hpp"

bfloat16 rlibm_log(bfloat16 x) {
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
    double y = 1.2722152807088404902202682933420874178409576416015625;
    y *= codyX2;
    y += 3.91172520217394070751737444879836402833461761474609375e-01;
    y *= codyX2;
    y += 9.749438269300123582894457285874523222446441650390625e-01;
    y *= codyX2;
    y += 2.885102725620722008414986703428439795970916748046875;
    y *= codyX;
    
    // Range propagation
    y = (m + y) / 1.442695040888963387004650940070860087871551513671875;
    return y;
}
