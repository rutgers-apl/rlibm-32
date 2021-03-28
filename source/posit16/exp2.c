#include "posit16_math.h"

posit16_t rlibm_exp2(posit16_t x) {
    
    if (x.v > 0x8000 & x.v <= 0x8d3f) {
        // Take care of when result is minpos. exp(x) for posit should never
        // return 0, because exp(x) is always > 0 as long as x != -infinity
        x.v = 0x1;
        return x;
    } else if (x.v >= 0x72c1 && x.v < 0x8000) {
        // Take care of maxpos case.
        x.v = 0x7FFF;
        return x;
    } else if (x.v == 0x8000) {
        // Take care of NaR
        return x;
    } else if ((x.v >= 0xff64) || (x.v <= 0xdc)) {
        // The values in these range return 1.0.
        x.v = 0x4000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    double xprime = convertP16ToDouble(x);
    double modifier;
    double f = modf(xprime, &modifier);
    if (f < 0.0f) {
        f += 1.0;
        modifier -= 1.0;
    }
    
    // Now compute polynomial
    double y = 3.65720720951589702875372811519127935753203928470611572265625e-04 ;
    y *= f;
    y += 7.694531242965385771370723233530952711589634418487548828125e-04;
    y *= f;
    y += 1.02531888584330328761939910009459708817303180694580078125e-02;
    y *= f;
    y += 5.5157921920287643346991757198338746093213558197021484375e-02;
    y *= f;
    y += 2.40314607704837424062560558013501577079296112060546875e-01;
    y *= f;
    y += 6.9313911175081532878294865440693683922290802001953125e-01;
    y *= f;
    y += 1.0;

    y = ldexp(y, modifier);
    
    return convertDoubleToP16(y);
}
