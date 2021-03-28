#include "float_math.h"
#include "float_headers/Sinpi.h"
#include "float_headers/Cospi.h"
#include "float_headers/constants.h"

#define PI 3.141592653589793115997963468544185161590576171875

float rlibm_sinpi(float x) {
    floatX fX;
    fX.f = x;
    unsigned s = fX.x & 0x80000000;
    fX.x &= 0x7FFFFFFF;
    
    // Special cases:
    if (fX.x <= 0x33fc1537) {
        return PI * (double)x;
    }
    
    if (fX.x >= 0x4b000000) {
        if (fX.x >= 0x7F800000) {
            return 0.0f/0.0f;
        }
        return 0.0f;
    }
    
    double xp = fX.f * 512;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = N >> 8;
    double R;
    
    if (I & 0x1) {
        N2 = 255 - N2;
        R = (N + 1) * 0.001953125 - fX.f;
    } else R = fX.f - N * 0.001953125;
    
    if (I & 0x2) s ^= 0x80000000;
    
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
        
    fX.f = sinpiMBy512[N2] * cospiR + cospiMBy512[N2] * sinpiR;
    fX.x ^= s;
    
    return fX.f;
}
