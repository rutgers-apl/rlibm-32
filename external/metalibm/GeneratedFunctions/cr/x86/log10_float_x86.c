/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 10 --language c \
 *     --accuracy cr --precision float --target x86 --output \
 *     GeneratedFunctions/cr/x86/log10_float_x86.c --fname log10_float_x86
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <math.h>


static const float ml_log1p_table[256]  = {
     0.0f, 0.0f, -0x1.bafd48p-9f, 0x1.bbc25cp-34f, -0x1.b9476ap-8f, -0x1.3f3444p-34f,
     -0x1.49b086p-7f, 0x1.d7793p-32f, -0x1.b5e908p-7f, -0x1.d626f2p-32f,
     -0x1.10a83ap-6f, -0x1.088d8ep-31f, -0x1.45f4f6p-6f, 0x1.4d1d08p-32f,
     -0x1.7adc3ep-6f, 0x1.89c01p-35f, -0x1.af5f92p-6f, -0x1.601cc2p-31f,
     -0x1.e3806ap-6f, -0x1.97a0b2p-31f, -0x1.0ba01ap-5f, -0x1.02ep-30f,
     -0x1.25502cp-5f, -0x1.f86298p-34f, -0x1.3ed11ap-5f, 0x1.9686f6p-31f,
     -0x1.58238ep-5f, -0x1.d66a7cp-30f, -0x1.714834p-5f, -0x1.3e954cp-32f,
     -0x1.8a3faep-5f, 0x1.47b80cp-33f, -0x1.a30a9ep-5f, 0x1.3ec202p-30f,
     -0x1.bba9ap-5f, -0x1.637f62p-31f, -0x1.d41d52p-5f, 0x1.360a6ap-30f,
     -0x1.ec6648p-5f, 0x1.4a77f8p-33f, -0x1.02428cp-4f, -0x1.f08016p-32f,
     -0x1.0e3d2ap-4f, 0x1.3f74dp-31f, -0x1.1a2344p-4f, -0x1.540606p-30f,
     -0x1.25f522p-4f, 0x1.4294d6p-29f, -0x1.31b306p-4f, 0x1.4771dcp-29f,
     -0x1.3d5d34p-4f, 0x1.4759dp-29f, -0x1.48f3eep-4f, 0x1.c416ep-29f,
     -0x1.547774p-4f, 0x1.cd183p-29f, -0x1.5fe804p-4f, -0x1.115eap-29f,
     -0x1.6b45ep-4f, 0x1.2183a6p-29f, -0x1.76914p-4f, -0x1.44a4ep-29f,
     -0x1.81ca64p-4f, 0x1.7d2ddcp-31f, -0x1.8cf184p-4f, 0x1.de6dfcp-30f,
     -0x1.9806dap-4f, 0x1.7d6bbep-29f, -0x1.a30a9ep-4f, 0x1.3ec202p-29f,
     -0x1.adfd08p-4f, 0x1.7d284p-29f, -0x1.b8de4ep-4f, 0x1.8a984ep-29f,
     -0x1.c3aea4p-4f, -0x1.4b8dep-29f, -0x1.ce6e42p-4f, 0x1.b9c25cp-32f,
     -0x1.d91d58p-4f, -0x1.9aaa66p-30f, -0x1.e3bc1ap-4f, -0x1.61c34p-29f,
     -0x1.ee4abap-4f, -0x1.843c82p-30f, -0x1.f8c968p-4f, -0x1.a340c8p-31f,
     -0x1.019c2ap-3f, -0x1.92d21ap-33f, -0x1.06cbd6p-3f, -0x1.e9b0eep-29f,
     -0x1.0bf3dp-3f, -0x1.26f884p-28f, -0x1.11143p-3f, 0x1.efdd96p-28f,
     -0x1.162d08p-3f, -0x1.564e88p-30f, -0x1.1b3e72p-3f, 0x1.36b086p-31f,
     -0x1.204882p-3f, 0x1.08bc44p-30f, -0x1.254b4ep-3f, 0x1.943058p-28f,
     -0x1.2a46e8p-3f, -0x1.94f746p-28f, -0x1.2f3b6ap-3f, 0x1.c74cp-28f,
     -0x1.3428e2p-3f, -0x1.50025cp-29f, 0x1.2f7302p-3f, -0x1.858bc2p-30f,
     0x1.2a935cp-3f, -0x1.683ae2p-29f, 0x1.25ba82p-3f, 0x1.5af7fcp-31f,
     0x1.20e862p-3f, 0x1.00e3fcp-29f, 0x1.1c1ceap-3f, -0x1.aa8fcep-29f,
     0x1.175806p-3f, -0x1.753c2p-30f, 0x1.1299a4p-3f, 0x1.f67c6p-28f, 0x1.0de1b6p-3f,
     -0x1.3952ap-28f, 0x1.093026p-3f, -0x1.799a26p-29f, 0x1.0484e4p-3f,
     0x1.285548p-28f, 0x1.ffbfc2p-4f, 0x1.778fp-29f, 0x1.f68216p-4f, 0x1.9398e4p-29f,
     0x1.ed50a4p-4f, 0x1.44dd6p-29f, 0x1.e42b4cp-4f, 0x1.6caaf2p-32f, 0x1.db11eep-4f,
     -0x1.132a82p-29f, 0x1.d2046ap-4f, -0x1.cd2f5p-30f, 0x1.c902a2p-4f,
     -0x1.866bbcp-30f, 0x1.c00c78p-4f, -0x1.31bb46p-29f, 0x1.b721cep-4f,
     -0x1.d1d504p-29f, 0x1.ae4286p-4f, -0x1.5ecd5ep-29f, 0x1.a56e84p-4f,
     -0x1.b4147p-29f, 0x1.9ca5aap-4f, 0x1.729f44p-32f, 0x1.93e7dep-4f, 0x1.f87dp-33f,
     0x1.8b3504p-4f, -0x1.3673b6p-29f, 0x1.828cfep-4f, 0x1.a53442p-29f,
     0x1.79efb6p-4f, -0x1.09e1p-29f, 0x1.715d0cp-4f, 0x1.c6cf6p-29f, 0x1.68d4eap-4f,
     0x1.e4dafep-29f, 0x1.605736p-4f, -0x1.167a1p-32f, 0x1.57e3d4p-4f,
     0x1.f0ebdep-30f, 0x1.4f7aaep-4f, -0x1.910d14p-30f, 0x1.471ba8p-4f,
     0x1.4fbc56p-29f, 0x1.3ec6aep-4f, -0x1.57f0f2p-29f, 0x1.367ba4p-4f,
     -0x1.5579ep-30f, 0x1.2e3a74p-4f, 0x1.6f001ep-33f, 0x1.260308p-4f,
     -0x1.abb41p-29f, 0x1.1dd546p-4f, 0x1.9162dep-33f, 0x1.15b11ap-4f,
     0x1.294354p-33f, 0x1.0d966cp-4f, 0x1.8ca02p-29f, 0x1.058528p-4f, 0x1.bb20bcp-31f,
     0x1.fafa6ep-5f, -0x1.8d0204p-30f, 0x1.eafd06p-5f, -0x1.f94858p-30f,
     0x1.db11eep-5f, -0x1.132a82p-30f, 0x1.cb38fcp-5f, 0x1.9b17fcp-30f,
     0x1.bb720ap-5f, -0x1.70ed8ep-32f, 0x1.abbcecp-5f, -0x1.3d81bp-32f,
     0x1.9c197ap-5f, 0x1.7e01bap-30f, 0x1.8c878ep-5f, 0x1.d60a0ep-30f, 0x1.7d0702p-5f,
     -0x1.741606p-30f, 0x1.6d97acp-5f, -0x1.88b43ep-30f, 0x1.5e3966p-5f,
     0x1.6fd252p-30f, 0x1.4eec0ep-5f, 0x1.22c798p-32f, 0x1.3faf7cp-5f,
     0x1.98c184p-31f, 0x1.30838cp-5f, 0x1.b85f8p-30f, 0x1.21681cp-5f,
     -0x1.46e7bep-30f, 0x1.125d04p-5f, 0x1.975106p-32f, 0x1.036224p-5f,
     0x1.e638ecp-33f, 0x1.e8eebp-6f, 0x1.3e5edap-31f, 0x1.cb38fcp-6f, 0x1.9b17fcp-31f,
     0x1.ada2e8p-6f, 0x1.c7ca8ep-31f, 0x1.902c32p-6f, -0x1.4eabdep-33f,
     0x1.72d496p-6f, -0x1.26bbf4p-31f, 0x1.559bd2p-6f, 0x1.01b0eep-32f,
     0x1.3881a8p-6f, -0x1.1f9c18p-32f, 0x1.1b85d6p-6f, 0x1.13a6b8p-36f,
     0x1.fd503cp-7f, 0x1.c8278ep-34f, 0x1.c3d084p-7f, -0x1.10f678p-32f,
     0x1.8a8c06p-7f, 0x1.763a5ep-32f, 0x1.51824cp-7f, 0x1.d61facp-33f, 0x1.18b2dcp-7f,
     0x1.1a5772p-32f, 0x1.c03a8p-8f, 0x1.5cbc0ap-33f, 0x1.4f8206p-8f,
     -0x1.b95dfap-33f, 0x1.be76bep-9f, -0x1.109608p-34f, 0x1.bd96a2p-10f,
     -0x1.4131a2p-37f
};
static const float table[128]  = {
     0x1p0f, 0x1.fcp-1f, 0x1.f8p-1f, 0x1.f4p-1f, 0x1.fp-1f, 0x1.edp-1f, 0x1.e9p-1f,
     0x1.e5p-1f, 0x1.e2p-1f, 0x1.dep-1f, 0x1.dbp-1f, 0x1.d7p-1f, 0x1.d4p-1f,
     0x1.d1p-1f, 0x1.cep-1f, 0x1.cap-1f, 0x1.c7p-1f, 0x1.c4p-1f, 0x1.c1p-1f,
     0x1.bep-1f, 0x1.bbp-1f, 0x1.b8p-1f, 0x1.b5p-1f, 0x1.b2p-1f, 0x1.afp-1f,
     0x1.acp-1f, 0x1.aap-1f, 0x1.a7p-1f, 0x1.a4p-1f, 0x1.a1p-1f, 0x1.9fp-1f,
     0x1.9cp-1f, 0x1.9ap-1f, 0x1.97p-1f, 0x1.95p-1f, 0x1.92p-1f, 0x1.9p-1f,
     0x1.8dp-1f, 0x1.8bp-1f, 0x1.88p-1f, 0x1.86p-1f, 0x1.84p-1f, 0x1.82p-1f,
     0x1.7fp-1f, 0x1.7dp-1f, 0x1.7bp-1f, 0x1.79p-1f, 0x1.76p-1f, 0x1.74p-1f,
     0x1.72p-1f, 0x1.7p-1f, 0x1.6ep-1f, 0x1.6cp-1f, 0x1.6ap-1f, 0x1.68p-1f,
     0x1.66p-1f, 0x1.64p-1f, 0x1.62p-1f, 0x1.6p-1f, 0x1.5ep-1f, 0x1.5dp-1f,
     0x1.5bp-1f, 0x1.59p-1f, 0x1.57p-1f, 0x1.55p-1f, 0x1.54p-1f, 0x1.52p-1f,
     0x1.5p-1f, 0x1.4ep-1f, 0x1.4dp-1f, 0x1.4bp-1f, 0x1.49p-1f, 0x1.48p-1f,
     0x1.46p-1f, 0x1.44p-1f, 0x1.43p-1f, 0x1.41p-1f, 0x1.4p-1f, 0x1.3ep-1f,
     0x1.3dp-1f, 0x1.3bp-1f, 0x1.3ap-1f, 0x1.38p-1f, 0x1.37p-1f, 0x1.35p-1f,
     0x1.34p-1f, 0x1.32p-1f, 0x1.31p-1f, 0x1.2fp-1f, 0x1.2ep-1f, 0x1.2dp-1f,
     0x1.2bp-1f, 0x1.2ap-1f, 0x1.29p-1f, 0x1.27p-1f, 0x1.26p-1f, 0x1.25p-1f,
     0x1.23p-1f, 0x1.22p-1f, 0x1.21p-1f, 0x1.1fp-1f, 0x1.1ep-1f, 0x1.1dp-1f,
     0x1.1cp-1f, 0x1.1ap-1f, 0x1.19p-1f, 0x1.18p-1f, 0x1.17p-1f, 0x1.16p-1f,
     0x1.15p-1f, 0x1.13p-1f, 0x1.12p-1f, 0x1.11p-1f, 0x1.1p-1f, 0x1.0fp-1f,
     0x1.0ep-1f, 0x1.0dp-1f, 0x1.0bp-1f, 0x1.0ap-1f, 0x1.09p-1f, 0x1.08p-1f,
     0x1.07p-1f, 0x1.06p-1f, 0x1.05p-1f, 0x1.04p-1f, 0x1.03p-1f, 0x1.02p-1f,
     0x1.01p-1f
};

