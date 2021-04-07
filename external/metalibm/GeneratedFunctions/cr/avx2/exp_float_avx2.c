/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_exp2.py --language c --accuracy cr --precision \
 *     float --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/exp_float_avx2.c --fname exp_float_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <math.h>
#include <emmintrin.h>
#include <ml_support_lib.h>


static const __m128 exp_float_avx2_cst = {128.0f}/*sse*/;
static const __m128 exp_float_avx2_cst1 = {8.0f}/*sse*/;
static const __m128i exp_float_avx2_cst2 = {INT32_C(9)}/*sse*/;
static const __m128i exp_float_avx2_cst3 = {INT32_C(0)}/*sse*/;
static const __m128 exp_float_avx2_cst4 = {0.125f}/*sse*/;
static const __m128 exp_float_avx2_c_1 = {0x1.62e43p-1f}/*sse*/;
static const __m128 exp_float_avx2_c_2 = {0x1.ebfbep-3f}/*sse*/;
static const __m128 exp_float_avx2_c_3 = {0x1.c6afbap-5f}/*sse*/;
static const __m128 exp_float_avx2_c_4 = {0x1.3b2a6cp-7f}/*sse*/;
static const __m128 exp_float_avx2_c_5 = {0x1.62554ap-10f}/*sse*/;
static const __m128 exp_float_avx2_c_6 = {0x1.45fcf6p-13f}/*sse*/;
static const __m128i exp_float_avx2_cst5 = {INT32_C(127)}/*sse*/;
static const __m128i exp_float_avx2_cst6 = {INT32_C(23)}/*sse*/;
static const __m128 exp_float_avx2_cst7 = {-126.0f}/*sse*/;
static const __m128 exp_float_avx2_cst8 = {INFINITY}/*sse*/;
static const __m128 exp_float_avx2_cst9 = {-149.0f}/*sse*/;
static const __m128i exp_float_avx2_cst10 = {INT32_C(127)}/*sse*/;
static const __m128i exp_float_avx2_cst11 = {INT32_C(-126)}/*sse*/;
static const __m128i exp_float_avx2_cst12 = {INT32_C(23)}/*sse*/;
static const __m128i exp_float_avx2_cst13 = {INT32_C(-126)}/*sse*/;
static const __m128i exp_float_avx2_cst14 = {INT32_C(127)}/*sse*/;
static const __m128i exp_float_avx2_cst15 = {INT32_C(23)}/*sse*/;
static const __m128 exp_float_avx2_cst16 = {0.0f}/*sse*/;
static const float exp_float_avx2_exp2_table[9]  = {
     0x1p0f, 0x1.172b84p0f, 0x1.306fep0f, 0x1.4bfdaep0f, 0x1.6a09e6p0f,
     0x1.8ace54p0f, 0x1.ae89fap0f, 0x1.d5818ep0f, 0x1p1f
};

