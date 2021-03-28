#include "bfloat16_math.hpp"

bfloat16 rlibm_exp10(bfloat16 x) {
    float fInput = (float)x;

    // Take care of when result is 0
    if (fInput <= -40.5f) {
        return 0.0f;
    }

    // Take care of infinity case
    if (fInput >= 38.75f) {
        x.val = 0x7F80;
        return x;
    }
    
    // Take care of NaN
    if ((x.val & 0x7FFF) > 0x7F80) {
        return x;
    }
    
    if ((fInput >= -8.4686279296875e-04) && (fInput <= 1.68609619140625e-03)) {
        // The values in these range return 1.0.
        return 1.0f;
    }
    
    double xprime = fInput * 3.321928094887362181708567732130177319049835205078125;
    double intPart;
    double fracPart = modf(xprime, &intPart);
    if (fracPart < 0.0f) {
        fracPart += 1.0;
        intPart -= 1.0;
    }

    double y = 1.63907658064124488184187811157244141213595867156982421875e-02;
    y *= fracPart;
    y += 4.5758952998196537886865797872815164737403392791748046875e-02;
    y *= fracPart;
    y += 2.459833280009494360651700617381720803678035736083984375e-01;
    y *= fracPart;
    y += 6.9179740083422547325397999884444288909435272216796875e-01;
    y *= fracPart;
    y += 1.0000778485054981903346060789772309362888336181640625;
    
    return ldexp(y, intPart);
}
