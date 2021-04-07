/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix e --language c \
 *     --accuracy cr --precision float --target x86 --output \
 *     GeneratedFunctions/cr/x86/log_float_x86.c --fname log_float_x86
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <math.h>


static const float ml_log1p_table[256]  = {
     0.0f, 0.0f, -0x1.fe02a6p-8f, -0x1.620cf2p-33f, -0x1.fc0a8cp-7f, 0x1.e07f84p-32f,
     -0x1.7b91bp-6f, -0x1.f56c46p-32f, -0x1.f829bp-6f, -0x1.cf066p-31f,
     -0x1.39e87cp-5f, 0x1.8050a8p-31f, -0x1.77459p-5f, 0x1.39a46p-30f,
     -0x1.b42dd8p-5f, 0x1.dcd1c8p-30f, -0x1.f0a30cp-5f, -0x1.162a66p-37f,
     -0x1.16536ep-4f, -0x1.d46f5cp-29f, -0x1.341d7ap-4f, 0x1.3c85c6p-29f,
     -0x1.51b074p-4f, 0x1.f3cf82p-33f, -0x1.6f0d28p-4f, -0x1.5cad6ap-29f,
     -0x1.8c345ep-4f, 0x1.39cc9cp-29f, -0x1.a926d4p-4f, 0x1.6d4aa8p-30f,
     -0x1.c5e548p-4f, -0x1.eb78e8p-29f, -0x1.e27076p-4f, -0x1.c55e5cp-29f,
     -0x1.fec914p-4f, 0x1.c482a8p-29f, -0x1.0d77e8p-3f, 0x1.97b8d4p-30f,
     -0x1.1b72aep-3f, 0x1.5a130cp-28f, -0x1.29553p-3f, 0x1.f802b8p-29f,
     -0x1.371fc2p-3f, -0x1.e8f744p-35f, -0x1.44d2b6p-3f, -0x1.996fa4p-28f,
     -0x1.526e5ep-3f, -0x1.d0da1cp-30f, -0x1.5ff308p-3f, 0x1.eb0d86p-28f,
     -0x1.6d60fep-3f, -0x1.c67488p-29f, -0x1.7ab89p-3f, -0x1.086c84p-30f,
     -0x1.87fa06p-3f, -0x1.483244p-29f, -0x1.9525aap-3f, 0x1.85d4a6p-30f,
     -0x1.a23bc2p-3f, 0x1.d4a9cep-35f, -0x1.af3c94p-3f, -0x1.d017fep-28f,
     -0x1.bc2868p-3f, 0x1.7a4e66p-28f, -0x1.c8ff7cp-3f, -0x1.e6a688p-29f,
     -0x1.d5c216p-3f, -0x1.69f772p-28f, -0x1.e27076p-3f, -0x1.c55e5cp-28f,
     -0x1.ef0adcp-3f, -0x1.7b8b26p-28f, -0x1.fb9186p-3f, -0x1.abc7c6p-28f,
     -0x1.04025ap-2f, 0x1.6965f8p-27f, -0x1.0a324ep-2f, -0x1.39c872p-29f,
     -0x1.1058cp-2f, 0x1.946d4ap-28f, -0x1.1675cap-2f, -0x1.7574c2p-27f,
     -0x1.1c898cp-2f, -0x1.6999fap-30f, -0x1.22942p-2f, 0x1.0c21a6p-28f,
     -0x1.2895a2p-2f, 0x1.842f2cp-27f, -0x1.2e8e2cp-2f, 0x1.47b8b4p-28f,
     -0x1.347ddap-2f, 0x1.59e0aap-28f, -0x1.3a64c6p-2f, 0x1.52d742p-27f,
     -0x1.404308p-2f, -0x1.a1a9f8p-28f, -0x1.4618bcp-2f, -0x1.0e2f62p-29f,
     -0x1.4be5fap-2f, 0x1.5110ecp-27f, -0x1.51aad8p-2f, -0x1.cb7e0cp-28f,
     -0x1.576772p-2f, 0x1.1754b2p-27f, -0x1.5d1bdcp-2f, 0x1.4fec6cp-31f,
     -0x1.62c83p-2f, 0x1.a8c70ep-27f, 0x1.5d5bdep-2f, -0x1.4d41ap-31f, 0x1.57bf76p-2f,
     -0x1.86e5cp-27f, 0x1.522aep-2f, 0x1.ce28f6p-28f, 0x1.4c9e0ap-2f,
     -0x1.e8d3c4p-30f, 0x1.4718dcp-2f, 0x1.38e20ep-29f, 0x1.419b42p-2f,
     0x1.eaf464p-29f, 0x1.3c2528p-2f, -0x1.1999dp-27f, 0x1.36b678p-2f,
     -0x1.283ddep-27f, 0x1.314f1ep-2f, 0x1.d35ce4p-30f, 0x1.2bef08p-2f,
     -0x1.91b656p-29f, 0x1.269622p-2f, -0x1.d9648ep-27f, 0x1.214456p-2f,
     0x1.a1d71ap-27f, 0x1.1bf996p-2f, 0x1.ad35cap-29f, 0x1.16b5ccp-2f,
     0x1.759f6ep-27f, 0x1.1178e8p-2f, 0x1.13f23ep-29f, 0x1.0c42d6p-2f,
     0x1.d858b8p-28f, 0x1.071386p-2f, 0x1.35618ap-32f, 0x1.01eae6p-2f,
     -0x1.3b272ep-27f, 0x1.f991c6p-3f, 0x1.96767p-28f, 0x1.ef5adep-3f,
     0x1.373ffap-29f, 0x1.e530fp-3f, -0x1.8efedep-35f, 0x1.db13dcp-3f,
     -0x1.e56ed8p-28f, 0x1.d1038p-3f, -0x1.b3543p-28f, 0x1.c6ffbcp-3f,
     0x1.bc03dcp-29f, 0x1.bd0874p-3f, -0x1.f109d4p-29f, 0x1.b31d86p-3f,
     -0x1.148638p-28f, 0x1.a93ed4p-3f, -0x1.ba930ep-30f, 0x1.9f6c4p-3f,
     0x1.c2259ap-29f, 0x1.95a5aep-3f, -0x1.847f4p-30f, 0x1.8beafep-3f,
     0x1.671fd2p-28f, 0x1.823c16p-3f, 0x1.5468fp-29f, 0x1.7898d8p-3f, 0x1.51131cp-29f,
     0x1.6f0128p-3f, 0x1.6ead58p-28f, 0x1.6574ecp-3f, -0x1.73ecc6p-31f,
     0x1.5bf406p-3f, 0x1.6a87b6p-28f, 0x1.527e5ep-3f, 0x1.286d64p-29f, 0x1.4913d8p-3f,
     0x1.99dabp-30f, 0x1.3fb45ap-3f, 0x1.664a32p-29f, 0x1.365fccp-3f,
     -0x1.fd4dfep-28f, 0x1.2d161p-3f, 0x1.90d028p-28f, 0x1.23d712p-3f, 0x1.49384p-28f,
     0x1.1aa2b8p-3f, -0x1.dc08d6p-31f, 0x1.1178e8p-3f, 0x1.13f23ep-30f,
     0x1.08598cp-3f, -0x1.4c38cp-28f, 0x1.fe8914p-4f, -0x1.890aa6p-30f,
     0x1.ec7398p-4f, 0x1.85089p-31f, 0x1.da7276p-4f, 0x1.c22352p-31f, 0x1.c8858p-4f,
     0x1.bc4b24p-32f, 0x1.b6ac88p-4f, 0x1.b5ab64p-29f, 0x1.a4e764p-4f, 0x1.63787p-33f,
     0x1.9335e6p-4f, -0x1.535b3cp-31f, 0x1.8197e2p-4f, 0x1.e81c7ep-29f, 0x1.700d3p-4f,
     0x1.5d581cp-29f, 0x1.5e95a4p-4f, 0x1.b2f23ap-29f, 0x1.4d3116p-4f,
     -0x1.6fc0aap-31f, 0x1.3bdf5ap-4f, 0x1.f47b9ap-30f, 0x1.2aa04ap-4f,
     0x1.11c5eap-30f, 0x1.1973bep-4f, -0x1.d73554p-29f, 0x1.08598cp-4f,
     -0x1.4c38cp-29f, 0x1.eea31cp-5f, 0x1.ae1eecp-39f, 0x1.ccb73cp-5f,
     0x1.bbb65ap-30f, 0x1.aaef2ep-5f, -0x1.e09dep-30f, 0x1.894aa2p-5f,
     -0x1.6c0998p-30f, 0x1.67c95p-5f, -0x1.a56894p-30f, 0x1.466aeep-5f,
     -0x1.7a4382p-30f, 0x1.252f32p-5f, 0x1.f1a308p-30f, 0x1.0415d8p-5f,
     0x1.3ce888p-30f, 0x1.c63d2ep-6f, 0x1.82955ep-31f, 0x1.849252p-6f,
     0x1.191958p-31f, 0x1.432a92p-6f, 0x1.66033p-32f, 0x1.020566p-6f,
     -0x1.db29eep-32f, 0x1.82448ap-7f, 0x1.c45156p-34f, 0x1.010158p-7f,
     -0x1.4ee432p-32f, 0x1.008056p-8f, -0x1.a9dd32p-34f
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

float log_float_x86(float);
float log_float_x86(float x){
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
    float tmp19;
    float carg1;
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
    float tmp35;
    float carg2;
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
    float tmp53;
    float carg3;
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
    float tmp71;
    float carg4;
    float tmp72;
    float tmp73;
    float tmp74;
    float carg5;
    float tmp75;
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
    float log1pu_poly_hi;
    int tmp88;
    int32_t tmp89;
    int32_t tau;
    uint32_t exponent_srl_cast;
    int32_t tmp90;
    int32_t tmp91;
    int32_t tmp_eptau;
    int32_t tmp92;
    float fp_exponent;
    float tmp93;
    float carg6;
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
    float tmp104;
    float log1pu_poly_lo;
    float tmp105;
    float tmp106;
    float tmp107;
    float tmp108;
    float tmp109;
    float tmp110;
    float tmp111;
    float tmp112;
    float tmp113;
    float tmp114;
    float tmp115;
    uint32_t table_index_lo;
    float tbl_lo;
    float tmp116;
    float tmp117;
    float tmp118;
    float tmp119;
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
    tmp18 = u * u;
    tmp19 = u * 0x1.999bf8p-3f;
    carg1 =  - tmp19;
    tmp20 = fmaf(u, 0x1.999bf8p-3f, carg1);
    tmp21 = u * 0x1.54754p-30f;
    tmp22 = tmp20 + tmp21;
    tmp23 = tmp19 + tmp22;
    tmp24 = -0x1.00011cp-2f + tmp23;
    tmp25 = tmp24 - tmp23;
    tmp26 = -0x1.00011cp-2f - tmp25;
    tmp27 = tmp24 - tmp25;
    tmp28 = tmp23 - tmp27;
    tmp29 = tmp26 + tmp28;
    tmp30 = tmp23 - tmp19;
    tmp31 = tmp22 - tmp30;
    tmp32 = -0x1.6072cp-28f + tmp31;
    tmp33 = tmp29 + tmp32;
    tmp34 = tmp24 + tmp33;
    tmp35 = u * tmp34;
    carg2 =  - tmp35;
    tmp36 = fmaf(u, tmp34, carg2);
    tmp37 = tmp34 - tmp24;
    tmp38 = tmp33 - tmp37;
    tmp39 = u * tmp38;
    tmp40 = tmp36 + tmp39;
    tmp41 = tmp35 + tmp40;
    tmp42 = 0x1.555556p-2f + tmp41;
    tmp43 = tmp42 - tmp41;
    tmp44 = 0x1.555556p-2f - tmp43;
    tmp45 = tmp42 - tmp43;
    tmp46 = tmp41 - tmp45;
    tmp47 = tmp44 + tmp46;
    tmp48 = tmp41 - tmp35;
    tmp49 = tmp40 - tmp48;
    tmp50 = -0x1.56882ep-27f + tmp49;
    tmp51 = tmp47 + tmp50;
    tmp52 = tmp42 + tmp51;
    tmp53 = u * tmp52;
    carg3 =  - tmp53;
    tmp54 = fmaf(u, tmp52, carg3);
    tmp55 = tmp52 - tmp42;
    tmp56 = tmp51 - tmp55;
    tmp57 = u * tmp56;
    tmp58 = tmp54 + tmp57;
    tmp59 = tmp53 + tmp58;
    tmp60 = -0x1p-1f + tmp59;
    tmp61 = tmp60 - tmp59;
    tmp62 = -0x1p-1f - tmp61;
    tmp63 = tmp60 - tmp61;
    tmp64 = tmp59 - tmp63;
    tmp65 = tmp62 + tmp64;
    tmp66 = tmp59 - tmp53;
    tmp67 = tmp58 - tmp66;
    tmp68 = 0x1.a4f4p-36f + tmp67;
    tmp69 = tmp65 + tmp68;
    tmp70 = tmp60 + tmp69;
    tmp71 = tmp18 * tmp70;
    carg4 =  - tmp18;
    tmp72 = fmaf(u, u, carg4);
    tmp73 = tmp70 - tmp60;
    tmp74 = tmp69 - tmp73;
    carg5 =  - tmp71;
    tmp75 = fmaf(tmp18, tmp70, carg5);
    tmp76 = fmaf(tmp18, tmp74, tmp75);
    tmp77 = fmaf(tmp72, tmp70, tmp76);
    tmp78 = tmp71 + tmp77;
    tmp79 = u + tmp78;
    tmp80 = tmp78 - tmp71;
    tmp81 = tmp77 - tmp80;
    tmp82 = tmp79 - tmp78;
    tmp83 = u - tmp82;
    tmp84 = tmp79 - tmp82;
    tmp85 = tmp78 - tmp84;
    tmp86 = tmp83 + tmp85;
    tmp87 = tmp86 + tmp81;
    log1pu_poly_hi = tmp79 + tmp87;
    tmp88 = ( (int32_t) table_index) > INT32_C(53);
    tmp89 = tmp88 ? INT32_C(-1) : INT32_C(0);
    tau = tmp89 + INT32_C(1);
    exponent_srl_cast = tmp6;
    tmp90 = exponent_srl_cast >> INT32_C(23);
    tmp91 = tmp90 + INT32_C(-127);
    tmp_eptau = tmp91 + tau;
    tmp92 = tmp_eptau - alpha;
    fp_exponent = tmp92;
    tmp93 = fp_exponent * 0x1.62e43p-1f;
    carg6 =  - tmp93;
    tmp94 = fmaf(fp_exponent, 0x1.62e43p-1f, carg6);
    tmp95 = fp_exponent * -0x1.05c61p-29f;
    tmp96 = tmp94 + tmp95;
    tmp97 = tmp93 + tmp96;
    tmp98 = tmp97 + log1pu_poly_hi;
    tmp99 = tmp98 - log1pu_poly_hi;
    tmp100 = tmp97 - tmp99;
    tmp101 = tmp98 - tmp99;
    tmp102 = log1pu_poly_hi - tmp101;
    tmp103 = tmp100 + tmp102;
    tmp104 = log1pu_poly_hi - tmp79;
    log1pu_poly_lo = tmp87 - tmp104;
    tmp105 = tmp97 - tmp93;
    tmp106 = tmp96 - tmp105;
    tmp107 = tmp106 + log1pu_poly_lo;
    tmp108 = tmp103 + tmp107;
    tmp109 = tmp98 + tmp108;
    tmp110 = tmp109 + tbl_hi;
    tmp111 = tmp110 - tbl_hi;
    tmp112 = tmp109 - tmp111;
    tmp113 = tmp110 - tmp111;
    tmp114 = tbl_hi - tmp113;
    tmp115 = tmp112 + tmp114;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp116 = tmp109 - tmp98;
    tmp117 = tmp108 - tmp116;
    tmp118 = tmp117 + tbl_lo;
    tmp119 = tmp115 + tmp118;
    logx_hi = tmp110 + tmp119;
    return logx_hi;
}
