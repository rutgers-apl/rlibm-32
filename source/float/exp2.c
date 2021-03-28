#include "float_math.h"
#include "float_headers/Exp2.h"
#include "float_headers/constants.h"
#include "math.h"

float rlibm_exp2(float x) {
    floatX fx;
    fx.f = x;
    
    // Take care of special cases
    if (0x43000000 <= fx.x && fx.x <= 0xb338aa3b) {
        if (fx.x <= 0x7F800000) return 1.0/0.0;
        if (fx.x < 0x80000000) return 0.0/0.0;
        return 1.0;
    }
    
    if (fx.x <= 0x33b8aa3a) {
        return 1.0;
    }
    
    if (fx.x >= 0xc3160000) {
        if (fx.x <= 0xFF800000) return 0.0;
        return 0.0/0.0;
    }
    
    // Perform range reduction
    double xp = x * 64;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    
    int M = N1 / 64;
    int J = N2;
    double R = x - N * 0.015625;
    
    double y;
    
    doubleX dX;
    dX.d = R;
    
    // Find the polynomial coefficients to use.
    const double* coeff;
    if (dX.x > 0x8000000000000000) {
        unsigned long index = (dX.x & 0x01FFFFFFFFFFFFFFlu) >> 53lu;
        coeff = exp2NegCoeffs[index];
    }
    else {
        unsigned long index = (dX.x & 0x01FFFFFFFFFFFFFFlu) >> 54lu;
        coeff = exp2PosCoeffs[index];
    }
    
    // Compute polynomial
    y = coeff[4];
    y *= R;
    y += coeff[3];
    y *= R;
    y += coeff[2];
    y *= R;
    y += coeff[1];
    y *= R;
    y += coeff[0];
    
    // Perform output compensation
    return y * ldexp(exp2JBy64[J], M);
}
