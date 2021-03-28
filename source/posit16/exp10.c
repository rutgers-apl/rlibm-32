#include "posit16_math.h"

posit16_t rlibm_exp10(posit16_t x) {
    
    if (x.v > 0x8000 & x.v <= 0x97df) {
        // Take care of when result is minpos. exp(x) for posit should never
        // return 0, because exp(x) is always > 0 as long as x != -infinity
        x.v = 0x1;
        return x;
    } else if (x.v >= 0x6821 && x.v < 0x8000) {
        // Take care of maxpos case.
        x.v = 0x7FFF;
        return x;
    } else if (x.v == 0x8000) {
        // Take care of NaR
        return x;
    } else if ((x.v >= 0xffa9) || (x.v <= 0x77)) {
        // The values in these range return 1.0.
        x.v = 0x4000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    double xprime = convertP16ToDouble(x) * 3.321928094887362181708567732130177319049835205078125;;
    double modifier;
    double f = modf(xprime, &modifier);
    if (f < 0.0f) {
        f += 1.0;
        modifier -= 1.0;
    }
    
    // Now compute polynomial
    double y = 3.3019478519002672979587575952109546051360666751861572265625e-04 ;
    y *= f;
    y += 9.031838553965111128507547988419901230372488498687744140625e-04;
    y *= f;
    y += 1.006802205059511255702542342760352767072618007659912109375e-02;
    y *= f;
    y += 5.5274346317151945573442617387627251446247100830078125e-02;
    y *= f;
    y += 2.40282388412963510138098399693262763321399688720703125e-01;
    y *= f;
    y += 6.93141854936602630488096110639162361621856689453125e-01;
    y *= f;
    y += 1.0000000800001294098962034695432521402835845947265625;

    y = ldexp(y, modifier);
    
    return convertDoubleToP16(y);
}
