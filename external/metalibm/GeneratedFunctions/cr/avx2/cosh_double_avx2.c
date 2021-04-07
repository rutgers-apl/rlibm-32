/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_cosh.py --language c --accuracy cr --precision \
 *     double --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/cosh_double_avx2.c --fname cosh_double_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <ml_support_lib.h>


static const __m128d cosh_double_avx2_inv_log2 = {0x1.71547652b82fep3}/*sse*/;
static const __m128i cosh_double_avx2_cst = {INT32_C(2)}/*sse*/;
static const __m128i cosh_double_avx2_cst1 = {INT32_C(0)}/*sse*/;
static const __m128d cosh_double_avx2_log2_hi_value = {0x1.62e42fefap-4}/*sse*/;
static const __m128d cosh_double_avx2_log2_lo_value = {0x1.cf79abc9e3b3ap-43}/*sse*/;
static const __m128d cosh_double_avx2_c_8 = {0x1.a032192c939e3p-16}/*sse*/;
static const __m128d cosh_double_avx2_c_7 = {0x1.a0332b7b3953bp-13}/*sse*/;
static const __m128d cosh_double_avx2_c_6 = {0x1.6c16c0bb602cap-10}/*sse*/;
static const __m128d cosh_double_avx2_c_5 = {0x1.1111107e6e6f5p-7}/*sse*/;
static const __m128d cosh_double_avx2_c_4 = {0x1.5555555559723p-5}/*sse*/;
static const __m128d cosh_double_avx2_c_3 = {0x1.555555555a51bp-3}/*sse*/;
static const __m128d cosh_double_avx2_c_2 = {0x1.ffffffffffffep-2}/*sse*/;
static const __m128d cosh_double_avx2_c_1 = {0x1.ffffffffffffdp-1}/*sse*/;
static const __m128i cosh_double_avx2_cst2 = {INT32_C(3)}/*sse*/;
static const __m128d cosh_double_avx2_c_81 = {0x1.a032192c939e3p-16}/*sse*/;
static const __m128d cosh_double_avx2_c_71 = {0x1.a0332b7b3953bp-13}/*sse*/;
static const __m128d cosh_double_avx2_c_61 = {0x1.6c16c0bb602cap-10}/*sse*/;
static const __m128d cosh_double_avx2_c_51 = {0x1.1111107e6e6f5p-7}/*sse*/;
static const __m128d cosh_double_avx2_c_41 = {0x1.5555555559723p-5}/*sse*/;
static const __m128d cosh_double_avx2_c_31 = {0x1.555555555a51bp-3}/*sse*/;
static const __m128d cosh_double_avx2_c_21 = {0x1.ffffffffffffep-2}/*sse*/;
static const __m128d cosh_double_avx2_c_11 = {0x1.ffffffffffffdp-1}/*sse*/;
static const __m128i cosh_double_avx2_cst3 = {INT32_C(1)}/*sse*/;
static const __m128d cosh_double_avx2_cst4 = {0x1.633ce8fb9f87dp9}/*sse*/;
static const __m128d cosh_double_avx2_cst5 = {INFINITY}/*sse*/;
static const double cosh_double_avx2_exp2_table[16][4]  = {
    { 0x1p0, 0.0, 0x1p0, 0.0},
    {
     0x1.d5818dcfcp-1, -0x1.6de36897e9452p-39, 0x1.172b83c7cp0,
     0x1.517adcdf7c8c5p-36
},
    { 0x1.ae89f995cp-1, -0x1.2c52a178cb2e9p-37, 0x1.306fe0a3p0, 0x1.b7152de8d5a46p-36},
    {
     0x1.8ace5422cp-1, -0x1.5f24a4583aa5ep-37, 0x1.4bfdad538p0,
     -0x1.d5d8e2bc68501p-36
},
    { 0x1.6a09e668p-1, -0x1.8866dee9a09d9p-38, 0x1.6a09e668p0, -0x1.8866dee9a09d9p-37},
    {
     0x1.4bfdad538p-1, -0x1.d5d8e2bc68501p-37, 0x1.8ace5422cp0,
     -0x1.5f24a4583aa5ep-36
},
    { 0x1.306fe0a3p-1, 0x1.b7152de8d5a46p-37, 0x1.ae89f995cp0, -0x1.2c52a178cb2e9p-36},
    {
     0x1.172b83c7cp-1, 0x1.517adcdf7c8c5p-37, 0x1.d5818dcfcp0,
     -0x1.6de36897e9452p-38
},
    { 0x1p0, 0.0, 0x1p0, 0.0},
    {
     0x1.d5818dcfcp-1, -0x1.6de36897e9452p-39, 0x1.172b83c7cp0,
     0x1.517adcdf7c8c5p-36
},
    { 0x1.ae89f995cp-1, -0x1.2c52a178cb2e9p-37, 0x1.306fe0a3p0, 0x1.b7152de8d5a46p-36},
    {
     0x1.8ace5422cp-1, -0x1.5f24a4583aa5ep-37, 0x1.4bfdad538p0,
     -0x1.d5d8e2bc68501p-36
},
    { 0x1.6a09e668p-1, -0x1.8866dee9a09d9p-38, 0x1.6a09e668p0, -0x1.8866dee9a09d9p-37},
    {
     0x1.4bfdad538p-1, -0x1.d5d8e2bc68501p-37, 0x1.8ace5422cp0,
     -0x1.5f24a4583aa5ep-36
},
    { 0x1.306fe0a3p-1, 0x1.b7152de8d5a46p-37, 0x1.ae89f995cp0, -0x1.2c52a178cb2e9p-36},
    {
     0x1.172b83c7cp-1, 0x1.517adcdf7c8c5p-37, 0x1.d5818dcfcp0,
     -0x1.6de36897e9452p-38
}
};

