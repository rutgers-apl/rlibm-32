#include "bfloat16_math.hpp"

bfloat16 rlibm_sinpi(bfloat16 x) {
    if ((x.val & 0x7FFF) > 0x7F80) {
        // Take care of NaN
        return x;
    }
    
    if ((x.val & 0x7FFF) == 0x7F80) {
        x.val = 0x7FFF;
        return x;
    }
    
    float fInput = (float)x;
    
    if (fInput >= 256.0f || fInput <= -256.0f) {
        return 0.0f;
    }
    
    double modifier = 1;

    // sin(-x) = -sin(x)
    if (fInput < 0.0f) {
        fInput = -fInput;
        modifier *= -1;
    }
    
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf((double)fInput, &intPart);
    int iIntPart = intPart;
    
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
    
    // sin(x) = sin(pi - x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
    }
    double fracPart = frac;
    double y = 0;
    if (fracPart <= 0.006011962890625) {
        y = 3.14159292035398163278614447335712611675262451171875 * fracPart;
    } else {
        double xSquared = fracPart * fracPart;
        y = -4.43008519856437021910977591687696985900402069091796875e-01;
        y *= xSquared;
        y += 2.50692180297728217652775128954090178012847900390625;
        y *= xSquared;
        y += -5.16405991738943459523625278961844742298126220703125;
        y *= xSquared;
        y += 3.141515487020253072358855206402949988842010498046875;
        y *= fracPart;
    }
    
    return y * modifier;
}
