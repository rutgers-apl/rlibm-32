/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_cosh.py --language c --accuracy cr --precision \
 *     float --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/cosh_float_avx2.c --fname cosh_float_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <ml_support_lib.h>


static const __m128 cosh_float_avx2_cst = {0x1.65a9f8p6f}/*sse*/;
static const __m128 cosh_float_avx2_cst1 = {INFINITY}/*sse*/;
static const __m128 cosh_float_avx2_log2_hi_value = {0x1.63p-4f}/*sse*/;
static const __m128 cosh_float_avx2_inv_log2 = {0x1.715476p3f}/*sse*/;
static const __m128 cosh_float_avx2_log2_lo_value = {-0x1.bd0106p-16f}/*sse*/;
static const __m128 cosh_float_avx2_c_1 = {0x1.fffffcp-1f}/*sse*/;
static const __m128 cosh_float_avx2_c_2 = {0x1.fffffcp-2f}/*sse*/;
static const __m128 cosh_float_avx2_c_3 = {0x1.557c08p-3f}/*sse*/;
static const __m128 cosh_float_avx2_c_4 = {0x1.557c38p-5f}/*sse*/;
static const __m128i cosh_float_avx2_cst2 = {INT32_C(8)}/*sse*/;
static const __m128i cosh_float_avx2_cst3 = {INT32_C(8)}/*sse*/;
static const __m128i cosh_float_avx2_cst4 = {INT32_C(2)}/*sse*/;
static const __m128i cosh_float_avx2_cst5 = {INT32_C(3)}/*sse*/;
static const __m128i cosh_float_avx2_cst6 = {INT32_C(127)}/*sse*/;
static const __m128i cosh_float_avx2_cst7 = {INT32_C(3)}/*sse*/;
static const __m128i cosh_float_avx2_cst8 = {INT32_C(1)}/*sse*/;
static const __m128i cosh_float_avx2_cst9 = {INT32_C(-126)}/*sse*/;
static const __m128i cosh_float_avx2_cst10 = {INT32_C(23)}/*sse*/;
static const __m128 cosh_float_avx2_c_11 = {0x1.fffffcp-1f}/*sse*/;
static const __m128 cosh_float_avx2_c_21 = {0x1.fffffcp-2f}/*sse*/;
static const __m128 cosh_float_avx2_c_31 = {0x1.557c08p-3f}/*sse*/;
static const __m128 cosh_float_avx2_c_41 = {0x1.557c38p-5f}/*sse*/;
static const __m128i cosh_float_avx2_cst11 = {INT32_C(0)}/*sse*/;
static const __m128i cosh_float_avx2_cst12 = {INT32_C(1)}/*sse*/;
static const __m128i cosh_float_avx2_cst13 = {INT32_C(127)}/*sse*/;
static const __m128i cosh_float_avx2_cst14 = {INT32_C(1)}/*sse*/;
static const __m128i cosh_float_avx2_cst15 = {INT32_C(-126)}/*sse*/;
static const __m128i cosh_float_avx2_cst16 = {INT32_C(23)}/*sse*/;
static const float cosh_float_avx2_exp2_table[16][4]  = {
    { 0x1p0f, 0.0f, 0x1p0f, 0.0f},
    { 0x1.d582p-1f, -0x1.c8c116p-19f, 0x1.172cp0f, -0x1.f0e0acp-18f},
    { 0x1.ae8ap-1f, -0x1.9a94b2p-23f, 0x1.307p0f, -0x1.f5ce48p-20f},
    { 0x1.8acep-1f, 0x1.508aa8p-19f, 0x1.4bfep0f, -0x1.4ab276p-18f},
    { 0x1.6a0ap-1f, -0x1.9980c4p-21f, 0x1.6a0ap0f, -0x1.9980c4p-20f},
    { 0x1.4bfep-1f, -0x1.4ab276p-19f, 0x1.8acep0f, 0x1.508aa8p-18f},
    { 0x1.307p-1f, -0x1.f5ce48p-21f, 0x1.ae8ap0f, -0x1.9a94b2p-22f},
    { 0x1.172cp-1f, -0x1.f0e0acp-19f, 0x1.d582p0f, -0x1.c8c116p-18f},
    { 0x1p0f, 0.0f, 0x1p0f, 0.0f},
    { 0x1.d582p-1f, -0x1.c8c116p-19f, 0x1.172cp0f, -0x1.f0e0acp-18f},
    { 0x1.ae8ap-1f, -0x1.9a94b2p-23f, 0x1.307p0f, -0x1.f5ce48p-20f},
    { 0x1.8acep-1f, 0x1.508aa8p-19f, 0x1.4bfep0f, -0x1.4ab276p-18f},
    { 0x1.6a0ap-1f, -0x1.9980c4p-21f, 0x1.6a0ap0f, -0x1.9980c4p-20f},
    { 0x1.4bfep-1f, -0x1.4ab276p-19f, 0x1.8acep0f, 0x1.508aa8p-18f},
    { 0x1.307p-1f, -0x1.f5ce48p-21f, 0x1.ae8ap0f, -0x1.9a94b2p-22f},
    { 0x1.172cp-1f, -0x1.f0e0acp-19f, 0x1.d582p0f, -0x1.c8c116p-18f}
};

