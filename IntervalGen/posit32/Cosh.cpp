#include "IntervalGen/IntGenForPosit32TwoApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator2::MpfrCalculateFunction(double x) {
    mpfr_set_d(mval, x, MPFR_RNDN);
    mpfr_cosh(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
    
    // If you want to run this faster, you can try this. Use it at your own risk
    /*
    double res = cosh((double)x);
    return (float)res;
     */
}

bool IntervalGenerator2::ComputeSpecialCase(posit32 x, posit32& res) {
    if (x.value == 0x80000000) {
        res.value = 0x80000000;
        return true;
    }

    if (x.value <= 107612646) {
        res.value = 0x40000000;
        return true;
    }
    
    if (x.value >= 1764212883) {
        res.value = 0x7FFFFFFF;
        return true;
    }
    
    return false;
}

double IntervalGenerator2::RangeReduction(double x) {
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
    
    if (x == 2.283726425957866013050079345703125e-04) {
        printf("This INPUT!!!\n");
        printf("sinhHM = %.100e\n", sinhHM);
        printf("coshHM = %.100e\n", coshHM);
    }
    
    double res = sinhHM * sinhp + coshHM * coshp;
    return res;
}

void IntervalGenerator2::
SpecCaseRedInt(double x,
               double sinhLbGuess, bool& sinhLbSpec, double& sinhLB,
               double sinhUbGuess, bool& sinhUbSpec, double& sinhUB,
               double coshLbGuess, bool& coshLbSpec, double& coshLB,
               double coshUbGuess, bool& coshUbSpec, double& coshUB) {
    return;
}

bool IntervalGenerator2::GuessInitialLbUb(double x,
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
    
    // cosh(x) = sinhHM * sinh(R) + coshHM * cosh(R);
    // SX = sinh(x), SHM = sinhHM, CHM = coshHM
    // A = cosh(R), B = sinh(R)
    // SX = SHM * B + CHM * A
    // Now I want lb and ub of A and lb and ub of B.
    // The question is, can we have a multipler M for A:
    // totalLB = SHM * B * M1 + CHM * A * M1;
    // totalLB = (SHM * A + CHM * A) * M1;
    // M1 = totalLB / (SHM * B + CHM * A)
    double M1 = totalLB / (sinhHM * B + coshHM * A);
    coshLB = A * M1;
    sinhLB = B * M1;

    // If SHM == 0, then cosh(R) can be any value.
    if (sinhHM == 0) {
        dx.x = 0xFFEFFFFFFFFFFFFF;
        sinhLB = dx.d;
    }
    
    // If CHM == 0, then sinh(R) can be any value.
    if (coshHM == 0) {
        dx.x = 0xFFEFFFFFFFFFFFFF;
        coshLB = dx.d;
    }
    
    // Reconstruct sinh(x) using sinhHM * sinhLB + coshHM * coshLB and make
    // sure that we find the smallest sinhLB and coshLB boundary.
    unsigned long step = 0x1000000000000;
    while (step > 0) {
        dx1.d = coshLB;
        dx2.d = sinhLB;
        
        if (coshHM != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
        
        if (sinhHM != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
        
        double recon = sinhHM * dx2.d + coshHM * dx1.d;
        
        if (recon >= totalLB) {
            coshLB = dx1.d;
            sinhLB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    
    // Reconstruct sinh(x) using sinhHM * sinhLB + coshHM * coshLB and make
    // sure that sinhLB and coshLB makes larger than totalLB.
    double recon = sinhHM * sinhLB + coshHM * coshLB;

    while (recon < totalLB) {
        if (coshHM != 0) {
            dx.d = coshLB;
            if (dx.d >= 0) dx.x++;
            else dx.x--;
            coshLB = dx.d;
        }
        if (sinhHM != 0) {
            dx.d = sinhLB;
            if (dx.d >= 0) dx.x++;
            else dx.x--;
            sinhLB = dx.d;
        }
        recon = sinhHM * sinhLB + coshHM * coshLB;
    }
    
    
    
    // cosh(x) = sinhHM * sinh(R) + coshHM * cosh(R);
    // SX = sinh(x), SHM = sinhHM, CHM = coshHM
    // A = cosh(R), B = sinh(R)
    // SX = SHM * B + CHM * A
    // totalUB = SHM * B * M2 + CHM * A * M2;
    // totalUB = (SHM * B + CHM * A) * M2;
    // M2 = totalUB / (SHM * B + CHM * A)
    double M2 = totalUB / (sinhHM * B + coshHM * A);
    coshUB = A * M2;
    sinhUB = B * M2;
    
    // If SHM == 0, then cosh(R) can be any value.
    if (coshHM == 0) {
        dx.x = 0x7FEFFFFFFFFFFFFF;
        coshUB = dx.d;
    }
    
    // If CHM == 0, then sinh(R) can be any value.
    if (sinhHM == 0) {
        dx.x = 0x7FEFFFFFFFFFFFFF;
        sinhUB = dx.d;
    }
    
    // Reconstruct sinh(x) using sinhHM * sinhUB + coshHM * coshUB and make
    // sure that we find the largest sinhUB and coshUB boundary.
    step = 0x1000000000000;
    while (step > 0) {
        dx1.d = coshUB;
        dx2.d = sinhUB;
        
        if (coshHM != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        if (sinhHM != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
        
        double recon = sinhHM * dx2.d + coshHM * dx1.d;
        
        if (recon <= totalUB) {
            coshUB = dx1.d;
            sinhUB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    
    // Reconstruct sinh(x) using sinhHM * sinhLB + coshHM * coshLB and make
    // sure that sinhLB and coshLB makes larger than totalLB.
    recon = sinhHM * sinhUB + coshHM * coshUB;

    while (recon > totalUB) {
        if (coshHM != 0) {
            dx.d = coshUB;
            if (dx.d >= 0) dx.x--;
            else dx.x++;
            coshUB = dx.d;
        }
        if (sinhHM != 0) {
            dx.d = sinhUB;
            if (dx.d >= 0) dx.x--;
            else dx.x++;
            sinhUB = dx.d;
        }
        recon = sinhHM * sinhUB + coshHM * coshUB;
    }
    return true;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 200);
    
    if (argc != 3) {
        printf("Usage: %s <reduced sinh file> <reduced cosh file>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator2 CoshIntGen;
    CoshIntGen.CreateReducedIntervalFile(0x0, 0x80000000, argv[1], argv[2]);
    
    return 0;
}
