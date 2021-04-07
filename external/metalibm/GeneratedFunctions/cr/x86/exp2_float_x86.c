/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_exp2.py --language c --accuracy cr --precision \
 *     float --target x86 --output GeneratedFunctions/cr/x86/exp2_float_x86.c \
 *     --fname exp2_float_x86
 * 
**/
#include <stdint.h>
#include <math.h>
#include <ml_support_lib.h>


static const float exp2_float_x86_exp2_table[9]  = {
     0x1p0f, 0x1.172b84p0f, 0x1.306fep0f, 0x1.4bfdaep0f, 0x1.6a09e6p0f,
     0x1.8ace54p0f, 0x1.ae89fap0f, 0x1.d5818ep0f, 0x1p1f
};

float exp2_float_x86(float);
float exp2_float_x86(float x){
    int oflow_test;
    float vx_floor;
    float vx_r;
    float tmp;
    float r_hi;
    int32_t r_hi_int;
    int minmax_pred;
    int32_t tmp1;
    int minmax_pred1;
    int32_t tmp2;
    float hi_part_value;
    int32_t vx_int;
    float tmp3;
    float r_lo;
    float pm_5;
    float pa_5;
    float pm_4;
    float pa_4;
    float pm_3;
    float pa_3;
    float pm_2;
    float pa_2;
    float tmp4;
    float tmp5;
    float poly;
    float exp_X;
    int uflow_test;
    int std_test;
    
    oflow_test = x >= 128.0f;
    vx_floor = floorf(x);
    vx_r = x - vx_floor;
    tmp = vx_r * 8.0f;
    r_hi = rintf(tmp);
    r_hi_int = r_hi;
    minmax_pred = r_hi_int < INT32_C(9);
    tmp1 = minmax_pred ? r_hi_int : INT32_C(9);
    minmax_pred1 = tmp1 > INT32_C(0);
    tmp2 = minmax_pred1 ? tmp1 : INT32_C(0);
    hi_part_value = exp2_float_x86_exp2_table[tmp2];
    vx_int = vx_floor;
    tmp3 = r_hi * 0.125f;
    r_lo = vx_r - tmp3;
    pm_5 = r_lo * 0x1.45fcf6p-13f;
    pa_5 = 0x1.62554ap-10f + pm_5;
    pm_4 = r_lo * pa_5;
    pa_4 = 0x1.3b2a6cp-7f + pm_4;
    pm_3 = r_lo * pa_4;
    pa_3 = 0x1.c6afbap-5f + pm_3;
    pm_2 = r_lo * pa_3;
    pa_2 = 0x1.ebfbep-3f + pm_2;
    tmp4 = r_lo * pa_2;
    tmp5 = 0x1.62e43p-1f + tmp4;
    poly = r_lo * tmp5;
    exp_X = ml_exp_insertion_fp32(vx_int);
    uflow_test = x < -126.0f;
    std_test = oflow_test || uflow_test;

    if (__builtin_expect(std_test, 0)) {


        if (__builtin_expect(oflow_test, 0)) {

            return INFINITY;
        } else {
            int sub_test;

            sub_test = x > -149.0f;

            if (__builtin_expect(sub_test, 0)) {
                float exp_min;
                int32_t tmp0;
                int32_t offset;
                float exp_offset;
                float tmp6;
                float tmp7;
                float tmp8;
                float tmp9;
                float tmp10;
                float tmp11;

                exp_min = ml_exp_insertion_fp32(INT32_C(-126));
                tmp0 = INT32_C(-126) - vx_int;
                offset =  - tmp0;
                exp_offset = ml_exp_insertion_fp32(offset);
                tmp6 = hi_part_value * exp_offset;
                tmp7 = tmp6 * exp_min;
                tmp8 = tmp7 * poly;
                tmp9 = hi_part_value * exp_offset;
                tmp10 = tmp9 * exp_min;
                tmp11 = tmp8 + tmp10;
                return tmp11;
            } else {

                return 0.0f;
            }
        }
    } else {
        float tmp0;
        float tmp6;
        float tmp7;
        float result;

        tmp0 = hi_part_value * exp_X;
        tmp6 = tmp0 * poly;
        tmp7 = hi_part_value * exp_X;
        result = tmp6 + tmp7;
        return result;
    }
}
