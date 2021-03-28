#include "posit32_math.h"
#include "posit32_headers/constants.h"
#include "posit32_headers/Exp10.h"
#include "math.h"

posit32_t rlibm_exp10(posit32_t x) {
    // Compute Special Case
    if (x.v >= 1685106804 && x.v <= 2609860492) {
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
    if (x.v >= 4288951429 || x.v <= 7064443) {
        return castP32(0x40000000);
    }
    
    double d = convertP32ToDouble(x);
    
    // Range Reduction
    doubleX dX;
    double xp = d * 2.12603398072791179629348334856331348419189453125e+02;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int M = N1 / 64;
    dX.d = d - N *
    4.703593682249706219022922226713490090332925319671630859375e-03;
    
    // Compute Polynomial
    // Is reduced input positive or negative?
    //printf("dX.d = %.100e\n", dX.d);
    const double* coeff;
    double yp = 0;
    if (dX.d >= 0.0) {
        // It's positive
        //unsigned posBitsSame = 6;
        //unsigned posN = 13
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 45;
        coeff = posExp10Coeffs[index];
        yp = coeff[2];
        yp *= dX.d;
        yp += coeff[1];
        yp *= dX.d;
        yp += coeff[0];
    } else {
        // It's negative
        // negBitSame = 6;
        // negN = 13;
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 45;
        coeff = negExp10Coeffs[index];
        yp = coeff[3];
        yp *= dX.d;
        yp += coeff[2];
        yp *= dX.d;
        yp += coeff[1];
        yp *= dX.d;
        yp += coeff[0];
    }
    
    // Output compensation
    double retVal = yp * ldexp(exp2JBy64[N2], M);
    return convertDoubleToP32(retVal);
}
