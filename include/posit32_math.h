#include "softposit.h"
#include "stdint.h"
#include "math.h"

typedef union {
    double d;
    unsigned long long x;
} doubleX;

posit32_t rlibm_log2(posit32_t x);
posit32_t rlibm_log(posit32_t x);
posit32_t rlibm_log10(posit32_t x);
posit32_t rlibm_exp2(posit32_t x);
posit32_t rlibm_exp(posit32_t x);
posit32_t rlibm_exp10(posit32_t x);
posit32_t rlibm_sinh(posit32_t x);

posit32_t rlibm_cosh_1212(posit32_t x);
posit32_t rlibm_cosh_1412(posit32_t x);

posit32_t rlibm_cospi_99(posit32_t x);
posit32_t rlibm_cospi_910(posit32_t x);
posit32_t rlibm_cospi_914(posit32_t x);
posit32_t rlibm_cospi_119(posit32_t x);
posit32_t rlibm_cospi_1110(posit32_t x);
posit32_t rlibm_cospi_1114(posit32_t x);
posit32_t rlibm_cospi_139(posit32_t x);
posit32_t rlibm_cospi_1310(posit32_t x);
posit32_t rlibm_cospi_1314(posit32_t x);

posit32_t rlibm_sinpi_99(posit32_t x);
posit32_t rlibm_sinpi_913(posit32_t x);
posit32_t rlibm_sinpi_109(posit32_t x);
posit32_t rlibm_sinpi_1013(posit32_t x);
posit32_t rlibm_sinpi_129(posit32_t x);
posit32_t rlibm_sinpi_1213(posit32_t x);
