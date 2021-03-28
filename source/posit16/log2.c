#include "posit16_math.h"

posit16_t rlibm_log2(posit16_t x) {
    if (x.v == 0x0 || x.v >= 0x8000) {
        // If x == 0, NaR, or negative, then resutl should be NaR
        x.v = 0x8000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2))
    int m;
    double fx = frexp(convertP16ToDouble(x), &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = fx;
    double codyX = (dx - 1) / (dx + 1);

    double codyX2 = codyX * codyX;
    // Now compute polynomial
    double y = 6.8022527114824737903830964569351635873317718505859375e-01;
    y *= codyX2;
    y += 3.36729567454907396939489672149647958576679229736328125e-01;
    y *= codyX2;
    y += 5.827497609092706642996972732362337410449981689453125e-01;
    y *= codyX2;
    y += 9.616405555684151007511673014960251748561859130859375e-01;
    y *= codyX2;
    y += 2.88539115994917327867597123258747160434722900390625;
    y *= codyX;
    y += (double)m;
    
    return convertDoubleToP16(y);
}
