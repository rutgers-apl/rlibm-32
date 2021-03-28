#include "posit32_math.h"
#include "posit32_headers/constants.h"
#include "posit32_headers/ExpV2.h"
#include "math.h"

posit32_t rlibm_exp(posit32_t x) {
    // Compute Special Case
    if (x.v >= 1763486065 && x.v <= 2531481231) {
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
    if (x.v >= 4287627264 || x.v <= 8388607) {
        return castP32(0x40000000);
    }
    
    double d = convertP32ToDouble(x);
    
    // Range Reduction
    doubleX dX;
    double xp = d * (92.332482616893656768297660164535045623779296875 * 2.0);
    int N = (int)xp;
    int N2 = N % 128;
    if (N2 < 0) N2 += 128;
    int N1 = N - N2;
    int M = N1 / 128;
    dX.d = d - N *
    (0.01083042469624914509729318723429969395510852336883544921875 / 2.0);
    
    // Compute Polynomial
    // Is reduced input positive or negative?
    //printf("dX.d = %.100e\n", dX.d);
    const double* coeff;
    if (dX.d >= 0.0) {
        // It's positive
        //unsigned posBitsSame = 6;
        //unsigned posN = 12
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 46;
        //printf("index = %lu\n", index);
        coeff = posExpCoeffs[index];
        //printf("coeff[2] = %.100e\n", coeff[2]);
        //printf("coeff[1] = %.100e\n", coeff[1]);
        //printf("coeff[0] = %.100e\n", coeff[0]);
    } else {
        // It's negative
        // negBitSame = 6;
        // negN = 12;
        unsigned long index = (dX.x & 0x03FFFFFFFFFFFFFFlu) >> 46;
        //printf("index = %lu\n", index);
        coeff = negExpCoeffs[index];
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
    double retVal = yp * ldexp(exp2JBy128[N2], M);
    return convertDoubleToP32(retVal);
}