float exp_float_avx2(float);
float exp_float_avx2(float x){
    float tmp;
    int oflow_test;
    __m128 tmp1;
    float vx_floor;
    __m128 tmp2;
    __m128 vx_r;
    __m128 tmp3;
    __m128 r_hi;
    float tmp4;
    int32_t r_hi_int;
    int32_t tmp5;
    int minmax_pred;
    int32_t tmp6;
    int32_t tmp7;
    int minmax_pred1;
    int32_t tmp8;
    __m128i tmp9;
    float* carg;
    __m128 hi_part_value;
    float tmp10;
    int32_t vx_int;
    __m128 tmp11;
    __m128 r_lo;
    __m128 pm_5;
    __m128 pa_5;
    __m128 pm_4;
    __m128 pa_4;
    __m128 pm_3;
    __m128 pa_3;
    __m128 pm_2;
    __m128 pa_2;
    __m128 tmp12;
    __m128 tmp13;
    __m128 poly;
    float tmp14;
    __m128i tmp15;
    __m128i tmp16;
    __m128i tmp17;
    int32_t tmp18;
    float exp_X;
    float tmp19;
    int uflow_test;
    int std_test;
    
    tmp = _mm_cvtss_f32(exp_float_avx2_cst);
    oflow_test = x >= tmp;
    tmp1 = _mm_set_ss(x);
    vx_floor = floorf(x);
    tmp2 = _mm_set_ss(vx_floor);
    vx_r = _mm_sub_ss(tmp1, tmp2);
    tmp3 = _mm_mul_ss(vx_r, exp_float_avx2_cst1);
    r_hi = _mm_round_ss(tmp3, tmp3, _MM_FROUND_TO_NEAREST_INT);
    tmp4 = _mm_cvtss_f32(r_hi);
    r_hi_int = tmp4;
    tmp5 = _mm_cvtsi128_si32(exp_float_avx2_cst2);
    minmax_pred = r_hi_int < tmp5;
    tmp6 = minmax_pred ? r_hi_int : tmp5;
    tmp7 = _mm_cvtsi128_si32(exp_float_avx2_cst3);
    minmax_pred1 = tmp6 > tmp7;
    tmp8 = minmax_pred1 ? tmp6 : tmp7;
    tmp9 = _mm_set1_epi32(tmp8);
    carg = (float*)&exp_float_avx2_exp2_table[_mm_cvtsi128_si32(tmp9)];
    hi_part_value = _mm_load_ss(carg);
    tmp10 = _mm_cvtss_f32(hi_part_value);
    vx_int = vx_floor;
    tmp11 = _mm_mul_ss(r_hi, exp_float_avx2_cst4);
    r_lo = _mm_sub_ss(vx_r, tmp11);
    pm_5 = _mm_mul_ss(r_lo, exp_float_avx2_c_6);
    pa_5 = _mm_add_ss(exp_float_avx2_c_5, pm_5);
    pm_4 = _mm_mul_ss(r_lo, pa_5);
    pa_4 = _mm_add_ss(exp_float_avx2_c_4, pm_4);
    pm_3 = _mm_mul_ss(r_lo, pa_4);
    pa_3 = _mm_add_ss(exp_float_avx2_c_3, pm_3);
    pm_2 = _mm_mul_ss(r_lo, pa_3);
    pa_2 = _mm_add_ss(exp_float_avx2_c_2, pm_2);
    tmp12 = _mm_mul_ss(r_lo, pa_2);
    tmp13 = _mm_add_ss(exp_float_avx2_c_1, tmp12);
    poly = _mm_mul_ss(r_lo, tmp13);
    tmp14 = _mm_cvtss_f32(poly);
    tmp15 = _mm_set1_epi32(vx_int);
    tmp16 = _mm_add_epi32(tmp15, exp_float_avx2_cst5);
    tmp17 = tmp16 << exp_float_avx2_cst6;
    tmp18 = _mm_cvtsi128_si32(tmp17);
    exp_X = float_from_32b_encoding(tmp18);
    tmp19 = _mm_cvtss_f32(exp_float_avx2_cst7);
    uflow_test = x < tmp19;
    std_test = oflow_test || uflow_test;

    if (__builtin_expect(std_test, 0)) {


        if (__builtin_expect(oflow_test, 0)) {
            float tmp0;

            tmp0 = _mm_cvtss_f32(exp_float_avx2_cst8);
            return tmp0;
        } else {
            float tmp0;
            int sub_test;

            tmp0 = _mm_cvtss_f32(exp_float_avx2_cst9);
            sub_test = x > tmp0;

            if (__builtin_expect(sub_test, 0)) {
                int32_t tmp20;
                int32_t tmp21;
                int32_t offset;
                __m128i tmp22;
                __m128i tmp23;
                __m128i tmp24;
                int32_t tmp25;
                float exp_offset;
                __m128 tmp26;
                __m128 tmp27;
                __m128i tmp28;
                __m128i tmp29;
                int32_t tmp30;
                float exp_min;
                __m128 tmp31;
                __m128 tmp32;
                __m128 tmp33;
                __m128 tmp34;
                __m128 tmp35;
                __m128 tmp36;
                float tmp37;

                tmp20 = _mm_cvtsi128_si32(exp_float_avx2_cst11);
                tmp21 = tmp20 - vx_int;
                offset =  - tmp21;
                tmp22 = _mm_set1_epi32(offset);
                tmp23 = _mm_add_epi32(tmp22, exp_float_avx2_cst10);
                tmp24 = tmp23 << exp_float_avx2_cst12;
                tmp25 = _mm_cvtsi128_si32(tmp24);
                exp_offset = float_from_32b_encoding(tmp25);
                tmp26 = _mm_set_ss(exp_offset);
                tmp27 = _mm_mul_ss(hi_part_value, tmp26);
                tmp28 = _mm_add_epi32(exp_float_avx2_cst13, exp_float_avx2_cst14);
                tmp29 = tmp28 << exp_float_avx2_cst15;
                tmp30 = _mm_cvtsi128_si32(tmp29);
                exp_min = float_from_32b_encoding(tmp30);
                tmp31 = _mm_set_ss(exp_min);
                tmp32 = _mm_mul_ss(tmp27, tmp31);
                tmp33 = _mm_mul_ss(tmp32, poly);
                tmp34 = _mm_mul_ss(hi_part_value, tmp26);
                tmp35 = _mm_mul_ss(tmp34, tmp31);
                tmp36 = _mm_add_ss(tmp33, tmp35);
                tmp37 = _mm_cvtss_f32(tmp36);
                return tmp37;
            } else {
                float tmp20;

                tmp20 = _mm_cvtss_f32(exp_float_avx2_cst16);
                return tmp20;
            }
        }
    } else {
        __m128 tmp0;
        __m128 tmp20;
        __m128 tmp21;
        __m128 tmp22;
        __m128 result;
        float tmp23;

        tmp0 = _mm_set_ss(exp_X);
        tmp20 = _mm_mul_ss(hi_part_value, tmp0);
        tmp21 = _mm_mul_ss(tmp20, poly);
        tmp22 = _mm_mul_ss(hi_part_value, tmp0);
        result = _mm_add_ss(tmp21, tmp22);
        tmp23 = _mm_cvtss_f32(result);
        return tmp23;
    }
}
