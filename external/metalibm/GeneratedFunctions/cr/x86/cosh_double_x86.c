/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_cosh.py --language c --accuracy cr --precision \
 *     double --target x86 --output \
 *     GeneratedFunctions/cr/x86/cosh_double_x86.c --fname cosh_double_x86
 * 
**/
#include <stdint.h>
#include <math.h>
#include <ml_support_lib.h>


static const double cosh_double_x86_exp2_table[16][4]  = {
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

double cosh_double_x86(double);
double cosh_double_x86(double x){
    double tmp;
    double tmp1;
    double tmp2;
    int64_t k_integer;
    int64_t k_int_lo;
    int64_t table_index;
    double pos_value_load_hi;
    uint64_t k_int_hi_srl_cast;
    int64_t tmp3;
    int64_t k_plus;
    int minmax_pred;
    int64_t tmp4;
    double pow_exp_pos;
    double tmp5;
    double neg_value_load_hi;
    int64_t tmp6;
    int64_t k_neg;
    int minmax_pred1;
    int64_t tmp7;
    double pow_exp_neg;
    double tmp8;
    double hi_terms;
    double k_log2;
    double r_hi;
    double tmp9;
    double tmp10;
    double r;
    double pm_7;
    double pa_7;
    double pm_6;
    double pa_6;
    double pm_5;
    double pa_5;
    double pm_4;
    double pa_4;
    double pm_3;
    double pa_3;
    double pm_2;
    double pa_2;
    double tmp11;
    double tmp12;
    double poly_pos;
    double tmp13;
    double pos_value_load_lo;
    double tmp14;
    double tmp15;
    double tmp16;
    double pos_exp;
    double tmp17;
    double pm_71;
    double pa_71;
    double pm_61;
    double pa_61;
    double pm_51;
    double pa_51;
    double pm_41;
    double pa_41;
    double pm_31;
    double pa_31;
    double pm_21;
    double pa_21;
    double tmp18;
    double tmp19;
    double poly_neg;
    double tmp20;
    double neg_value_load_lo;
    double tmp21;
    double tmp22;
    double tmp23;
    double neg_exp;
    double tmp24;
    double result;
    double tmp25;
    int ov_flag;
    double tmp26;
    
    tmp = fabs(x);
    tmp1 = 0x1.71547652b82fep3 * tmp;
    tmp2 = trunc(tmp1);
    k_integer = tmp2;
    k_int_lo = k_integer % INT64_C(8);
    table_index = k_int_lo + INT64_C(8);
    pos_value_load_hi = cosh_double_x86_exp2_table[table_index][INT32_C(2)];
    k_int_hi_srl_cast = k_integer;
    tmp3 = k_int_hi_srl_cast >> INT64_C(3);
    k_plus = tmp3 - INT64_C(1);
    minmax_pred = k_plus > INT64_C(-1022);
    tmp4 = minmax_pred ? k_plus : INT64_C(-1022);
    pow_exp_pos = ml_exp_insertion_fp64(tmp4);
    tmp5 = pos_value_load_hi * pow_exp_pos;
    neg_value_load_hi = cosh_double_x86_exp2_table[table_index][INT32_C(0)];
    tmp6 =  - tmp3;
    k_neg = tmp6 - INT64_C(1);
    minmax_pred1 = k_neg > INT64_C(-1022);
    tmp7 = minmax_pred1 ? k_neg : INT64_C(-1022);
    pow_exp_neg = ml_exp_insertion_fp64(tmp7);
    tmp8 = neg_value_load_hi * pow_exp_neg;
    hi_terms = tmp5 + tmp8;
    k_log2 = tmp2 * 0x1.62e42fefap-4;
    r_hi = tmp - k_log2;
    tmp9 =  - tmp2;
    tmp10 = tmp9 * 0x1.cf79abc9e3b3ap-43;
    r = r_hi + tmp10;
    pm_7 = r * 0x1.a032192c939e3p-16;
    pa_7 = 0x1.a0332b7b3953bp-13 + pm_7;
    pm_6 = r * pa_7;
    pa_6 = 0x1.6c16c0bb602cap-10 + pm_6;
    pm_5 = r * pa_6;
    pa_5 = 0x1.1111107e6e6f5p-7 + pm_5;
    pm_4 = r * pa_5;
    pa_4 = 0x1.5555555559723p-5 + pm_4;
    pm_3 = r * pa_4;
    pa_3 = 0x1.555555555a51bp-3 + pm_3;
    pm_2 = r * pa_3;
    pa_2 = 0x1.ffffffffffffep-2 + pm_2;
    tmp11 = r * pa_2;
    tmp12 = 0x1.ffffffffffffdp-1 + tmp11;
    poly_pos = r * tmp12;
    tmp13 = pos_value_load_hi * poly_pos;
    pos_value_load_lo = cosh_double_x86_exp2_table[table_index][INT32_C(3)];
    tmp14 = pos_value_load_lo * poly_pos;
    tmp15 = pos_value_load_lo + tmp14;
    tmp16 = tmp13 + tmp15;
    pos_exp = tmp16 * pow_exp_pos;
    tmp17 =  - r;
    pm_71 = tmp17 * 0x1.a032192c939e3p-16;
    pa_71 = 0x1.a0332b7b3953bp-13 + pm_71;
    pm_61 = tmp17 * pa_71;
    pa_61 = 0x1.6c16c0bb602cap-10 + pm_61;
    pm_51 = tmp17 * pa_61;
    pa_51 = 0x1.1111107e6e6f5p-7 + pm_51;
    pm_41 = tmp17 * pa_51;
    pa_41 = 0x1.5555555559723p-5 + pm_41;
    pm_31 = tmp17 * pa_41;
    pa_31 = 0x1.555555555a51bp-3 + pm_31;
    pm_21 = tmp17 * pa_31;
    pa_21 = 0x1.ffffffffffffep-2 + pm_21;
    tmp18 = tmp17 * pa_21;
    tmp19 = 0x1.ffffffffffffdp-1 + tmp18;
    poly_neg = tmp17 * tmp19;
    tmp20 = neg_value_load_hi * poly_neg;
    neg_value_load_lo = cosh_double_x86_exp2_table[table_index][INT32_C(1)];
    tmp21 = neg_value_load_lo * poly_neg;
    tmp22 = neg_value_load_lo + tmp21;
    tmp23 = tmp20 + tmp22;
    neg_exp = tmp23 * pow_exp_neg;
    tmp24 = pos_exp + neg_exp;
    result = tmp24 + hi_terms;
    tmp25 = fabs(tmp);
    ov_flag = tmp25 > 0x1.633ce8fb9f87dp9;
    tmp26 = ov_flag ? INFINITY : result;
    return tmp26;
}
