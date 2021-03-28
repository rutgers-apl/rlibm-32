#include "bfloat16_math.hpp"


bfloat16 rlibm_exp2(bfloat16 x) {
    float fInput = (float)x;
    
    // Take care of 0 case
    if (fInput <= -134.0f) {
        return 0.0f;
    }
     
    // Take care of infinity case
    if (fInput >= 128.0f) {
        x.val = 0x7F80;
        return x;
    }
     
    // Take care of NaN
    if ((x.val & 0x7FFFFFFF) > 0x7F800000) {
        return x.val;
    }
    
    // Take care of when result is 1:
    if (fInput >= -2.8076171875e-03 && fInput <= 2.8076171875e-03) {
        return 1.0f;
    }
     
    // Range Reduction
    double intPart;
    double fracPart = modf(fInput, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }
    
    // Polynomial approximation
    double y = 1.557767964117490015751865684023869107477366924285888671875e-02;
    y *= fracPart;
    y += 4.8046547014740259573528646797058172523975372314453125e-02;
    y *= fracPart;
    y += 2.437159431324379121885925769674940966069698333740234375e-01;
    y *= fracPart;
    y += 6.9265463004053107187729665383812971413135528564453125e-01;
    y *= fracPart;
    y += 1.0000091388165410766220020377659238874912261962890625;

    // Output compensation
    return ldexp(y, intPart);
}
