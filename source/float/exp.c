#include "float_math.h"
#include "float_headers/Exp.h"
#include "float_headers/constants.h"
#include "math.h"

float rlibm_exp(float x) {
    floatX fx;
    fx.f = x;
    
    // Take care of special cases
    if (0x42b17218 <= fx.x && fx.x <= 0xb3000000) {
        if (fx.x <= 0x7F800000) return 1.0/0.0;
        if (fx.x < 0x80000000) return 0.0/0.0;
        return 1.0;
    }
    
    if (fx.x <= 0x337fffff) {
        return 1.0;
    }
    
    if (fx.x >= 0xc2cff218) {
        if (fx.x <= 0xFF800000) return 0.0;
        return 0.0/0.0;
    }
    
    // Perform range reduction
    double xp = x * 92.332482616893656768297660164535045623779296875;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    
    int M = N1 / 64;
    int J = N2;
    double R = x - N *
    0.01083042469624914509729318723429969395510852336883544921875;
    
    doubleX dX;
    dX.d = R;
    
    // Find the polynomial coefficients to use.
    const double* coeff;
    unsigned index = (dX.x & 0x03FFFFFFFFFFFFFF) >> 51;
    if (dX.x > 0x8000000000000000) coeff = expNegCoeffs[index];
    else coeff = expPosCoeffs[index];
    
    // Compute polynomial
    double y = coeff[4];
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
