/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_exp2.py --language c --accuracy cr --precision \
 *     double --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/exp2_double_avx2.c --fname exp2_double_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <math.h>
#include <ml_support_lib.h>
#include <emmintrin.h>


static const __m128d exp2_double_avx2_cst = {1024.0}/*sse*/;
static const __m128d exp2_double_avx2_cst1 = {8.0}/*sse*/;
static const __m128d exp2_double_avx2_cst2 = {0.125}/*sse*/;
static const __m128d exp2_double_avx2_c_10 = {0x1.1907a8c1c78c1p-27}/*sse*/;
static const __m128d exp2_double_avx2_c_9 = {0x1.9de07f01b20bep-24}/*sse*/;
static const __m128d exp2_double_avx2_c_8 = {0x1.62bcf28aeda6cp-20}/*sse*/;
static const __m128d exp2_double_avx2_c_7 = {0x1.ffcdc44bc06d7p-17}/*sse*/;
static const __m128d exp2_double_avx2_c_6 = {0x1.4309131068c2ap-13}/*sse*/;
static const __m128d exp2_double_avx2_c_5 = {0x1.5d87fe6c9eeadp-10}/*sse*/;
static const __m128d exp2_double_avx2_c_4 = {0x1.3b2ab6fba44fep-7}/*sse*/;
static const __m128d exp2_double_avx2_c_3 = {0x1.c6b08d704a8c5p-5}/*sse*/;
static const __m128d exp2_double_avx2_c_2 = {0x1.ebfbdff82c58fp-3}/*sse*/;
static const __m128d exp2_double_avx2_c_1 = {0x1.62e42fefa39efp-1}/*sse*/;
static const __m128d exp2_double_avx2_cst3 = {-1022.0}/*sse*/;
static const __m128d exp2_double_avx2_cst4 = {INFINITY}/*sse*/;
static const __m128d exp2_double_avx2_cst5 = {-1074.0}/*sse*/;
static const __m128i exp2_double_avx2_cst6 = {INT32_C(-1022)}/*sse*/;
static const __m128d exp2_double_avx2_cst7 = {0.0}/*sse*/;
static const double exp2_double_avx2_exp2_table[9]  = {
     0x1p0, 0x1.172b83c7d517bp0, 0x1.306fe0a31b715p0, 0x1.4bfdad5362a27p0,
     0x1.6a09e667f3bcdp0, 0x1.8ace5422aa0dbp0, 0x1.ae89f995ad3adp0,
     0x1.d5818dcfba487p0, 0x1p1
};