float cosh_float_avx2(float);
float cosh_float_avx2(float x){
    float tmp;
    float tmp1;
    float tmp2;
    int ov_flag;
    float tmp3;
    __m128 tmp4;
    __m128 tmp5;
    float tmp6;
    float tmp7;
    __m128 tmp8;
    __m128 k_log2;
    __m128 r_hi;
    float tmp9;
    __m128 tmp10;
    __m128 tmp11;
    __m128 r;
    __m128 pm_3;
    __m128 pa_3;
    __m128 pm_2;
    __m128 pa_2;
    __m128 tmp12;
    __m128 tmp13;
    __m128 poly_pos;
    int32_t k_integer;
    int32_t tmp14;
    int32_t k_int_lo;
    __m128i tmp15;
    __m128i table_index;
    int32_t tmp16;
    int32_t tmp17;
    float pos_value_load_hi;
    __m128 tmp18;
    __m128 tmp19;
    int32_t tmp20;
    float pos_value_load_lo;
    __m128 tmp21;
    __m128 tmp22;
    __m128 tmp23;
    __m128 tmp24;
    int32_t tmp25;
    uint32_t k_int_hi_srl_cast;
    int32_t tmp26;
    int32_t tmp27;
    int32_t k_plus;
    int32_t tmp28;
    int minmax_pred;
    int32_t tmp29;
    __m128i tmp30;
    __m128i tmp31;
    __m128i tmp32;
    int32_t tmp33;
    float pow_exp_pos;
    __m128 tmp34;
    __m128 pos_exp;
    float tmp35;
    float tmp36;
    __m128 tmp37;
    __m128 pm_31;
    __m128 pa_31;
    __m128 pm_21;
    __m128 pa_21;
    __m128 tmp38;
    __m128 tmp39;
    __m128 poly_neg;
    int32_t tmp40;
    float neg_value_load_hi;
    __m128 tmp41;
    __m128 tmp42;
    int32_t tmp43;
    float neg_value_load_lo;
    __m128 tmp44;
    __m128 tmp45;
    __m128 tmp46;
    __m128 tmp47;
    int32_t tmp48;
    int32_t tmp49;
    int32_t k_neg;
    int32_t tmp50;
    int minmax_pred1;
    int32_t tmp51;
    __m128i tmp52;
    __m128i tmp53;
    __m128i tmp54;
    int32_t tmp55;
    float pow_exp_neg;
    __m128 tmp56;
    __m128 neg_exp;
    __m128 tmp57;
    __m128 tmp58;
    __m128 tmp59;
    __m128 hi_terms;
    __m128 result;
    float tmp60;
    float tmp61;
    
    tmp = fabsf(x);
    tmp1 = fabsf(tmp);
    tmp2 = _mm_cvtss_f32(cosh_float_avx2_cst);
    ov_flag = tmp1 > tmp2;
    tmp3 = _mm_cvtss_f32(cosh_float_avx2_cst1);
    tmp4 = _mm_set_ss(tmp);
    tmp5 = _mm_mul_ss(cosh_float_avx2_inv_log2, tmp4);
    tmp6 = _mm_cvtss_f32(tmp5);
    tmp7 = truncf(tmp6);
    tmp8 = _mm_set_ss(tmp7);
    k_log2 = _mm_mul_ss(tmp8, cosh_float_avx2_log2_hi_value);
    r_hi = _mm_sub_ss(tmp4, k_log2);
    tmp9 =  - tmp7;
    tmp10 = _mm_set_ss(tmp9);
    tmp11 = _mm_mul_ss(tmp10, cosh_float_avx2_log2_lo_value);
    r = _mm_add_ss(r_hi, tmp11);
    pm_3 = _mm_mul_ss(r, cosh_float_avx2_c_4);
    pa_3 = _mm_add_ss(cosh_float_avx2_c_3, pm_3);
    pm_2 = _mm_mul_ss(r, pa_3);
    pa_2 = _mm_add_ss(cosh_float_avx2_c_2, pm_2);
    tmp12 = _mm_mul_ss(r, pa_2);
    tmp13 = _mm_add_ss(cosh_float_avx2_c_1, tmp12);
    poly_pos = _mm_mul_ss(r, tmp13);
    k_integer = tmp7;
    tmp14 = _mm_cvtsi128_si32(cosh_float_avx2_cst3);
    k_int_lo = k_integer % tmp14;
    tmp15 = _mm_set1_epi32(k_int_lo);
    table_index = _mm_add_epi32(tmp15, cosh_float_avx2_cst2);
    tmp16 = _mm_cvtsi128_si32(table_index);
    tmp17 = _mm_cvtsi128_si32(cosh_float_avx2_cst4);
    pos_value_load_hi = cosh_float_avx2_exp2_table[tmp16][tmp17];
    tmp18 = _mm_set_ss(pos_value_load_hi);
    tmp19 = _mm_mul_ss(tmp18, poly_pos);
    tmp20 = _mm_cvtsi128_si32(cosh_float_avx2_cst5);
    pos_value_load_lo = cosh_float_avx2_exp2_table[tmp16][tmp20];
    tmp21 = _mm_set_ss(pos_value_load_lo);
    tmp22 = _mm_mul_ss(tmp21, poly_pos);
    tmp23 = _mm_add_ss(tmp21, tmp22);
    tmp24 = _mm_add_ss(tmp19, tmp23);
    tmp25 = _mm_cvtsi128_si32(cosh_float_avx2_cst7);
    k_int_hi_srl_cast = k_integer;
    tmp26 = k_int_hi_srl_cast >> tmp25;
    tmp27 = _mm_cvtsi128_si32(cosh_float_avx2_cst8);
    k_plus = tmp26 - tmp27;
    tmp28 = _mm_cvtsi128_si32(cosh_float_avx2_cst9);
    minmax_pred = k_plus > tmp28;
    tmp29 = minmax_pred ? k_plus : tmp28;
    tmp30 = _mm_set1_epi32(tmp29);
    tmp31 = _mm_add_epi32(tmp30, cosh_float_avx2_cst6);
    tmp32 = tmp31 << cosh_float_avx2_cst10;
    tmp33 = _mm_cvtsi128_si32(tmp32);
    pow_exp_pos = float_from_32b_encoding(tmp33);
    tmp34 = _mm_set_ss(pow_exp_pos);
    pos_exp = _mm_mul_ss(tmp24, tmp34);
    tmp35 = _mm_cvtss_f32(r);
    tmp36 =  - tmp35;
    tmp37 = _mm_set_ss(tmp36);
    pm_31 = _mm_mul_ss(tmp37, cosh_float_avx2_c_41);
    pa_31 = _mm_add_ss(cosh_float_avx2_c_31, pm_31);
    pm_21 = _mm_mul_ss(tmp37, pa_31);
    pa_21 = _mm_add_ss(cosh_float_avx2_c_21, pm_21);
    tmp38 = _mm_mul_ss(tmp37, pa_21);
    tmp39 = _mm_add_ss(cosh_float_avx2_c_11, tmp38);
    poly_neg = _mm_mul_ss(tmp37, tmp39);
    tmp40 = _mm_cvtsi128_si32(cosh_float_avx2_cst11);
    neg_value_load_hi = cosh_float_avx2_exp2_table[tmp16][tmp40];
    tmp41 = _mm_set_ss(neg_value_load_hi);
    tmp42 = _mm_mul_ss(tmp41, poly_neg);
    tmp43 = _mm_cvtsi128_si32(cosh_float_avx2_cst12);
    neg_value_load_lo = cosh_float_avx2_exp2_table[tmp16][tmp43];
    tmp44 = _mm_set_ss(neg_value_load_lo);
    tmp45 = _mm_mul_ss(tmp44, poly_neg);
    tmp46 = _mm_add_ss(tmp44, tmp45);
    tmp47 = _mm_add_ss(tmp42, tmp46);
    tmp48 =  - tmp26;
    tmp49 = _mm_cvtsi128_si32(cosh_float_avx2_cst14);
    k_neg = tmp48 - tmp49;
    tmp50 = _mm_cvtsi128_si32(cosh_float_avx2_cst15);
    minmax_pred1 = k_neg > tmp50;
    tmp51 = minmax_pred1 ? k_neg : tmp50;
    tmp52 = _mm_set1_epi32(tmp51);
    tmp53 = _mm_add_epi32(tmp52, cosh_float_avx2_cst13);
    tmp54 = tmp53 << cosh_float_avx2_cst16;
    tmp55 = _mm_cvtsi128_si32(tmp54);
    pow_exp_neg = float_from_32b_encoding(tmp55);
    tmp56 = _mm_set_ss(pow_exp_neg);
    neg_exp = _mm_mul_ss(tmp47, tmp56);
    tmp57 = _mm_add_ss(pos_exp, neg_exp);
    tmp58 = _mm_mul_ss(tmp18, tmp34);
    tmp59 = _mm_mul_ss(tmp41, tmp56);
    hi_terms = _mm_add_ss(tmp58, tmp59);
    result = _mm_add_ss(tmp57, hi_terms);
    tmp60 = _mm_cvtss_f32(result);
    tmp61 = ov_flag ? tmp3 : tmp60;
    return tmp61;
}
