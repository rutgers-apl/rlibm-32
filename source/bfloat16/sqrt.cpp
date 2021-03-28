#include "bfloat16_math.hpp"

bfloat16 rlibm_sqrt(bfloat16 x) {
    
    // If x == 0, then it should be 0
    if (x.val == 0x0 || x.val == 0x8000) {
        return x;
    }

    // If x == inf, then it should be infinity
    if (x.val == 0x7f80) {
        return x;
    }
    
    // If x == NaN or negative, then it should be NaN
    if (x.val > 0x7F80) {
        x.val = 0xFFFF;
        return x;
    }
    
    
    // Extract exponent and mantissa (where mantissa is between [1, 4))
    int m;
    float fx = frexpf((float)x, &m);
    fx *= 2.0;
    m--;
    
    if ((m & 0x1) == 1) {
        fx *= 2.0;
        m--;
    }
    
    m >>= 1;
    
    // Now compute polynomial
    double y = -3.0848915765425755954043385287377532222308218479156494140625e-03;
    y *= fx;
    y += 3.800384608453956369888970812098705209791660308837890625e-02;
    y *= fx;
    y += -1.99230719933062794257949690290843136608600616455078125e-01;
    y *= fx;
    y += 7.923315194006106398916244870633818209171295166015625e-01;
    y *= fx;
    y += 3.7202139260816802224240973373525775969028472900390625e-01;
    
    return ldexp(y, m);
}
