#include "posit16_math.h"

posit16_t rlibm_exp(posit16_t x) {
    
    if (x.v == 0x8000) {
        // Take care of NaR
        return x;
    } else if (x.v > 0x8000 & x.v <= 0x8f52) {
        // Take care of when result is minpos. exp(x) for posit should never
        // return 0, because exp(x) is always > 0 as long as x != -infinity
        x.v = 0x1;
        return x;
    } else if (x.v >= 0x70ae && x.v < 0x8000) {
        // Take care of maxpos case.
        x.v = 0x7FFF;
        return x;
    } else if ((x.v >= 0xff80) || (x.v <= 0xbf)) {
        // The values in these range return 1.0.
        x.v = 0x4000;
        return x;
    }
    
    // Extract exponent and mantissa (where mantissa is between [1, 2)
    double xprime = convertP16ToDouble(x) *
    1.442695040888963387004650940070860087871551513671875;
    double modifier;
    double f = modf(xprime, &modifier);
    if (f < 0.0f) {
        f += 1.0;
        modifier -= 1.0;
    }
    
    // Now compute polynomial
    double y = 3.880795968797916273285153465621988289058208465576171875e-04 ;
    y *= f;
    y += 7.56416228767151587429606873769216690561734139919281005859375e-04;
    y *= f;
    y += 1.019728060416365440776775841413837042637169361114501953125e-02;
    y *= f;
    y += 5.522989323495941516029006379540078341960906982421875e-02;
    y *= f;
    y += 2.40286646236610668125877054990269243717193603515625e-01;
    y *= f;
    y += 6.93141820259879803955982424668036401271820068359375e-01;
    y *= f;
    y += 1.0000001298120355652798707524198107421398162841796875;

    y = ldexp(y, modifier);
    
    return convertDoubleToP16(y);
}
