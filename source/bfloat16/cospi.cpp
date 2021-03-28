#include "bfloat16_math.hpp"

bfloat16 rlibm_cospi(bfloat16 x) {
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
        return 1.0f;
    }
    
    double modifier = 1;

    // cos(-x) = cos(x)
    if (fInput < 0.0f) fInput = -fInput;
     
    // How do we reduce range of x?
    // Reduce x to [0, 1)
    double intPart;
    double frac = modf((double)fInput, &intPart);
    int iIntPart = intPart;
     
    // if iIntPart is odd, then flip modifier
    if (iIntPart % 2 == 1) modifier *= -1;
     
    // cos(pi - x) = -cos(x)
    if (frac >= 0.5) {
        frac = 1.0 - frac;
        modifier *= -1;
    }
    
    double fracPart = frac;
    double y = 0;
    if (fracPart <= 0.01989746093750000000) {
        y = 1.00390625;
    } else if (fracPart < 0.5f) {
        double xSquared = fracPart * fracPart;
        y = -1.1640167711700171171429474270553328096866607666015625;
        y *= xSquared;
        y += 4.02150995405109146219047033810056746006011962890625;
        y *= xSquared;
        y += -4.9324802047472200428046562592498958110809326171875;
        y *= xSquared;
        y += 9.9997996859304827399483883709763176739215850830078125e-01;
    } else {
        y = 0.0f;
    }
    
    return y * modifier;
}
