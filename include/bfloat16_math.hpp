#include <stdint.h>
#include "bfloat16.hpp"
#include <cstdint>

typedef union {
    double d;
    uint64_t x;
} dx;

typedef union {
    float f;
    unsigned int x;
} fx;

bfloat16 rlibm_exp(bfloat16);
bfloat16 rlibm_exp2(bfloat16);
bfloat16 rlibm_exp10(bfloat16);
bfloat16 rlibm_log(bfloat16);
bfloat16 rlibm_log2(bfloat16);
bfloat16 rlibm_log10(bfloat16);
bfloat16 rlibm_sinpi(bfloat16);
bfloat16 rlibm_cospi(bfloat16);
bfloat16 rlibm_sqrt(bfloat16);
bfloat16 rlibm_cbrt(bfloat16);
