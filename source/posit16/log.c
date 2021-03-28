#include "posit16_math.h"

posit16_t rlibm_log(posit16_t x) {
    if (x.v == 0x0 || x.v >= 0x8000) {
        // If x == 0, NaR, or negative, then resutl should be NaR
        x.v = 0x8000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    int m;
    double fx = frexp(convertP16ToDouble(x), &m);
    fx *= 2.0;
    m--;
    
    // Cody and Waite Transformation on input
    double dx = fx;
    double codyX = (dx - 1) / (dx + 1);
    double codyX2 = codyX * codyX;
    
    // Now compute polynomial
    double y = 4.5254178489671204044242358577321283519268035888671875e-01;
    y *= codyX2;
    y += 3.9449243216490248453709455134230665862560272216796875e-01;
    y *= codyX2;
    y += 5.7802192858859535729010303839459083974361419677734375e-01;
    y *= codyX2;
    y += 9.6177728824005104257821585633791983127593994140625e-01;
    y *= codyX2;
    y += 2.8853901812623536926594169926829636096954345703125;
    y *= codyX;
    
    // Range propagation
    y = (m + y) / 1.442695040888963387004650940070860087871551513671875;
    
    return convertDoubleToP16(y);
}
