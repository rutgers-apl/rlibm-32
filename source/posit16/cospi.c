#include "posit16_math.h"

posit16_t rlibm_cospi(posit16_t x) {
    if (x.v == 0x8000) {
        // Take care of NaN
        x.v = 0x8000;
        return x;
    }
    
    double dx = convertP16ToDouble(x);
    double modifier = 1;

    // cos(-x) = cos(x)
    if (dx < 0.0f) dx = -1 * dx;
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double y = 0;
    if (frac <= 0.003509521484375) {
        y = 1.0001220703125;
    } else if (frac < 0.5f) {
        double xSquared = frac * frac;
        y = 2.215338495769658688772096866159699857234954833984375e-01;
        y *= xSquared;
        y += -1.3327362938689424343152722940430976450443267822265625;
        y *= xSquared;
        y += 4.05853647916781223869975292473100125789642333984375;
        y *= xSquared;
        y += -4.93479863229652071510145106003619730472564697265625;
        y *= xSquared;
        y += 1.000000009410458634562246515997685492038726806640625;
    } else {
        y = 0.0f;
    }
    
    y *= modifier;
    return convertDoubleToP16(y);
}
