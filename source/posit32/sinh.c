#include "posit32_math.h"
#include "posit32_headers/SinhForSinh.h"
#include "posit32_headers/CoshForSinh.h"
#include "posit32_headers/constants.h"

#define CONST64BYLN2 92.332482616893656768297660164535045623779296875
#define LN2BY64 0.01083042469624914509729318723429969395510852336883544921875

posit32_t rlibm_sinh(posit32_t x) {
    posit32_t temp = x;
    bool sign = ((unsigned)x.v > 0x80000000) ? true : false;
    if (x.v > 0x80000000) x.v = -x.v;
    
    // Take care of special cases
    if (x.v == 0x80000000) return x;
    
    if (x.v <= 139073532) return temp;
    
    if (x.v >= 1764212883) {
        if (sign) x.v = 0x80000001;
        else  x.v = 0x7FFFFFFF;
        return x;
    }
    
    // Perform range reduction
    double d = convertP32ToDouble(x);
    
    double xp = d * CONST64BYLN2;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int I = N1 / 64;
    double R =  d - N * LN2BY64;
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
    unsigned long Index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 44lu;
    
    const double* sinhCoeff = SinhForSinhCoeffs[Index];
    const double* coshCoeff = CoshForSinhCoeffs[Index];
    
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
    posit32_t retVal = convertDoubleToP32(sinhHM * coshL + coshHM * sinhL);
    if (sign) retVal.v = -retVal.v;
    return retVal;
}
