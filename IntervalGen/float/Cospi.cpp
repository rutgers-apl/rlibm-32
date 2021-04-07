#include "IntervalGen/IntGenForFloatTwoApprox.h"
#include "luts.h"
#include "math.h"

float IntervalGenerator2::MpfrCalculateFunction(float x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, x, MPFR_RNDN);
    mpfr_cos(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator2::ComputeSpecialCase(float x, float& res) {
   floatX fX;
   fX.f = x;
   fX.x &= 0x7FFFFFFF;
   
   // Special cases:
   // If x is smaller than 0x38a2f983, then it's 1.0f
   if (fX.x <= 0x38a2f983) {
       res = 1.0f;
       return true;
   }
   
   if (fX.x >= 0x4b000000) {
       // If x >= 0x7F800000, then result is NaN
       if (fX.x >= 0x7F800000) {
           res = 0.0f/0.0f;
           return true;
       }
       // If x >= 2^24, then result is always 1.0f
       if (fX.x >= 0x4b800000) {
           res = 1.0f;
           return true;
       }
       // If x >= 2^23, then if x is even, then 1.0f
       if ((fX.x & 0x1) == 0) {
           res = 1.0f;
           return true;
       }
       // Otherwise, then -1.0f
       res = -1.0f;
       return true;
   }
   
   return false;
}

double IntervalGenerator2::RangeReduction(float x) {
    floatX fX;
    fX.f = x;
    fX.x &= 0x7FFFFFFF;
    
    // Range Reduction
    double xp = fX.f * 512.0;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = (N >> 8) + 1;
    double R, cospiM, sinpiM;
    unsigned sign = (I & 0x2) ? 0x80000000 : 0;
    
    if (I & 1) {
      if (N2 == 0) {
	R = fX.f - N * 0.001953125;
      }
      else {
	N2++;
	R = (N + 1) * 0.001953125 - fX.f;
      }
    } else {
      R = fX.f - N * 0.001953125;
    }
    
    return R;
}

double IntervalGenerator2::OutputCompensation(double x,
                                              double sinpip,
                                              double cospip) {
    floatX fX;
    fX.f = x;
    fX.x &= 0x7FFFFFFF;
    
    // Range Reduction
    double xp = fX.f * 512.0;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = (N >> 8) + 1;
    double R, cospiM, sinpiM;
    unsigned sign = (I & 0x2) ? 0x80000000 : 0;
    
    if (I & 1) {
      if (N2 == 0) {
        R = fX.f - N * 0.001953125;
        cospiM = 1.0;
        sinpiM = 0.0;
      }
      else {
        N2++;
        R = (N + 1) * 0.001953125 - fX.f;
        cospiM = sinpiMBy512[256 - N2];
        sinpiM = cospiMBy512[256 - N2];
      }
    } else {
      R = fX.f - N * 0.001953125;
      cospiM = sinpiMBy512[N2];
      sinpiM = cospiMBy512[N2];
    }
    
    fX.f = cospiM * cospip + sinpiM * sinpip;
    fX.x ^= sign;
    return fX.f;
}

void IntervalGenerator2::
SpecCaseRedInt(float x,
               double sinpiLbGuess, bool& sinpiLbSpec, double& sinpiLbSpecVal,
               double sinpiUbGuess, bool& sinpiUbSpec, double& sinpiUbSpecVal,
               double cospiLbGuess, bool& cospiLbSpec, double& cospiLbSpecVal,
               double cospiUbGuess, bool& cospiUbSpec, double& cospiUbSpecVal) {
    return;
}

bool IntervalGenerator2::GuessInitialLbUb(float x,
                                          double totalLB, double totalUB,
                                          double R,
                                          double& sinpiLB, double& sinpiUB,
                                          double& cospiLB, double& cospiUB) {
    
    doubleX dx, dx1, dx2;
    floatX fX;
    fX.f = x;
    fX.x &= 0x7FFFFFFF;
    
    // Range Reduction
    double xp = fX.f * 512.0;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = (N >> 8) + 1;
    double cospiM, sinpiM;
    unsigned sign = (I & 0x2) ? 0x80000000 : 0;
    
    if (I & 1) {
        if (N2 == 0) {
            cospiM = 1.0;
            sinpiM = 0.0;
        }
        else {
            N2++;
            cospiM = sinpiMBy512[256 - N2];
            sinpiM = cospiMBy512[256 - N2];
        }
    } else {
        cospiM = sinpiMBy512[N2];
        sinpiM = cospiMBy512[N2];
    }
    
    // I can tell here whether sign should be flipped or not
    if (sign != 0) {
        double temp = totalLB;
        totalLB = -totalUB;
        totalUB = -temp;
    }

    double cospiR = cos(R * PI);
    double sinpiR = sin(R * PI);
    double M1 = totalLB / (cospiM * cospiR + sinpiM * sinpiR);
    double M2 = totalUB / (cospiM * cospiR + sinpiM * sinpiR);
    
    if (cospiM == 0) {
        cospiLB = -1.0e300;
        cospiUB = 1.0e300;
    } else if (cospiR == 0) {
        cospiLB = 0.0;
        cospiUB = 0.0;
    } else {
        cospiLB = cospiR * M1;
        cospiUB = cospiR * M2;
    }
    
    if (sinpiM == 0) {
        sinpiLB = -1.0e300;
        sinpiUB = 1.0e300;
    } else if (sinpiR == 0) {
        sinpiLB = 0.0;
        sinpiUB = 0.0;
    } else {
        sinpiLB = sinpiR * M1;
        sinpiUB = sinpiR * M2;
    }

    if (cospiM * cospiR + sinpiM * sinpiR == 0) {
        return true;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that sinpiLB and cospiLB makes larger than totalLB.
    double recon = sinpiM * sinpiLB + cospiM * cospiLB;

    while (recon < totalLB) {
        //printf("hm1\n");
        if (cospiM != 0 && cospiLB != 0) {
            dx.d = cospiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            cospiLB = dx.d;
        }
        if (sinpiM != 0 && sinpiLB != 0) {
            dx.d = sinpiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            sinpiLB = dx.d;
        }
        recon = sinpiM * sinpiLB + cospiM * cospiLB;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that we find the smallest sinpiLB and cospiLB boundary.
    unsigned long step = 0x100000000000;
    while (step > 0) {
        //printf("hm2\n");
        dx1.d = cospiLB;
        dx2.d = sinpiLB;
        
        if (cospiM != 0 && cospiLB != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
          
        if (sinpiM != 0 && sinpiLB != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon >= totalLB) {
            cospiLB = dx1.d;
            sinpiLB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }

    // I should try to make cospiLB and sinpiLB lower individually.
    step = 0x100000000000;
    while (step > 0) {
        //printf("hm2\n");
        dx1.d = cospiLB;
          
        if (cospiM != 0 && cospiLB != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon >= totalLB) {
            cospiLB = dx1.d;
        }
        else if (step > 0) step /= 2;
    }

    step = 0x100000000000;
    while (step > 0) {
        dx2.d = sinpiLB;
        
        if (sinpiM != 0 && sinpiLB != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon >= totalLB) {
            sinpiLB = dx2.d;
        } else if (step > 0) step /= 2;
    }

    // Reconstruct cospi(x) using sinpiM * sinpiUB + cospiM * cospiUB and make
    // sure that sinpiLB and cospiLB makes smaller than totalUB.
    recon = sinpiM * sinpiUB + cospiM * cospiUB;

    while (recon > totalUB) {
        if (cospiM != 0 && cospiUB != 0) {
            dx.d = cospiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            cospiUB = dx.d;
        }
        if (sinpiM != 0 && sinpiUB != 0) {
            dx.d = sinpiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            sinpiUB = dx.d;
        }
        recon = sinpiM * sinpiUB + cospiM * cospiUB;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiUB + cospiHM * sinpiUB and make
    // sure that we find the largest sinpiUB and cospiUB boundary.
    step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiUB;
        dx2.d = sinpiUB;
        
        if (cospiM != 0 && cospiUB != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        if (sinpiM != 0 && sinpiUB != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon <= totalUB) {
            cospiUB = dx1.d;
            sinpiUB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }

    // I should try to make CospiUB and sinpiUB larger individually
    step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiUB;
        
        if (cospiM != 0 && cospiUB != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon <= totalUB) {
            cospiUB = dx1.d;
        }
        else if (step > 0) step /= 2;
    }

    step = 0x100000000000;
    while (step > 0) {
        dx2.d = sinpiUB;
        
        if (sinpiM != 0 && sinpiUB != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon <= totalUB) {
            sinpiUB = dx2.d;
        }
        else if (step > 0) step /= 2;
    }
    
    return true;
    
}


int main(int argc, char** argv) {
    mpfr_init2(mval, 500);
    
    if (argc != 3) {
        printf("Usage: %s <reduced sinpi file> <reduced cospi file>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator2 SinpiIntGen;
    SinpiIntGen.CreateReducedIntervalFile(0x0, 0x40000001llu, argv[1], argv[2]);
    return 0;
}