double exp2_double_avx2(double);
double exp2_double_avx2(double x){
    double tmp;
    int oflow_test;
    double vx_floor;
    double vx_r;
    double tmp1;
    double tmp2;
    __m128d tmp3;
    __m128d r_hi;
    double tmp4;
    int64_t r_hi_int;
    int minmax_pred;
    int64_t tmp5;
    int minmax_pred1;
    int64_t tmp6;
    double hi_part_value;
    int64_t vx_int;
    double tmp7;
    double tmp8;
    double r_lo;
    double tmp9;
    double pm_9;
    double tmp10;
    double pa_9;
    double pm_8;
    double tmp11;
    double pa_8;
    double pm_7;
    double tmp12;
    double pa_7;
    double pm_6;
    double tmp13;
    double pa_6;
    double pm_5;
    double tmp14;
    double pa_5;
    double pm_4;
    double tmp15;
    double pa_4;
    double pm_3;
    double tmp16;
    double pa_3;
    double pm_2;
    double tmp17;
    double pa_2;
    double tmp18;
    double tmp19;
    double tmp20;
    double poly;
    int64_t tmp21;
    int64_t tmp22;
    double exp_X;
    double tmp23;
    int uflow_test;
    int std_test;
    
    tmp = _mm_cvtsd_f64(exp2_double_avx2_cst);
    oflow_test = x >= tmp;
    vx_floor = floor(x);
    vx_r = x - vx_floor;
    tmp1 = _mm_cvtsd_f64(exp2_double_avx2_cst1);
    tmp2 = vx_r * tmp1;
    tmp3 = _mm_set_sd(tmp2);
    r_hi = _mm_round_sd(tmp3, tmp3, _MM_FROUND_TO_NEAREST_INT);
    tmp4 = _mm_cvtsd_f64(r_hi);
    r_hi_int = tmp4;
    minmax_pred = r_hi_int < INT64_C(9);
    tmp5 = minmax_pred ? r_hi_int : INT64_C(9);
    minmax_pred1 = tmp5 > INT64_C(0);
    tmp6 = minmax_pred1 ? tmp5 : INT64_C(0);
    hi_part_value = exp2_double_avx2_exp2_table[tmp6];
    vx_int = vx_floor;
    tmp7 = _mm_cvtsd_f64(exp2_double_avx2_cst2);
    tmp8 = tmp4 * tmp7;
    r_lo = vx_r - tmp8;
    tmp9 = _mm_cvtsd_f64(exp2_double_avx2_c_10);
    pm_9 = r_lo * tmp9;
    tmp10 = _mm_cvtsd_f64(exp2_double_avx2_c_9);
    pa_9 = tmp10 + pm_9;
    pm_8 = r_lo * pa_9;
    tmp11 = _mm_cvtsd_f64(exp2_double_avx2_c_8);
    pa_8 = tmp11 + pm_8;
    pm_7 = r_lo * pa_8;
    tmp12 = _mm_cvtsd_f64(exp2_double_avx2_c_7);
    pa_7 = tmp12 + pm_7;
    pm_6 = r_lo * pa_7;
    tmp13 = _mm_cvtsd_f64(exp2_double_avx2_c_6);
    pa_6 = tmp13 + pm_6;
    pm_5 = r_lo * pa_6;
    tmp14 = _mm_cvtsd_f64(exp2_double_avx2_c_5);
    pa_5 = tmp14 + pm_5;
    pm_4 = r_lo * pa_5;
    tmp15 = _mm_cvtsd_f64(exp2_double_avx2_c_4);
    pa_4 = tmp15 + pm_4;
    pm_3 = r_lo * pa_4;
    tmp16 = _mm_cvtsd_f64(exp2_double_avx2_c_3);
    pa_3 = tmp16 + pm_3;
    pm_2 = r_lo * pa_3;
    tmp17 = _mm_cvtsd_f64(exp2_double_avx2_c_2);
    pa_2 = tmp17 + pm_2;
    tmp18 = r_lo * pa_2;
    tmp19 = _mm_cvtsd_f64(exp2_double_avx2_c_1);
    tmp20 = tmp19 + tmp18;
    poly = r_lo * tmp20;
    tmp21 = vx_int + INT64_C(1023);
    tmp22 = tmp21 << INT64_C(52);
    exp_X = double_from_64b_encoding(tmp22);
    tmp23 = _mm_cvtsd_f64(exp2_double_avx2_cst3);
    uflow_test = x < tmp23;
    std_test = oflow_test || uflow_test;

    if (__builtin_expect(std_test, 0)) {


        if (__builtin_expect(oflow_test, 0)) {
            double tmp0;

            tmp0 = _mm_cvtsd_f64(exp2_double_avx2_cst4);
            return tmp0;
        } else {
            double tmp0;
            int sub_test;

            tmp0 = _mm_cvtsd_f64(exp2_double_avx2_cst5);
            sub_test = x > tmp0;

            if (__builtin_expect(sub_test, 0)) {
                int64_t tmp24;
                int64_t offset;
                int64_t tmp25;
                int64_t tmp26;
                double exp_offset;
                double tmp27;
                int32_t tmp28;
                int64_t tmp29;
                int64_t tmp30;
                double exp_min;
                double tmp31;
                double tmp32;
                double tmp33;
                double tmp34;
                double tmp35;

                tmp24 = INT64_C(-1022) - vx_int;
                offset =  - tmp24;
                tmp25 = offset + INT64_C(1023);
                tmp26 = tmp25 << INT64_C(52);
                exp_offset = double_from_64b_encoding(tmp26);
                tmp27 = hi_part_value * exp_offset;
                tmp28 = _mm_cvtsi128_si32(exp2_double_avx2_cst6);
                tmp29 = ( (int64_t) tmp28) + INT64_C(1023);
                tmp30 = tmp29 << INT64_C(52);
                exp_min = double_from_64b_encoding(tmp30);
                tmp31 = tmp27 * exp_min;
                tmp32 = tmp31 * poly;
                tmp33 = hi_part_value * exp_offset;
                tmp34 = tmp33 * exp_min;
                tmp35 = tmp32 + tmp34;
                return tmp35;
            } else {
                double tmp24;

                tmp24 = _mm_cvtsd_f64(exp2_double_avx2_cst7);
                return tmp24;
            }
        }
    } else {
        double tmp0;
        double tmp24;
        double tmp25;
        double result;

        tmp0 = hi_part_value * exp_X;
        tmp24 = tmp0 * poly;
        tmp25 = hi_part_value * exp_X;
        result = tmp24 + tmp25;
        return result;
    }
}
