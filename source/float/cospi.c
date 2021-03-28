#include "float_math.h"
#include "float_headers/Sinpi.h"
#include "float_headers/Cospi.h"
#include "float_headers/constants.h"
#include "stdio.h"

float rlibm_cospi(float x) {
    floatX fX;
    fX.f = x;
    fX.x &= 0x7FFFFFFF;
    
    // Special cases:
    // If x is smaller than 0x38a2f983, then it's 1.0f
    if (fX.x <= 0x38a2f983) {
        return 1.0f;
    }
    
    if (fX.x >= 0x4b000000) {
        // If x >= 0x7F800000, then result is NaN
        if (fX.x >= 0x7F800000) return 0.0f/0.0f;
        // If x >= 2^24, then result is always 1.0f
        if (fX.x >= 0x4b800000) return 1.0f;
        // If x >= 2^23, then if x is even, then 1.0f
        if ((fX.x & 0x1) == 0) return 1.0f;
        // Otherwise, then -1.0f
        return -1.0f;
    }
    
    // Range Reduction
    double xp = fX.f * 512.0;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = (N >> 8) + 1;
    double R, cospiM, sinpiM;
    unsigned s = (I & 0x2) ? 0x80000000 : 0;

    if (I & 1) {
        if (N2 == 0) {
            R = fX.f - N * 0.001953125;
            cospiM = 1.0;
            sinpiM = 0.0;
        }
        else {
            N2++;
            R = (N + 1) * 0.001953125 - fX.f;
            cospiM = sinpiMBy512[256 - N2];
            sinpiM = cospiMBy512[256 - N2];
        }
    } else {
        R = fX.f - N * 0.001953125;
        cospiM = sinpiMBy512[N2];
        sinpiM = cospiMBy512[N2];
    }
    
    double R2 = R * R;
    double cospiR, sinpiR;
        
    sinpiR = S2;
    sinpiR *= R2;
    sinpiR += S1;
    sinpiR *= R2;
    sinpiR += S0;
    sinpiR *= R;
    
    cospiR = C2;
    cospiR *= R2;
    cospiR += C1;
    cospiR *= R2;
    cospiR += C0;

    fX.f = cospiM * cospiR + sinpiM * sinpiR;
    fX.x ^= s;
    
    return fX.f;
}
