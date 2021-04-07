/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_exp2.py --language c --accuracy cr --precision \
 *     double --target x86 --output \
 *     GeneratedFunctions/cr/x86/exp2_double_x86.c --fname exp2_double_x86
 * 
**/
#include <stdint.h>
#include <math.h>
#include <ml_support_lib.h>


static const double exp2_double_x86_exp2_table[9]  = {
     0x1p0, 0x1.172b83c7d517bp0, 0x1.306fe0a31b715p0, 0x1.4bfdad5362a27p0,
     0x1.6a09e667f3bcdp0, 0x1.8ace5422aa0dbp0, 0x1.ae89f995ad3adp0,
     0x1.d5818dcfba487p0, 0x1p1
};

double exp2_double_x86(double);
double exp2_double_x86(double x){
    int oflow_test;
    double vx_floor;
    double vx_r;
    double tmp;
    double r_hi;
    int64_t r_hi_int;
    int minmax_pred;
    int64_t tmp1;
    int minmax_pred1;
    int64_t tmp2;
    double hi_part_value;
    int64_t vx_int;
    double tmp3;
    double r_lo;
    double pm_9;
    double pa_9;
    double pm_8;
    double pa_8;
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
    double tmp4;
    double tmp5;
    double poly;
    double exp_X;
    int uflow_test;
    int std_test;
    
    oflow_test = x >= 1024.0;
    vx_floor = floor(x);
    vx_r = x - vx_floor;
    tmp = vx_r * 8.0;
    r_hi = rint(tmp);
    r_hi_int = r_hi;
    minmax_pred = r_hi_int < INT64_C(9);
    tmp1 = minmax_pred ? r_hi_int : INT64_C(9);
    minmax_pred1 = tmp1 > INT64_C(0);
    tmp2 = minmax_pred1 ? tmp1 : INT64_C(0);
    hi_part_value = exp2_double_x86_exp2_table[tmp2];
    vx_int = vx_floor;
    tmp3 = r_hi * 0.125;
    r_lo = vx_r - tmp3;
    pm_9 = r_lo * 0x1.1907a8c1c78c1p-27;
    pa_9 = 0x1.9de07f01b20bep-24 + pm_9;
    pm_8 = r_lo * pa_9;
    pa_8 = 0x1.62bcf28aeda6cp-20 + pm_8;
    pm_7 = r_lo * pa_8;
    pa_7 = 0x1.ffcdc44bc06d7p-17 + pm_7;
    pm_6 = r_lo * pa_7;
    pa_6 = 0x1.4309131068c2ap-13 + pm_6;
    pm_5 = r_lo * pa_6;
    pa_5 = 0x1.5d87fe6c9eeadp-10 + pm_5;
    pm_4 = r_lo * pa_5;
    pa_4 = 0x1.3b2ab6fba44fep-7 + pm_4;
    pm_3 = r_lo * pa_4;
    pa_3 = 0x1.c6b08d704a8c5p-5 + pm_3;
    pm_2 = r_lo * pa_3;
    pa_2 = 0x1.ebfbdff82c58fp-3 + pm_2;
    tmp4 = r_lo * pa_2;
    tmp5 = 0x1.62e42fefa39efp-1 + tmp4;
    poly = r_lo * tmp5;
    exp_X = ml_exp_insertion_fp64(vx_int);
    uflow_test = x < -1022.0;
    std_test = oflow_test || uflow_test;

    if (__builtin_expect(std_test, 0)) {


        if (__builtin_expect(oflow_test, 0)) {

            return INFINITY;
        } else {
            int sub_test;

            sub_test = x > -1074.0;

            if (__builtin_expect(sub_test, 0)) {
                double exp_min;
                int64_t tmp0;
                int64_t offset;
                double exp_offset;
                double tmp6;
                double tmp7;
                double tmp8;
                double tmp9;
                double tmp10;
                double tmp11;

                exp_min = ml_exp_insertion_fp64(INT32_C(-1022));
                tmp0 = INT64_C(-1022) - vx_int;
                offset =  - tmp0;
                exp_offset = ml_exp_insertion_fp64(offset);
                tmp6 = hi_part_value * exp_offset;
                tmp7 = tmp6 * exp_min;
                tmp8 = tmp7 * poly;
                tmp9 = hi_part_value * exp_offset;
                tmp10 = tmp9 * exp_min;
                tmp11 = tmp8 + tmp10;
                return tmp11;
            } else {

                return 0.0;
            }
        }
    } else {
        double tmp0;
        double tmp6;
        double tmp7;
        double result;

        tmp0 = hi_part_value * exp_X;
        tmp6 = tmp0 * poly;
        tmp7 = hi_part_value * exp_X;
        result = tmp6 + tmp7;
        return result;
    }
}
