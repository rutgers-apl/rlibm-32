/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_cosh.py --language c --accuracy cr --precision \
 *     float --target x86 --output GeneratedFunctions/cr/x86/cosh_float_x86.c \
 *     --fname cosh_float_x86
 * 
**/
#include <stdint.h>
#include <math.h>
#include <ml_support_lib.h>


static const float cosh_float_x86_exp2_table[16][4]  = {
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

float cosh_float_x86(float);
float cosh_float_x86(float x){
    float tmp;
    float tmp1;
    float tmp2;
    int32_t k_integer;
    int32_t k_int_lo;
    int32_t table_index;
    float pos_value_load_hi;
    uint32_t k_int_hi_srl_cast;
    int32_t tmp3;
    int32_t k_plus;
    int minmax_pred;
    int32_t tmp4;
    float pow_exp_pos;
    float tmp5;
    float neg_value_load_hi;
    int32_t tmp6;
    int32_t k_neg;
    int minmax_pred1;
    int32_t tmp7;
    float pow_exp_neg;
    float tmp8;
    float hi_terms;
    float k_log2;
    float r_hi;
    float tmp9;
    float tmp10;
    float r;
    float pm_3;
    float pa_3;
    float pm_2;
    float pa_2;
    float tmp11;
    float tmp12;
    float poly_pos;
    float tmp13;
    float pos_value_load_lo;
    float tmp14;
    float tmp15;
    float tmp16;
    float pos_exp;
    float tmp17;
    float pm_31;
    float pa_31;
    float pm_21;
    float pa_21;
    float tmp18;
    float tmp19;
    float poly_neg;
    float tmp20;
    float neg_value_load_lo;
    float tmp21;
    float tmp22;
    float tmp23;
    float neg_exp;
    float tmp24;
    float result;
    float tmp25;
    int ov_flag;
    float tmp26;
    
    tmp = fabsf(x);
    tmp1 = 0x1.715476p3f * tmp;
    tmp2 = truncf(tmp1);
    k_integer = tmp2;
    k_int_lo = k_integer % INT32_C(8);
    table_index = k_int_lo + INT32_C(8);
    pos_value_load_hi = cosh_float_x86_exp2_table[table_index][INT32_C(2)];
    k_int_hi_srl_cast = k_integer;
    tmp3 = k_int_hi_srl_cast >> INT32_C(3);
    k_plus = tmp3 - INT32_C(1);
    minmax_pred = k_plus > INT32_C(-126);
    tmp4 = minmax_pred ? k_plus : INT32_C(-126);
    pow_exp_pos = ml_exp_insertion_fp32(tmp4);
    tmp5 = pos_value_load_hi * pow_exp_pos;
    neg_value_load_hi = cosh_float_x86_exp2_table[table_index][INT32_C(0)];
    tmp6 =  - tmp3;
    k_neg = tmp6 - INT32_C(1);
    minmax_pred1 = k_neg > INT32_C(-126);
    tmp7 = minmax_pred1 ? k_neg : INT32_C(-126);
    pow_exp_neg = ml_exp_insertion_fp32(tmp7);
    tmp8 = neg_value_load_hi * pow_exp_neg;
    hi_terms = tmp5 + tmp8;
    k_log2 = tmp2 * 0x1.63p-4f;
    r_hi = tmp - k_log2;
    tmp9 =  - tmp2;
    tmp10 = tmp9 * -0x1.bd0106p-16f;
    r = r_hi + tmp10;
    pm_3 = r * 0x1.557c38p-5f;
    pa_3 = 0x1.557c08p-3f + pm_3;
    pm_2 = r * pa_3;
    pa_2 = 0x1.fffffcp-2f + pm_2;
    tmp11 = r * pa_2;
    tmp12 = 0x1.fffffcp-1f + tmp11;
    poly_pos = r * tmp12;
    tmp13 = pos_value_load_hi * poly_pos;
    pos_value_load_lo = cosh_float_x86_exp2_table[table_index][INT32_C(3)];
    tmp14 = pos_value_load_lo * poly_pos;
    tmp15 = pos_value_load_lo + tmp14;
    tmp16 = tmp13 + tmp15;
    pos_exp = tmp16 * pow_exp_pos;
    tmp17 =  - r;
    pm_31 = tmp17 * 0x1.557c38p-5f;
    pa_31 = 0x1.557c08p-3f + pm_31;
    pm_21 = tmp17 * pa_31;
    pa_21 = 0x1.fffffcp-2f + pm_21;
    tmp18 = tmp17 * pa_21;
    tmp19 = 0x1.fffffcp-1f + tmp18;
    poly_neg = tmp17 * tmp19;
    tmp20 = neg_value_load_hi * poly_neg;
    neg_value_load_lo = cosh_float_x86_exp2_table[table_index][INT32_C(1)];
    tmp21 = neg_value_load_lo * poly_neg;
    tmp22 = neg_value_load_lo + tmp21;
    tmp23 = tmp20 + tmp22;
    neg_exp = tmp23 * pow_exp_neg;
    tmp24 = pos_exp + neg_exp;
    result = tmp24 + hi_terms;
    tmp25 = fabsf(tmp);
    ov_flag = tmp25 > 0x1.65a9f8p6f;
    tmp26 = ov_flag ? INFINITY : result;
    return tmp26;
}
