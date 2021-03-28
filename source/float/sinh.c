#include "float_math.h"
#include "float_headers/Sinh.h"
#include "float_headers/Cosh.h"
#include "float_headers/constants.h"

#define CONST64BYLN2 92.332482616893656768297660164535045623779296875
#define LN2BY64 0.01083042469624914509729318723429969395510852336883544921875

float rlibm_sinh(float x) {
    floatX fx;
    fx.f = x;
    unsigned sign = fx.x & 0x80000000;
    fx.x &= 0x7FFFFFFF;
    
    // Take care of special cases
    if (fx.x <= 971544424) return x;
    
    if (fx.x >= 1119016189) {
        if (fx.x > 0x7F800000) return 0.0f/0.0f;
        return x / 0.0f;
    }
    
    // Perform range reduction
    double xp = fx.f * CONST64BYLN2;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int I = N1 / 64;
    double R = fx.f - N * LN2BY64;
    double R2 = R * R;
    
    double sinhHigh = sinhKLn2[I];
    double coshHigh = coshKLn2[I];
    double sinhMid = sinhKLn2By64[N2];
    double coshMid = coshKLn2By64[N2];
    
    double sinhHM = sinhHigh * coshMid + coshHigh * sinhMid;
    double coshHM = sinhHigh * sinhMid + coshHigh * coshMid;
    
    doubleX dX;
    dX.d = R;
    
    // Find the polynomial coefficients to use.
    unsigned long Index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 52lu;
    
    const double* sinhCoeff = Sinh[Index];
    const double* coshCoeff = Cosh[Index];
    
    // Compute sinh component
    double sinhL = sinhCoeff[2];
    sinhL *= R2;
    sinhL += sinhCoeff[1];
    sinhL *= R2;
    sinhL += sinhCoeff[0];
    sinhL *= R;
    
    // Compute cosh component
    double coshL = coshCoeff[2];
    coshL *= R2;
    coshL += coshCoeff[1];
    coshL *= R2;
    coshL += coshCoeff[0];
    
    // Perform output compensation
    fx.f = sinhHM * coshL + coshHM * sinhL;
    fx.x |= sign;
    return fx.f;
}
