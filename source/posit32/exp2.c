#include "posit32_math.h"
#include "posit32_headers/constants.h"
#include "posit32_headers/Exp2.h"
#include "math.h"

posit32_t rlibm_exp2(posit32_t x) {
    // Compute Special Case
    if (x.v >= 1801453569 && x.v <= 2493513727) {
        // 2^x rounds to minpos
        if (x.v > 0x80000000) {
            return castP32(0x00000001);
        }
        
        // 2^x rounds to maxpos
        if (x.v < 0x80000000) {
            return castP32(0x7FFFFFFF);
        }
        
        // Otherwise it's NaN
        return castP32(0x80000000);
    }
    
    // If x is between these values, 2^x rounds to 1.0
    if (x.v >= 4287163065 || x.v <= 9317006) {
        return castP32(0x40000000);
    }
    
    double d = convertP32ToDouble(x);
    
    // Range Reduction
    doubleX dX;
    double xp = d * 64;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int M = N1 / 64;
    dX.d = d - N * 0.015625;
    
    // Compute Polynomial
    // Is reduced input positive or negative?
    const double* coeff;
    if (dX.d >= 0.0) {
        // It's positive
        //unsigned posBitsSame = 6;
        //unsigned posN = 12
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 46;
        coeff = posExp2Coeffs[index];
    } else {
        // It's negative
        // negBitSame = 6;
        // negN = 10;
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 48;
        coeff = negExp2Coeffs[index];
    }
    
    // Compute polynomial
    double yp = coeff[3];
    yp *= dX.d;
    yp += coeff[2];
    yp *= dX.d;
    yp += coeff[1];
    yp *= dX.d;
    yp += coeff[0];
    
    // Output compensation
    double retVal = yp * ldexp(exp2JBy64[N2], M);
    return convertDoubleToP32(retVal);
}
