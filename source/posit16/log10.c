#include "posit16_math.h"

posit16_t rlibm_log10(posit16_t x) {
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
    double y = 6.91650888349585102332639507949352264404296875e-01;
    y *= codyX2;
    y += 3.30016589138880600540204568460467271506786346435546875e-01;
    y *= codyX2;
    y += 5.837756666515827586039222296676598489284515380859375e-01;
    y *= codyX2;
    y += 9.6158476800643521986700079651200212538242340087890625e-01;
    y *= codyX2;
    y += 2.885392110906054075059046226670034229755401611328125;
    y *= codyX;
    
    // Range propagation
    y = (m + y) / 3.321928094887362181708567732130177319049835205078125;
    
    return convertDoubleToP16(y);
}
