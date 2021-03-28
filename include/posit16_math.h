#include "softposit.h"
#include "stdint.h"
#include "math.h"

typedef union {
    double d;
    unsigned long long x;
} dint;

posit16_t rlibm_cospi(posit16_t x);
posit16_t rlibm_log(posit16_t x);
posit16_t rlibm_log2(posit16_t x);
posit16_t rlibm_log10(posit16_t x);
posit16_t rlibm_sinpi(posit16_t x);
posit16_t rlibm_sqrt(posit16_t x);
posit16_t rlibm_exp(posit16_t x);
posit16_t rlibm_exp2(posit16_t x);
posit16_t rlibm_exp10(posit16_t x);
