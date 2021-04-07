/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 2 --language c \
 *     --accuracy cr --precision float --target x86 --output \
 *     GeneratedFunctions/cr/x86/log2_float_x86.c --fname log2_float_x86
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <math.h>


static const float ml_log1p_table[256]  = {
     0.0f, 0.0f, -0x1.6fe50cp-7f, 0x1.221ef6p-32f, -0x1.6e7968p-6f, -0x1.70b48ap-32f,
     -0x1.11cd1ep-5f, 0x1.5d997ep-30f, -0x1.6bad38p-5f, 0x1.4e205p-30f,
     -0x1.c4dfacp-5f, 0x1.bd5528p-31f, -0x1.0eb38ap-4f, 0x1.758196p-34f,
     -0x1.3aa2fep-4f, 0x1.6c071ep-31f, -0x1.663f7p-4f, 0x1.4dbb3ap-30f,
     -0x1.918a16p-4f, -0x1.c8c66cp-29f, -0x1.bc8424p-4f, -0x1.5b5774p-33f,
     -0x1.e72ec2p-4f, 0x1.d00b4ap-29f, -0x1.08c588p-3f, -0x1.9b4f3cp-28f,
     -0x1.1dcd1ap-3f, 0x1.155a9p-28f, -0x1.32ae9ep-3f, -0x1.3c570ep-30f,
     -0x1.476aap-3f, 0x1.9f022cp-29f, -0x1.5c01a4p-3f, 0x1.810a5ep-29f,
     -0x1.70742ep-3f, 0x1.621fbp-28f, -0x1.84c2bep-3f, 0x1.fa1f8ap-28f,
     -0x1.98eddp-3f, -0x1.df9c38p-29f, -0x1.acf5e2p-3f, -0x1.b69d92p-28f,
     -0x1.c0db6cp-3f, -0x1.bb29bep-28f, -0x1.d49ee4p-3f, -0x1.864b2ep-28f,
     -0x1.e840bep-3f, -0x1.d39a94p-29f, -0x1.fbc16cp-3f, 0x1.bf65fep-29f,
     -0x1.0790aep-2f, 0x1.13f3fep-28f, -0x1.11307ep-2f, 0x1.4b3d22p-28f,
     -0x1.1ac05cp-2f, 0x1.adc1f2p-27f, -0x1.24407ap-2f, -0x1.61c0e8p-27f,
     -0x1.2db11p-2f, 0x1.d932a8p-29f, -0x1.37124cp-2f, -0x1.d499bep-27f,
     -0x1.406464p-2f, 0x1.393eeep-28f, -0x1.49a784p-2f, -0x1.79a372p-27f,
     -0x1.52dbep-2f, 0x1.d9b4a6p-29f, -0x1.5c01a4p-2f, 0x1.810a5ep-28f,
     -0x1.6518fep-2f, -0x1.19deeap-28f, -0x1.6e221cp-2f, -0x1.b3a19cp-27f,
     -0x1.771d2cp-2f, 0x1.604132p-28f, -0x1.800a56p-2f, -0x1.8b0e2ap-29f,
     -0x1.88e9c8p-2f, 0x1.a3e9bcp-27f, -0x1.91bba8p-2f, -0x1.23e2e2p-27f,
     -0x1.9a8024p-2f, 0x1.b87734p-28f, -0x1.a3376p-2f, -0x1.4fec0ap-27f,
     -0x1.abe188p-2f, 0x1.a0382ep-28f, -0x1.b47ecp-2f, 0x1.18efacp-27f,
     -0x1.bd0f2ep-2f, -0x1.3cf206p-27f, -0x1.c592fap-2f, -0x1.a52b6ap-27f,
     -0x1.ce0a4ap-2f, 0x1.b8b4fp-27f, -0x1.d6753ep-2f, -0x1.975078p-33f,
     -0x1.ded3fep-2f, 0x1.77b936p-27f, -0x1.e726aap-2f, -0x1.e754d2p-30f,
     -0x1.ef6d68p-2f, 0x1.9ae3bcp-27f, -0x1.f7a856p-2f, -0x1.1960dap-27f,
     -0x1.ffd79ap-2f, 0x1.5f001ap-28f, 0x1.f804aep-2f, 0x1.1a19ap-27f, 0x1.efec62p-2f,
     -0x1.3fb81ep-28f, 0x1.e7df6p-2f, -0x1.ac754cp-30f, 0x1.dfdd8ap-2f,
     -0x1.53c8eap-29f, 0x1.d7e6cp-2f, 0x1.5786bp-27f, 0x1.cffae6p-2f, 0x1.1ad12cp-30f,
     0x1.c819dcp-2f, 0x1.6a2ff2p-29f, 0x1.c04386p-2f, -0x1.874094p-28f,
     0x1.b877c6p-2f, -0x1.09c9f2p-27f, 0x1.b0b68p-2f, -0x1.6172fep-27f,
     0x1.a8ff98p-2f, -0x1.cfdeb4p-27f, 0x1.a152f2p-2f, -0x1.7acfcap-27f,
     0x1.99b072p-2f, 0x1.52d8d6p-27f, 0x1.9218p-2f, 0x1.249ba8p-27f, 0x1.8a898p-2f,
     0x1.57f7a6p-27f, 0x1.8304dap-2f, -0x1.e7dc06p-27f, 0x1.7b89fp-2f,
     0x1.679556p-29f, 0x1.7418acp-2f, 0x1.d77e32p-27f, 0x1.6cb0f6p-2f,
     0x1.0cb91ep-27f, 0x1.6552b4p-2f, 0x1.330c4ep-27f, 0x1.5dfddp-2f,
     -0x1.c22a3ep-27f, 0x1.56b22ep-2f, 0x1.ad5e3ap-28f, 0x1.4f6fbcp-2f,
     -0x1.a6274cp-27f, 0x1.48365ep-2f, 0x1.a575e6p-28f, 0x1.410602p-2f,
     -0x1.07826cp-27f, 0x1.39de8ep-2f, 0x1.559f7p-30f, 0x1.32bfeep-2f,
     0x1.b87734p-29f, 0x1.2baa0cp-2f, 0x1.a5f0f6p-29f, 0x1.249cd2p-2f,
     0x1.6279aep-27f, 0x1.1d982cp-2f, 0x1.3aa4e2p-27f, 0x1.169c06p-2f,
     -0x1.9381d4p-27f, 0x1.0fa848p-2f, 0x1.12cd44p-32f, 0x1.08bcep-2f,
     0x1.b2bf46p-27f, 0x1.01d9bcp-2f, -0x1.82cf16p-29f, 0x1.f5fd8ap-3f,
     0x1.20c7c6p-28f, 0x1.e857d4p-3f, -0x1.64f64cp-30f, 0x1.dac22ep-3f,
     -0x1.8377c6p-28f, 0x1.cd3c72p-3f, -0x1.a59ddep-28f, 0x1.bfc67ap-3f,
     0x1.fffd34p-29f, 0x1.b26024p-3f, 0x1.2faa68p-28f, 0x1.a5094cp-3f,
     -0x1.565afap-28f, 0x1.97c1ccp-3f, -0x1.d87028p-28f, 0x1.8a898p-3f,
     0x1.57f7a6p-28f, 0x1.7d604ap-3f, -0x1.260896p-28f, 0x1.704604p-3f,
     -0x1.c70c1p-28f, 0x1.633a8cp-3f, -0x1.79063ep-32f, 0x1.563dc2p-3f,
     0x1.3ff596p-28f, 0x1.494f86p-3f, 0x1.dc6f9ap-30f, 0x1.3c6fb6p-3f,
     0x1.433794p-29f, 0x1.2f9e32p-3f, 0x1.ab7fbap-28f, 0x1.22dadcp-3f,
     0x1.559a4cp-30f, 0x1.162594p-3f, -0x1.cf24b2p-28f, 0x1.097e38p-3f,
     0x1.9cc0cap-28f, 0x1.f9c95ep-4f, -0x1.f1774ep-31f, 0x1.e0b1aep-4f,
     0x1.1e5faap-29f, 0x1.c7b528p-4f, 0x1.6e1e38p-29f, 0x1.aed392p-4f,
     -0x1.52662cp-30f, 0x1.960cbp-4f, -0x1.95120ep-30f, 0x1.7d604ap-4f,
     -0x1.260896p-29f, 0x1.64ce26p-4f, 0x1.80ce2ap-29f, 0x1.4c561p-4f,
     -0x1.975078p-32f, 0x1.33f7cep-4f, -0x1.eb30a6p-32f, 0x1.1bb32ap-4f,
     0x1.801528p-30f, 0x1.0387fp-4f, -0x1.0d5e58p-30f, 0x1.d6ebd2p-5f,
     -0x1.c02804p-34f, 0x1.a6f9c4p-5f, -0x1.10459cp-30f, 0x1.77394cp-5f,
     0x1.3b2b1ap-30f, 0x1.47aa08p-5f, -0x1.9511f6p-30f, 0x1.184b8ep-5f,
     0x1.315abep-31f, 0x1.d23afcp-6f, 0x1.244e7ep-32f, 0x1.743ee8p-6f,
     0x1.87cd56p-32f, 0x1.16a21ep-6f, 0x1.050522p-33f, 0x1.72c7bap-7f,
     0x1.07b994p-34f, 0x1.720d9cp-8f, 0x1.aa0d7ap-38f
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

float log2_float_x86(float);
float log2_float_x86(float x){
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
    int tmp17;
    int32_t tmp18;
    int32_t tau;
    uint32_t exponent_srl_cast;
    int32_t tmp19;
    int32_t tmp20;
    int32_t tmp_eptau;
    int32_t tmp21;
    float fp_exponent;
    float tmp22;
    float carg;
    float u;
    float tmp23;
    float carg1;
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
    float tmp35;
    float tmp36;
    float tmp37;
    float tmp38;
    float tmp39;
    float carg2;
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
    float tmp53;
    float tmp54;
    float tmp55;
    float tmp56;
    float tmp57;
    float carg3;
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
    float tmp71;
    float tmp72;
    float tmp73;
    float tmp74;
    float tmp75;
    float carg4;
    float tmp76;
    float tmp77;
    float tmp78;
    float tmp79;
    float tmp80;
    float tmp81;
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
    float tmp93;
    float carg5;
    float tmp94;
    float tmp95;
    float tmp96;
    float tmp97;
    float tmp98;
    float log1pu_poly_hi;
    float tmp99;
    float tmp100;
    float log1pu_poly_lo;
    float tmp101;
    float tmp102;
    float tmp103;
    float tmp104;
    float tmp105;
    float tmp106;
    float tmp107;
    float tmp108;
    float tmp109;
    float tmp110;
    float tmp111;
    float tmp112;
    float tmp113;
    uint32_t table_index_lo;
    float tbl_lo;
    float tmp114;
    float tmp115;
    float tmp116;
    float tmp117;
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
    tmp17 = ( (int32_t) table_index) > INT32_C(53);
    tmp18 = tmp17 ? INT32_C(-1) : INT32_C(0);
    tau = tmp18 + INT32_C(1);
    exponent_srl_cast = tmp6;
    tmp19 = exponent_srl_cast >> INT32_C(23);
    tmp20 = tmp19 + INT32_C(-127);
    tmp_eptau = tmp20 + tau;
    tmp21 = tmp_eptau - alpha;
    fp_exponent = tmp21;
    tmp22 = float_from_32b_encoding(ri_fast_rndn);
    carg =  - 1.0f;
    u = fmaf(tmp7, tmp22, carg);
    tmp23 = u * 0x1.27791ep-2f;
    carg1 =  - tmp23;
    tmp24 = fmaf(u, 0x1.27791ep-2f, carg1);
    tmp25 = u * -0x1.62e9cp-29f;
    tmp26 = tmp24 + tmp25;
    tmp27 = tmp23 + tmp26;
    tmp28 = -0x1.71561p-2f + tmp27;
    tmp29 = tmp28 - tmp27;
    tmp30 = -0x1.71561p-2f - tmp29;
    tmp31 = tmp28 - tmp29;
    tmp32 = tmp27 - tmp31;
    tmp33 = tmp30 + tmp32;
    tmp34 = tmp27 - tmp23;
    tmp35 = tmp26 - tmp34;
    tmp36 = -0x1.6a353cp-27f + tmp35;
    tmp37 = tmp33 + tmp36;
    tmp38 = tmp28 + tmp37;
    tmp39 = u * tmp38;
    carg2 =  - tmp39;
    tmp40 = fmaf(u, tmp38, carg2);
    tmp41 = tmp38 - tmp28;
    tmp42 = tmp37 - tmp41;
    tmp43 = u * tmp42;
    tmp44 = tmp40 + tmp43;
    tmp45 = tmp39 + tmp44;
    tmp46 = 0x1.ec709ep-2f + tmp45;
    tmp47 = tmp46 - tmp45;
    tmp48 = 0x1.ec709ep-2f - tmp47;
    tmp49 = tmp46 - tmp47;
    tmp50 = tmp45 - tmp49;
    tmp51 = tmp48 + tmp50;
    tmp52 = tmp45 - tmp39;
    tmp53 = tmp44 - tmp52;
    tmp54 = -0x1.f30a38p-29f + tmp53;
    tmp55 = tmp51 + tmp54;
    tmp56 = tmp46 + tmp55;
    tmp57 = u * tmp56;
    carg3 =  - tmp57;
    tmp58 = fmaf(u, tmp56, carg3);
    tmp59 = tmp56 - tmp46;
    tmp60 = tmp55 - tmp59;
    tmp61 = u * tmp60;
    tmp62 = tmp58 + tmp61;
    tmp63 = tmp57 + tmp62;
    tmp64 = -0x1.715476p-1f + tmp63;
    tmp65 = tmp64 - tmp63;
    tmp66 = -0x1.715476p-1f - tmp65;
    tmp67 = tmp64 - tmp65;
    tmp68 = tmp63 - tmp67;
    tmp69 = tmp66 + tmp68;
    tmp70 = tmp63 - tmp57;
    tmp71 = tmp62 - tmp70;
    tmp72 = -0x1.49b0cp-27f + tmp71;
    tmp73 = tmp69 + tmp72;
    tmp74 = tmp64 + tmp73;
    tmp75 = u * tmp74;
    carg4 =  - tmp75;
    tmp76 = fmaf(u, tmp74, carg4);
    tmp77 = tmp74 - tmp64;
    tmp78 = tmp73 - tmp77;
    tmp79 = u * tmp78;
    tmp80 = tmp76 + tmp79;
    tmp81 = tmp75 + tmp80;
    tmp82 = 0x1.715476p0f + tmp81;
    tmp83 = tmp82 - tmp81;
    tmp84 = 0x1.715476p0f - tmp83;
    tmp85 = tmp82 - tmp83;
    tmp86 = tmp81 - tmp85;
    tmp87 = tmp84 + tmp86;
    tmp88 = tmp81 - tmp75;
    tmp89 = tmp80 - tmp88;
    tmp90 = 0x1.4ae0cp-26f + tmp89;
    tmp91 = tmp87 + tmp90;
    tmp92 = tmp82 + tmp91;
    tmp93 = u * tmp92;
    carg5 =  - tmp93;
    tmp94 = fmaf(u, tmp92, carg5);
    tmp95 = tmp92 - tmp82;
    tmp96 = tmp91 - tmp95;
    tmp97 = u * tmp96;
    tmp98 = tmp94 + tmp97;
    log1pu_poly_hi = tmp93 + tmp98;
    tmp99 = fp_exponent + log1pu_poly_hi;
    tmp100 = log1pu_poly_hi - tmp93;
    log1pu_poly_lo = tmp98 - tmp100;
    tmp101 = tmp99 - log1pu_poly_hi;
    tmp102 = fp_exponent - tmp101;
    tmp103 = tmp99 - tmp101;
    tmp104 = log1pu_poly_hi - tmp103;
    tmp105 = tmp102 + tmp104;
    tmp106 = tmp105 + log1pu_poly_lo;
    tmp107 = tmp99 + tmp106;
    tmp108 = tmp107 + tbl_hi;
    tmp109 = tmp108 - tbl_hi;
    tmp110 = tmp107 - tmp109;
    tmp111 = tmp108 - tmp109;
    tmp112 = tbl_hi - tmp111;
    tmp113 = tmp110 + tmp112;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp114 = tmp107 - tmp99;
    tmp115 = tmp106 - tmp114;
    tmp116 = tmp115 + tbl_lo;
    tmp117 = tmp113 + tmp116;
    logx_hi = tmp108 + tmp117;
    return logx_hi;
}
