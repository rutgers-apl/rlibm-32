#include "float_math.h"
#include "float_headers/Exp10.h"
#include "float_headers/constants.h"
#include "math.h"

float rlibm_exp10(float x) {
    floatX fx;
    fx.f = x;
    
    // Take care of special cases
    if (0x421a209b <= fx.x && fx.x <= 0xb25e5bd8) {
        if (fx.x <= 0x7F800000) return 1.0/0.0;
        if (fx.x < 0x80000000) return 0.0/0.0;
        return 1.0;
    }
    
    if (fx.x <= 0x32de5bd8) {
        return 1.0;
    }
    
    if (fx.x >= 0xc2349e36) {
        if (fx.x <= 0xFF800000) return 0.0;
        return 0.0/0.0;
    }
    
    // Perform range reduction
    double xp = x * 2.12603398072791179629348334856331348419189453125e+02;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    
    int M = N1 / 64;
    int J = N2;
    double R = x - N *
    4.703593682249706219022922226713490090332925319671630859375e-03;
    
    doubleX dX;
    dX.d = R;
    
    // Find the polynomial coefficients to use.
    double y;
    if (dX.x > 0x8000000000000000) {
        unsigned index = (dX.x & 0x03FFFFFFFFFFFFFF) >> 52lu;
        const double* coeff = exp10NegCoeffs[index];
        
        y = coeff[4];
        y *= R;
        y += coeff[3];
        y *= R;
        y += coeff[2];
        y *= R;
        y += coeff[1];
        y *= R;
        y += coeff[0];
    }
    else {
        unsigned index = (dX.x & 0x03FFFFFFFFFFFFFF) >> 50lu;
        const double* coeff = exp10PosCoeffs[index];
        y = coeff[3];
        y *= R;
        y += coeff[2];
        y *= R;
        y += coeff[1];
        y *= R;
        y += coeff[0];
    }
    
    // Perform output compensation
    return y * ldexp(exp2JBy64[J], M);
}
