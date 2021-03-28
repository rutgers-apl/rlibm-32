#include "posit16_math.h"

posit16_t rlibm_sinpi(posit16_t x) {
    if (x.v == 0x8000) {
        // Take care of NaN
        x.v = 0x8000;
        return x;
    }
    
    double dx = convertP16ToDouble(x);
    double modifier = 1;

    // sin(-x) = -sin(x)
    if (dx < 0.0f) {
        dx = -1.0 * dx;
        modifier *= -1;
    }
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf(dx, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // sin(x) = sin(pi - x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
    }
    double fracPart = frac;
    double y = 0;
    if (fracPart <= 0.00252532958984375000) {
        y = 3.141577060931899811890843920991756021976470947265625 * fracPart;
    } else {
        double xSquared = fracPart * fracPart;
        y = 9.47599641221426869375221713198698125779628753662109375e-02;
        y *= xSquared;
        y += -6.0547119473342603246379667325527407228946685791015625e-01;
        y *= xSquared;
        y += 2.55098424541712009983029929571785032749176025390625;
        y *= xSquared;
        y += -5.1677486367595673044661452877335250377655029296875;
        y *= xSquared;
        y += 3.141593069399674309494230328709818422794342041015625;
        y *= fracPart;
    }
    
    y *= modifier;
    return convertDoubleToP16(y);
}