double cosh_double_avx2(double);
double cosh_double_avx2(double x){
    double tmp;
    double tmp1;
    double tmp2;
    double tmp3;
    int64_t k_integer;
    int64_t k_int_lo;
    int64_t table_index;
    int32_t tmp4;
    double pos_value_load_hi;
    uint64_t k_int_hi_srl_cast;
    int64_t tmp5;
    int64_t k_plus;
    int minmax_pred;
    int64_t tmp6;
    int64_t tmp7;
    int64_t tmp8;
    double pow_exp_pos;
    double tmp9;
    int32_t tmp10;
    double neg_value_load_hi;
    int64_t tmp11;
    int64_t k_neg;
    int minmax_pred1;
    int64_t tmp12;
    int64_t tmp13;
    int64_t tmp14;
    double pow_exp_neg;
    double tmp15;
    double hi_terms;
    double tmp16;
    double k_log2;
    double r_hi;
    double tmp17;
    double tmp18;
    double tmp19;
    double r;
    double tmp20;
    double pm_7;
    double tmp21;
    double pa_7;
    double pm_6;
    double tmp22;
    double pa_6;
    double pm_5;
    double tmp23;
    double pa_5;
    double pm_4;
    double tmp24;
    double pa_4;
    double pm_3;
    double tmp25;
    double pa_3;
    double pm_2;
    double tmp26;
    double pa_2;
    double tmp27;
    double tmp28;
    double tmp29;
    double poly_pos;
    double tmp30;
    int32_t tmp31;
    double pos_value_load_lo;
    double tmp32;
    double tmp33;
    double tmp34;
    double pos_exp;
    double tmp35;
    double tmp36;
    double pm_71;
    double tmp37;
    double pa_71;
    double pm_61;
    double tmp38;
    double pa_61;
    double pm_51;
    double tmp39;
    double pa_51;
    double pm_41;
    double tmp40;
    double pa_41;
    double pm_31;
    double tmp41;
    double pa_31;
    double pm_21;
    double tmp42;
    double pa_21;
    double tmp43;
    double tmp44;
    double tmp45;
    double poly_neg;
    double tmp46;
    int32_t tmp47;
    double neg_value_load_lo;
    double tmp48;
    double tmp49;
    double tmp50;
    double neg_exp;
    double tmp51;
    double result;
    double tmp52;
    double tmp53;
    int ov_flag;
    double tmp54;
    double tmp55;
    
    tmp = fabs(x);
    tmp1 = _mm_cvtsd_f64(cosh_double_avx2_inv_log2);
    tmp2 = tmp1 * tmp;
    tmp3 = trunc(tmp2);
    k_integer = tmp3;
    k_int_lo = k_integer % INT64_C(8);
    table_index = k_int_lo + INT64_C(8);
    tmp4 = _mm_cvtsi128_si32(cosh_double_avx2_cst);
    pos_value_load_hi = cosh_double_avx2_exp2_table[table_index][tmp4];
    k_int_hi_srl_cast = k_integer;
    tmp5 = k_int_hi_srl_cast >> INT64_C(3);
    k_plus = tmp5 - INT64_C(1);
    minmax_pred = k_plus > INT64_C(-1022);
    tmp6 = minmax_pred ? k_plus : INT64_C(-1022);
    tmp7 = tmp6 + INT64_C(1023);
    tmp8 = tmp7 << INT64_C(52);
    pow_exp_pos = double_from_64b_encoding(tmp8);
    tmp9 = pos_value_load_hi * pow_exp_pos;
    tmp10 = _mm_cvtsi128_si32(cosh_double_avx2_cst1);
    neg_value_load_hi = cosh_double_avx2_exp2_table[table_index][tmp10];
    tmp11 =  - tmp5;
    k_neg = tmp11 - INT64_C(1);
    minmax_pred1 = k_neg > INT64_C(-1022);
    tmp12 = minmax_pred1 ? k_neg : INT64_C(-1022);
    tmp13 = tmp12 + INT64_C(1023);
    tmp14 = tmp13 << INT64_C(52);
    pow_exp_neg = double_from_64b_encoding(tmp14);
    tmp15 = neg_value_load_hi * pow_exp_neg;
    hi_terms = tmp9 + tmp15;
    tmp16 = _mm_cvtsd_f64(cosh_double_avx2_log2_hi_value);
    k_log2 = tmp3 * tmp16;
    r_hi = tmp - k_log2;
    tmp17 =  - tmp3;
    tmp18 = _mm_cvtsd_f64(cosh_double_avx2_log2_lo_value);
    tmp19 = tmp17 * tmp18;
    r = r_hi + tmp19;
    tmp20 = _mm_cvtsd_f64(cosh_double_avx2_c_8);
    pm_7 = r * tmp20;
    tmp21 = _mm_cvtsd_f64(cosh_double_avx2_c_7);
    pa_7 = tmp21 + pm_7;
    pm_6 = r * pa_7;
    tmp22 = _mm_cvtsd_f64(cosh_double_avx2_c_6);
    pa_6 = tmp22 + pm_6;
    pm_5 = r * pa_6;
    tmp23 = _mm_cvtsd_f64(cosh_double_avx2_c_5);
    pa_5 = tmp23 + pm_5;
    pm_4 = r * pa_5;
    tmp24 = _mm_cvtsd_f64(cosh_double_avx2_c_4);
    pa_4 = tmp24 + pm_4;
    pm_3 = r * pa_4;
    tmp25 = _mm_cvtsd_f64(cosh_double_avx2_c_3);
    pa_3 = tmp25 + pm_3;
    pm_2 = r * pa_3;
    tmp26 = _mm_cvtsd_f64(cosh_double_avx2_c_2);
    pa_2 = tmp26 + pm_2;
    tmp27 = r * pa_2;
    tmp28 = _mm_cvtsd_f64(cosh_double_avx2_c_1);
    tmp29 = tmp28 + tmp27;
    poly_pos = r * tmp29;
    tmp30 = pos_value_load_hi * poly_pos;
    tmp31 = _mm_cvtsi128_si32(cosh_double_avx2_cst2);
    pos_value_load_lo = cosh_double_avx2_exp2_table[table_index][tmp31];
    tmp32 = pos_value_load_lo * poly_pos;
    tmp33 = pos_value_load_lo + tmp32;
    tmp34 = tmp30 + tmp33;
    pos_exp = tmp34 * pow_exp_pos;
    tmp35 =  - r;
    tmp36 = _mm_cvtsd_f64(cosh_double_avx2_c_81);
    pm_71 = tmp35 * tmp36;
    tmp37 = _mm_cvtsd_f64(cosh_double_avx2_c_71);
    pa_71 = tmp37 + pm_71;
    pm_61 = tmp35 * pa_71;
    tmp38 = _mm_cvtsd_f64(cosh_double_avx2_c_61);
    pa_61 = tmp38 + pm_61;
    pm_51 = tmp35 * pa_61;
    tmp39 = _mm_cvtsd_f64(cosh_double_avx2_c_51);
    pa_51 = tmp39 + pm_51;
    pm_41 = tmp35 * pa_51;
    tmp40 = _mm_cvtsd_f64(cosh_double_avx2_c_41);
    pa_41 = tmp40 + pm_41;
    pm_31 = tmp35 * pa_41;
    tmp41 = _mm_cvtsd_f64(cosh_double_avx2_c_31);
    pa_31 = tmp41 + pm_31;
    pm_21 = tmp35 * pa_31;
    tmp42 = _mm_cvtsd_f64(cosh_double_avx2_c_21);
    pa_21 = tmp42 + pm_21;
    tmp43 = tmp35 * pa_21;
    tmp44 = _mm_cvtsd_f64(cosh_double_avx2_c_11);
    tmp45 = tmp44 + tmp43;
    poly_neg = tmp35 * tmp45;
    tmp46 = neg_value_load_hi * poly_neg;
    tmp47 = _mm_cvtsi128_si32(cosh_double_avx2_cst3);
    neg_value_load_lo = cosh_double_avx2_exp2_table[table_index][tmp47];
    tmp48 = neg_value_load_lo * poly_neg;
    tmp49 = neg_value_load_lo + tmp48;
    tmp50 = tmp46 + tmp49;
    neg_exp = tmp50 * pow_exp_neg;
    tmp51 = pos_exp + neg_exp;
    result = tmp51 + hi_terms;
    tmp52 = fabs(tmp);
    tmp53 = _mm_cvtsd_f64(cosh_double_avx2_cst4);
    ov_flag = tmp52 > tmp53;
    tmp54 = _mm_cvtsd_f64(cosh_double_avx2_cst5);
    tmp55 = ov_flag ? tmp54 : result;
    return tmp55;
}
