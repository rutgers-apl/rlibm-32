#include "IntervalGen/IntGenForFloatTwoApprox.h"
#include "luts.h"
#include "math.h"

float IntervalGenerator2::MpfrCalculateFunction(float x) {
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_sinh(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator2::ComputeSpecialCase(float x, float& res) {
    floatX fx;
    fx.f = x;
    
    fx.x &= 0x7FFFFFFF;
    
    if (fx.x <= 971544424) {
        res = x;
        return true;
    }
    
    if (fx.x > 0x7F800000) {
        res = 0.0/0.0;
        return true;
    }
    
    if (fx.x >= 1119016189) {
        res = 1.0/0.0;
        return true;
    }
    
    return false;
}

double IntervalGenerator2::RangeReduction(float x) {
    double xp = x * CONST64BYLN2;
    int N = (int)xp;
    return x - N * LN2BY64;
}

double IntervalGenerator2::OutputCompensation(double x,
                                              double sinhp,
                                              double coshp) {
    double xp = x * CONST64BYLN2;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int I = N1 / 64;
    double sinhHM = sinhH[I] * coshM[N2] + coshH[I] * sinhM[N2];
    double coshHM = sinhH[I] * sinhM[N2] + coshH[I] * coshM[N2];
    
    return coshHM * sinhp + sinhHM * coshp;
}

void IntervalGenerator2::
SpecCaseRedInt(float x,
               double sinhLbGuess, bool& sinhLbSpec, double& sinhLbSpecVal,
               double sinhUbGuess, bool& sinhUbSpec, double& sinhUbSpecVal,
               double coshLbGuess, bool& coshLbSpec, double& coshLbSpecVal,
               double coshUbGuess, bool& coshUbSpec, double& coshUbSpecVal) {
    return;
}

bool IntervalGenerator2::GuessInitialLbUb(float x,
                                          double totalLB, double totalUB,
                                          double R,
                                          double& sinhLB, double& sinhUB,
                                          double& coshLB, double& coshUB) {
    doubleX dx, dx1, dx2;

    double xp = x * CONST64BYLN2;
    int N = (int)xp;
    int N2 = N % 64;
    if (N2 < 0) N2 += 64;
    int N1 = N - N2;
    int I = N1 / 64;
    double sinhHM = sinhH[I] * coshM[N2] + coshH[I] * sinhM[N2];
    double coshHM = sinhH[I] * sinhM[N2] + coshH[I] * coshM[N2];
    
    double A = cosh(R);
    double B = sinh(R);
    
    // sinh(x) = sinhHM * cosh(R) + coshHM * sinh(R);
    // SX = sinh(x), SHM = sinhHM, CHM = coshHM
    // A = cosh(R), B = sinh(R)
    // SX = SHM * A + CHM * B
    // Now I want lb and ub of A and lb and ub of B.
    // The question is, can we have a multipler M for A:
    // totalLB = SHM * A * M1 + CHM * B * M1;
    // totalLB = (SHM * A + CHM * B) * M1;
    // M1 = totalLB / (SHM * A + CHM * B)
    double M1 = totalLB / (sinhHM * A + coshHM * B);
    coshLB = A * M1;
    sinhLB = B * M1;

    // If SHM == 0, then cosh(R) can be any value.
    if (sinhHM == 0) {
        dx.x = 0xFFEFFFFFFFFFFFFF;
        coshLB = dx.d;
    }
    
    // If CHM == 0, then sinh(R) can be any value.
    if (coshHM == 0) {
        dx.x = 0xFFEFFFFFFFFFFFFF;
        sinhLB = dx.d;
    }
    
    // Reconstruct sinh(x) using sinhHM * coshLB + coshHM * sinhLB and make
    // sure that we find the smallest sinhLB and coshLB boundary.
    unsigned long step = 0x1000000000000;
    while (step > 0) {
        dx1.d = coshLB;
        dx2.d = sinhLB;
        
        if (sinhHM != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
        
        if (coshHM != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
        
        double recon = sinhHM * dx1.d + coshHM * dx2.d;
        
        if (recon >= totalLB) {
            coshLB = dx1.d;
            sinhLB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    
    // Reconstruct sinh(x) using sinhHM * coshLB + coshHM * sinhLB and make
    // sure that sinhLB and coshLB makes larger than totalLB.
    double recon = sinhHM * coshLB + coshHM * sinhLB;

    while (recon < totalLB) {
        if (sinhHM != 0) {
            dx.d = coshLB;
            if (dx.d >= 0) dx.x++;
            else dx.x--;
            coshLB = dx.d;
        }
        if (coshHM != 0) {
            dx.d = sinhLB;
            if (dx.d >= 0) dx.x++;
            else dx.x--;
            sinhLB = dx.d;
        }
        recon = sinhHM * coshLB + coshHM * sinhLB;
    }
    
    
    
    // sinh(x) = sinhHM * cosh(R) + coshHM * sinh(R);
    // SX = sinh(x), SHM = sinhHM, CHM = coshHM
    // A = cosh(R), B = sinh(R)
    // SX = SHM * A + CHM * B
    // totalUB = SHM * A * M2 + CHM * B * M2;
    // totalUB = (SHM * A + CHM * B) * M2;
    // M2 = totalUB / (SHM * A + CHM * B)
    double M2 = totalUB / (sinhHM * A + coshHM * B);
    coshUB = A * M2;
    sinhUB = B * M2;
    
    // If SHM == 0, then cosh(R) can be any value.
    if (sinhHM == 0) {
        dx.x = 0x7FEFFFFFFFFFFFFF;
        coshUB = dx.d;
    }
    
    // If CHM == 0, then sinh(R) can be any value.
    if (coshHM == 0) {
        dx.x = 0x7FEFFFFFFFFFFFFF;
        sinhUB = dx.d;
    }
    
    // Reconstruct sinh(x) using sinhHM * coshUB + coshHM * sinhUB and make
    // sure that we find the largest sinhUB and coshUB boundary.
    step = 0x1000000000000;
    while (step > 0) {
        dx1.d = coshUB;
        dx2.d = sinhUB;
        
        if (sinhHM != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        if (coshHM != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
        
        double recon = sinhHM * dx1.d + coshHM * dx2.d;
        
        if (recon <= totalUB) {
            coshUB = dx1.d;
            sinhUB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    
    // Reconstruct sinh(x) using sinhHM * coshLB + coshHM * sinhLB and make
    // sure that sinhLB and coshLB makes larger than totalLB.
    recon = sinhHM * coshUB + coshHM * sinhUB;

    while (recon > totalUB) {
        if (sinhHM != 0) {
            dx.d = coshUB;
            if (dx.d >= 0) dx.x--;
            else dx.x++;
            coshUB = dx.d;
        }
        if (coshHM != 0) {
            dx.d = sinhUB;
            if (dx.d >= 0) dx.x--;
            else dx.x++;
            sinhUB = dx.d;
        }
        recon = sinhHM * coshUB + coshHM * sinhUB;
    }
    return true;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 200);
    
    if (argc != 3) {
        printf("Usage: %s <reduced sinh file> <reduced cosh file>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator2 SinhIntGen;
    SinhIntGen.CreateReducedIntervalFile(0x0, 0x80000000, argv[1], argv[2]);
    
    return 0;
}