float log10_float_x86(float);
float log10_float_x86(float x){
    int32_t vx_as_int;
    int32_t tmp;
    int tmp1;
    int32_t is_subnormal;
    uint32_t fp_one_as_uint;
    uint32_t vx_as_uint;
    uint32_t Zi;
    float tmp2;
    float Zf;
    int32_t tmp3;
    uint32_t _srl_cast;
    int32_t tmp4;
    int32_t tmp5;
    int32_t n_value;
    int32_t alpha;
    int32_t tmp6;
    float normal_vx;
    float tmp7;
    int32_t tmp8;
    uint32_t _srl_cast1;
    int32_t tmp9;
    int32_t inv_index;
    float tmp10;
    float tmp11;
    int32_t op_exp;
    int32_t tmp12;
    float approx_exp;
    float tmp13;
    float inv_approx;
    int32_t tmp14;
    int32_t tmp15;
    uint32_t id_tmp;
    uint32_t ri_fast_rndn;
    uint32_t ri_bits;
    uint32_t table_index;
    uint32_t tmp16;
    uint32_t table_index_hi;
    float tbl_hi;
    float tmp17;
    float carg;
    float u;
    float tmp18;
    float carg1;
    float tmp19;
    float tmp20;
    float tmp21;
    float tmp22;
    float tmp23;
    float tmp24;
    float tmp25;
    float tmp26;
    float tmp27;
    float tmp28;
    float tmp29;
    float tmp30;
    float tmp31;
    float tmp32;
    float tmp33;
    float tmp34;
    float carg2;
    float tmp35;
    float tmp36;
    float tmp37;
    float tmp38;
    float tmp39;
    float tmp40;
    float tmp41;
    float tmp42;
    float tmp43;
    float tmp44;
    float tmp45;
    float tmp46;
    float tmp47;
    float tmp48;
    float tmp49;
    float tmp50;
    float tmp51;
    float tmp52;
    float carg3;
    float tmp53;
    float tmp54;
    float tmp55;
    float tmp56;
    float tmp57;
    float tmp58;
    float tmp59;
    float tmp60;
    float tmp61;
    float tmp62;
    float tmp63;
    float tmp64;
    float tmp65;
    float tmp66;
    float tmp67;
    float tmp68;
    float tmp69;
    float tmp70;
    float carg4;
    float tmp71;
    float tmp72;
    float tmp73;
    float tmp74;
    float tmp75;
    float log1pu_poly_hi;
    int tmp76;
    int32_t tmp77;
    int32_t tau;
    uint32_t exponent_srl_cast;
    int32_t tmp78;
    int32_t tmp79;
    int32_t tmp_eptau;
    int32_t tmp80;
    float fp_exponent;
    float tmp81;
    float carg5;
    float tmp82;
    float tmp83;
    float tmp84;
    float tmp85;
    float tmp86;
    float tmp87;
    float tmp88;
    float tmp89;
    float tmp90;
    float tmp91;
    float tmp92;
    float log1pu_poly_lo;
    float tmp93;
    float tmp94;
    float tmp95;
    float tmp96;
    float tmp97;
    float tmp98;
    float tmp99;
    float tmp100;
    float tmp101;
    float tmp102;
    float tmp103;
    uint32_t table_index_lo;
    float tbl_lo;
    float tmp104;
    float tmp105;
    float tmp106;
    float tmp107;
    float logx_hi;
    
    vx_as_int = float_to_32b_encoding(x);
    tmp = vx_as_int - INT32_C(1);
    tmp1 = tmp < INT32_C(8388607);
    is_subnormal = tmp1 ? INT32_C(-1) : INT32_C(0);
    fp_one_as_uint = float_to_32b_encoding(1.0f);
    vx_as_uint = float_to_32b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp2 = float_from_32b_encoding(Zi);
    Zf = tmp2 - 1.0f;
    tmp3 = float_to_32b_encoding(Zf);
    _srl_cast = tmp3;
    tmp4 = _srl_cast >> INT32_C(23);
    tmp5 = tmp4 + INT32_C(-127);
    n_value = tmp5 & is_subnormal;
    alpha =  - n_value;
    tmp6 = vx_as_int << alpha;
    normal_vx = float_from_32b_encoding(tmp6);
    tmp7 = ml_mantissa_extraction_fp32(normal_vx);
    tmp8 = float_to_32b_encoding(tmp7);
    _srl_cast1 = tmp8;
    tmp9 = _srl_cast1 >> INT32_C(16);
    inv_index = tmp9 & INT32_C(127);
    tmp10 = table[inv_index];
    tmp11 = copysignf(1.0f, tmp7);
    op_exp = ml_exp_extraction_dirty_fp32(tmp7);
    tmp12 =  - op_exp;
    approx_exp = ml_exp_insertion_fp32(tmp12);
    tmp13 = approx_exp * tmp11;
    inv_approx = tmp10 * tmp13;
    tmp14 = float_to_32b_encoding(inv_approx);
    tmp15 = tmp14 + INT32_C(32768);
    id_tmp = tmp15;
    ri_fast_rndn = id_tmp & UINT32_C(-65536);
    ri_bits = ri_fast_rndn >> UINT32_C(16);
    table_index = ri_bits & UINT32_C(255);
    tmp16 = table_index & UINT32_C(127);
    table_index_hi = tmp16 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp17 = float_from_32b_encoding(ri_fast_rndn);
    carg =  - 1.0f;
    u = fmaf(tmp7, tmp17, carg);
    tmp18 = u * -0x1.bcb9fcp-4f;
    carg1 =  - tmp18;
    tmp19 = fmaf(u, -0x1.bcb9fcp-4f, carg1);
    tmp20 = u * -0x1.e505acp-30f;
    tmp21 = tmp19 + tmp20;
    tmp22 = tmp18 + tmp21;
    tmp23 = 0x1.287b8p-3f + tmp22;
    tmp24 = tmp23 - tmp22;
    tmp25 = 0x1.287b8p-3f - tmp24;
    tmp26 = tmp23 - tmp24;
    tmp27 = tmp22 - tmp26;
    tmp28 = tmp25 + tmp27;
    tmp29 = tmp22 - tmp18;
    tmp30 = tmp21 - tmp29;
    tmp31 = 0x1.3cf4f8p-29f + tmp30;
    tmp32 = tmp28 + tmp31;
    tmp33 = tmp23 + tmp32;
    tmp34 = u * tmp33;
    carg2 =  - tmp34;
    tmp35 = fmaf(u, tmp33, carg2);
    tmp36 = tmp33 - tmp23;
    tmp37 = tmp32 - tmp36;
    tmp38 = u * tmp37;
    tmp39 = tmp35 + tmp38;
    tmp40 = tmp34 + tmp39;
    tmp41 = -0x1.bcb7b2p-3f + tmp40;
    tmp42 = tmp41 - tmp40;
    tmp43 = -0x1.bcb7b2p-3f - tmp42;
    tmp44 = tmp41 - tmp42;
    tmp45 = tmp40 - tmp44;
    tmp46 = tmp43 + tmp45;
    tmp47 = tmp40 - tmp34;
    tmp48 = tmp39 - tmp47;
    tmp49 = 0x1.5c396p-28f + tmp48;
    tmp50 = tmp46 + tmp49;
    tmp51 = tmp41 + tmp50;
    tmp52 = u * tmp51;
    carg3 =  - tmp52;
    tmp53 = fmaf(u, tmp51, carg3);
    tmp54 = tmp51 - tmp41;
    tmp55 = tmp50 - tmp54;
    tmp56 = u * tmp55;
    tmp57 = tmp53 + tmp56;
    tmp58 = tmp52 + tmp57;
    tmp59 = 0x1.bcb7b2p-2f + tmp58;
    tmp60 = tmp59 - tmp58;
    tmp61 = 0x1.bcb7b2p-2f - tmp60;
    tmp62 = tmp59 - tmp60;
    tmp63 = tmp58 - tmp62;
    tmp64 = tmp61 + tmp63;
    tmp65 = tmp58 - tmp52;
    tmp66 = tmp57 - tmp65;
    tmp67 = -0x1.5b72fp-27f + tmp66;
    tmp68 = tmp64 + tmp67;
    tmp69 = tmp59 + tmp68;
    tmp70 = u * tmp69;
    carg4 =  - tmp70;
    tmp71 = fmaf(u, tmp69, carg4);
    tmp72 = tmp69 - tmp59;
    tmp73 = tmp68 - tmp72;
    tmp74 = u * tmp73;
    tmp75 = tmp71 + tmp74;
    log1pu_poly_hi = tmp70 + tmp75;
    tmp76 = ( (int32_t) table_index) > INT32_C(53);
    tmp77 = tmp76 ? INT32_C(-1) : INT32_C(0);
    tau = tmp77 + INT32_C(1);
    exponent_srl_cast = tmp6;
    tmp78 = exponent_srl_cast >> INT32_C(23);
    tmp79 = tmp78 + INT32_C(-127);
    tmp_eptau = tmp79 + tau;
    tmp80 = tmp_eptau - alpha;
    fp_exponent = tmp80;
    tmp81 = fp_exponent * 0x1.344136p-2f;
    carg5 =  - tmp81;
    tmp82 = fmaf(fp_exponent, 0x1.344136p-2f, carg5);
    tmp83 = fp_exponent * -0x1.ec10cp-27f;
    tmp84 = tmp82 + tmp83;
    tmp85 = tmp81 + tmp84;
    tmp86 = tmp85 + log1pu_poly_hi;
    tmp87 = tmp86 - log1pu_poly_hi;
    tmp88 = tmp85 - tmp87;
    tmp89 = tmp86 - tmp87;
    tmp90 = log1pu_poly_hi - tmp89;
    tmp91 = tmp88 + tmp90;
    tmp92 = log1pu_poly_hi - tmp70;
    log1pu_poly_lo = tmp75 - tmp92;
    tmp93 = tmp85 - tmp81;
    tmp94 = tmp84 - tmp93;
    tmp95 = tmp94 + log1pu_poly_lo;
    tmp96 = tmp91 + tmp95;
    tmp97 = tmp86 + tmp96;
    tmp98 = tmp97 + tbl_hi;
    tmp99 = tmp98 - tbl_hi;
    tmp100 = tmp97 - tmp99;
    tmp101 = tmp98 - tmp99;
    tmp102 = tbl_hi - tmp101;
    tmp103 = tmp100 + tmp102;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp104 = tmp97 - tmp86;
    tmp105 = tmp96 - tmp104;
    tmp106 = tmp105 + tbl_lo;
    tmp107 = tmp103 + tmp106;
    logx_hi = tmp98 + tmp107;
    return logx_hi;
}
