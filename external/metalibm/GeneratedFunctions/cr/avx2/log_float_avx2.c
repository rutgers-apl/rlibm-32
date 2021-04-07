/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix e --language c \
 *     --accuracy cr --precision float --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/log_float_avx2.c --fname log_float_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <xmmintrin.h>
#include <ml_support_lib.h>
#include <emmintrin.h>
#include <immintrin.h>


static const __m128 log_float_avx2_log2_hi = {0x1.62e43p-1f}/*sse*/;
static const __m128i log_float_avx2_cst = {INT32_C(1)}/*sse*/;
static const __m128i log_float_avx2_subnormal_mask = {INT32_C(8388607)}/*sse*/;
static const __m128i log_float_avx2_cst1 = {INT32_C(-1)}/*sse*/;
static const __m128i log_float_avx2_cst2 = {INT32_C(0)}/*sse*/;
static const __m128i log_float_avx2_cst3 = {INT32_C(-127)}/*sse*/;
static const __m128i log_float_avx2_field_size = {INT32_C(23)}/*sse*/;
static const __m128 log_float_avx2_fp_one = {1.0f}/*sse*/;
static const __m128i log_float_avx2_cst4 = {INT32_C(-127)}/*sse*/;
static const __m128i log_float_avx2_field_size1 = {INT32_C(23)}/*sse*/;
static const __m128i log_float_avx2_cst5 = {INT32_C(1)}/*sse*/;
static const __m128i log_float_avx2_cst6 = {INT32_C(32768)}/*sse*/;
static const __m128i log_float_avx2_cst7 = {INT32_C(53)}/*sse*/;
static const __m128i log_float_avx2_cst8 = {INT32_C(-1)}/*sse*/;
static const __m128i log_float_avx2_cst9 = {INT32_C(0)}/*sse*/;
static const __m128 log_float_avx2_log2_lo = {-0x1.05c61p-29f}/*sse*/;
static const __m128 log_float_avx2_c_2hi = {-0x1p-1f}/*sse*/;
static const __m128 log_float_avx2_c_3hi = {0x1.555556p-2f}/*sse*/;
static const __m128 log_float_avx2_c_4hi = {-0x1.00011cp-2f}/*sse*/;
static const __m128 log_float_avx2_c_5hi = {0x1.999bf8p-3f}/*sse*/;
static const __m128 log_float_avx2_c_5lo = {0x1.54754p-30f}/*sse*/;
static const __m128 log_float_avx2_c_4lo = {-0x1.6072cp-28f}/*sse*/;
static const __m128 log_float_avx2_c_3lo = {-0x1.56882ep-27f}/*sse*/;
static const __m128 log_float_avx2_c_2lo = {0x1.a4f4p-36f}/*sse*/;
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

float log_float_avx2(float);
float log_float_avx2(float x){
    int32_t vx_as_int;
    int32_t tmp;
    int32_t tmp1;
    int32_t tmp2;
    int tmp3;
    int32_t tmp4;
    int32_t tmp5;
    int32_t is_subnormal;
    int32_t tmp6;
    float tmp7;
    uint32_t fp_one_as_uint;
    uint32_t vx_as_uint;
    uint32_t Zi;
    float tmp8;
    __m128 tmp9;
    __m128 Zf;
    float tmp10;
    int32_t tmp11;
    uint32_t _srl_cast;
    int32_t tmp12;
    __m128i tmp13;
    __m128i tmp14;
    int32_t tmp15;
    int32_t n_value;
    int32_t alpha;
    int32_t tmp16;
    __m128i tmp17;
    __m128i tmp18;
    __m128i tmp19;
    int32_t tmp20;
    uint32_t exponent_srl_cast;
    int32_t tmp21;
    __m128i tmp22;
    __m128i tmp23;
    float normal_vx;
    float tmp24;
    __m128 tmp25;
    __m128 rcp_m;
    float tmp26;
    int32_t tmp27;
    __m128i tmp28;
    __m128i tmp29;
    int32_t tmp30;
    uint32_t id_tmp;
    uint32_t ri_fast_rndn;
    uint32_t ri_bits;
    uint32_t table_index;
    int32_t tmp31;
    int tmp32;
    int32_t tmp33;
    int32_t tmp34;
    int32_t tmp35;
    __m128i tmp36;
    __m128i tau;
    __m128i tmp_eptau;
    int32_t tmp37;
    int32_t tmp38;
    float fp_exponent;
    __m128 tmp39;
    __m128 tmp40;
    __m128 tmp41;
    __m128 tmp42;
    __m128 tmp43;
    __m128 tmp44;
    float tmp45;
    __m128 tmp46;
    __m128 u;
    __m128 tmp47;
    __m128 tmp48;
    __m128 tmp49;
    __m128 tmp50;
    __m128 tmp51;
    __m128 tmp52;
    __m128 tmp53;
    __m128 tmp54;
    __m128 tmp55;
    __m128 tmp56;
    __m128 tmp57;
    __m128 tmp58;
    __m128 tmp59;
    __m128 tmp60;
    __m128 tmp61;
    __m128 tmp62;
    __m128 tmp63;
    __m128 tmp64;
    __m128 tmp65;
    __m128 tmp66;
    __m128 tmp67;
    __m128 tmp68;
    __m128 tmp69;
    __m128 tmp70;
    __m128 tmp71;
    __m128 tmp72;
    __m128 tmp73;
    __m128 tmp74;
    __m128 tmp75;
    __m128 tmp76;
    __m128 tmp77;
    __m128 tmp78;
    __m128 tmp79;
    __m128 tmp80;
    __m128 tmp81;
    __m128 tmp82;
    __m128 tmp83;
    __m128 tmp84;
    __m128 tmp85;
    __m128 tmp86;
    __m128 tmp87;
    __m128 tmp88;
    __m128 tmp89;
    __m128 tmp90;
    __m128 tmp91;
    __m128 tmp92;
    __m128 tmp93;
    __m128 tmp94;
    __m128 tmp95;
    __m128 tmp96;
    __m128 tmp97;
    __m128 tmp98;
    __m128 tmp99;
    __m128 tmp100;
    __m128 tmp101;
    __m128 tmp102;
    __m128 tmp103;
    __m128 tmp104;
    __m128 tmp105;
    __m128 tmp106;
    __m128 tmp107;
    __m128 tmp108;
    __m128 tmp109;
    __m128 tmp110;
    __m128 tmp111;
    __m128 tmp112;
    __m128 tmp113;
    __m128 tmp114;
    __m128 tmp115;
    __m128 tmp116;
    __m128 log1pu_poly_hi;
    __m128 tmp117;
    __m128 tmp118;
    __m128 tmp119;
    __m128 tmp120;
    __m128 tmp121;
    __m128 tmp122;
    __m128 tmp123;
    __m128 tmp124;
    __m128 tmp125;
    __m128 log1pu_poly_lo;
    __m128 tmp126;
    __m128 tmp127;
    __m128 tmp128;
    uint32_t tmp129;
    uint32_t table_index_hi;
    float tbl_hi;
    __m128 tmp130;
    __m128 tmp131;
    __m128 tmp132;
    __m128 tmp133;
    __m128 tmp134;
    __m128 tmp135;
    __m128 tmp136;
    __m128 tmp137;
    __m128 tmp138;
    uint32_t table_index_lo;
    float tbl_lo;
    __m128 tmp139;
    __m128 tmp140;
    __m128 tmp141;
    __m128 logx_hi;
    float tmp142;
    
    vx_as_int = float_to_32b_encoding(x);
    tmp = _mm_cvtsi128_si32(log_float_avx2_cst);
    tmp1 = vx_as_int - tmp;
    tmp2 = _mm_cvtsi128_si32(log_float_avx2_subnormal_mask);
    tmp3 = tmp1 < tmp2;
    tmp4 = _mm_cvtsi128_si32(log_float_avx2_cst1);
    tmp5 = _mm_cvtsi128_si32(log_float_avx2_cst2);
    is_subnormal = tmp3 ? tmp4 : tmp5;
    tmp6 = _mm_cvtsi128_si32(log_float_avx2_field_size);
    tmp7 = _mm_cvtss_f32(log_float_avx2_fp_one);
    fp_one_as_uint = float_to_32b_encoding(tmp7);
    vx_as_uint = float_to_32b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp8 = float_from_32b_encoding(Zi);
    tmp9 = _mm_set_ss(tmp8);
    Zf = _mm_sub_ss(tmp9, log_float_avx2_fp_one);
    tmp10 = _mm_cvtss_f32(Zf);
    tmp11 = float_to_32b_encoding(tmp10);
    _srl_cast = tmp11;
    tmp12 = _srl_cast >> tmp6;
    tmp13 = _mm_set1_epi32(tmp12);
    tmp14 = _mm_add_epi32(tmp13, log_float_avx2_cst3);
    tmp15 = _mm_cvtsi128_si32(tmp14);
    n_value = tmp15 & is_subnormal;
    alpha =  - n_value;
    tmp16 = _mm_cvtsi128_si32(log_float_avx2_field_size1);
    tmp17 = _mm_set1_epi32(vx_as_int);
    tmp18 = _mm_set1_epi32(alpha);
    tmp19 = tmp17 << tmp18;
    tmp20 = _mm_cvtsi128_si32(tmp19);
    exponent_srl_cast = tmp20;
    tmp21 = exponent_srl_cast >> tmp16;
    tmp22 = _mm_set1_epi32(tmp21);
    tmp23 = _mm_add_epi32(tmp22, log_float_avx2_cst4);
    normal_vx = float_from_32b_encoding(tmp20);
    tmp24 = ml_mantissa_extraction_fp32(normal_vx);
    tmp25 = _mm_set_ss(tmp24);
    rcp_m = _mm_rcp_ss(tmp25);
    tmp26 = _mm_cvtss_f32(rcp_m);
    tmp27 = float_to_32b_encoding(tmp26);
    tmp28 = _mm_set1_epi32(tmp27);
    tmp29 = _mm_add_epi32(tmp28, log_float_avx2_cst6);
    tmp30 = _mm_cvtsi128_si32(tmp29);
    id_tmp = tmp30;
    ri_fast_rndn = id_tmp & UINT32_C(-65536);
    ri_bits = ri_fast_rndn >> UINT32_C(16);
    table_index = ri_bits & UINT32_C(255);
    tmp31 = _mm_cvtsi128_si32(log_float_avx2_cst7);
    tmp32 = ( (int32_t) table_index) > tmp31;
    tmp33 = _mm_cvtsi128_si32(log_float_avx2_cst8);
    tmp34 = _mm_cvtsi128_si32(log_float_avx2_cst9);
    tmp35 = tmp32 ? tmp33 : tmp34;
    tmp36 = _mm_set1_epi32(tmp35);
    tau = _mm_add_epi32(tmp36, log_float_avx2_cst5);
    tmp_eptau = _mm_add_epi32(tmp23, tau);
    tmp37 = _mm_cvtsi128_si32(tmp_eptau);
    tmp38 = tmp37 - alpha;
    fp_exponent = tmp38;
    tmp39 = _mm_set_ss(fp_exponent);
    tmp40 = _mm_mul_ss(tmp39, log_float_avx2_log2_hi);
    tmp41 = _mm_fmsub_ss(tmp39, log_float_avx2_log2_hi, tmp40);
    tmp42 = _mm_mul_ss(tmp39, log_float_avx2_log2_lo);
    tmp43 = _mm_add_ss(tmp41, tmp42);
    tmp44 = _mm_add_ss(tmp40, tmp43);
    tmp45 = float_from_32b_encoding(ri_fast_rndn);
    tmp46 = _mm_set_ss(tmp45);
    u = _mm_fmsub_ss(tmp25, tmp46, log_float_avx2_fp_one);
    tmp47 = _mm_mul_ss(u, u);
    tmp48 = _mm_mul_ss(u, log_float_avx2_c_5hi);
    tmp49 = _mm_fmsub_ss(u, log_float_avx2_c_5hi, tmp48);
    tmp50 = _mm_mul_ss(u, log_float_avx2_c_5lo);
    tmp51 = _mm_add_ss(tmp49, tmp50);
    tmp52 = _mm_add_ss(tmp48, tmp51);
    tmp53 = _mm_add_ss(log_float_avx2_c_4hi, tmp52);
    tmp54 = _mm_sub_ss(tmp53, tmp52);
    tmp55 = _mm_sub_ss(log_float_avx2_c_4hi, tmp54);
    tmp56 = _mm_sub_ss(tmp53, tmp54);
    tmp57 = _mm_sub_ss(tmp52, tmp56);
    tmp58 = _mm_add_ss(tmp55, tmp57);
    tmp59 = _mm_sub_ss(tmp52, tmp48);
    tmp60 = _mm_sub_ss(tmp51, tmp59);
    tmp61 = _mm_add_ss(log_float_avx2_c_4lo, tmp60);
    tmp62 = _mm_add_ss(tmp58, tmp61);
    tmp63 = _mm_add_ss(tmp53, tmp62);
    tmp64 = _mm_mul_ss(u, tmp63);
    tmp65 = _mm_fmsub_ss(u, tmp63, tmp64);
    tmp66 = _mm_sub_ss(tmp63, tmp53);
    tmp67 = _mm_sub_ss(tmp62, tmp66);
    tmp68 = _mm_mul_ss(u, tmp67);
    tmp69 = _mm_add_ss(tmp65, tmp68);
    tmp70 = _mm_add_ss(tmp64, tmp69);
    tmp71 = _mm_add_ss(log_float_avx2_c_3hi, tmp70);
    tmp72 = _mm_sub_ss(tmp71, tmp70);
    tmp73 = _mm_sub_ss(log_float_avx2_c_3hi, tmp72);
    tmp74 = _mm_sub_ss(tmp71, tmp72);
    tmp75 = _mm_sub_ss(tmp70, tmp74);
    tmp76 = _mm_add_ss(tmp73, tmp75);
    tmp77 = _mm_sub_ss(tmp70, tmp64);
    tmp78 = _mm_sub_ss(tmp69, tmp77);
    tmp79 = _mm_add_ss(log_float_avx2_c_3lo, tmp78);
    tmp80 = _mm_add_ss(tmp76, tmp79);
    tmp81 = _mm_add_ss(tmp71, tmp80);
    tmp82 = _mm_mul_ss(u, tmp81);
    tmp83 = _mm_fmsub_ss(u, tmp81, tmp82);
    tmp84 = _mm_sub_ss(tmp81, tmp71);
    tmp85 = _mm_sub_ss(tmp80, tmp84);
    tmp86 = _mm_mul_ss(u, tmp85);
    tmp87 = _mm_add_ss(tmp83, tmp86);
    tmp88 = _mm_add_ss(tmp82, tmp87);
    tmp89 = _mm_add_ss(log_float_avx2_c_2hi, tmp88);
    tmp90 = _mm_sub_ss(tmp89, tmp88);
    tmp91 = _mm_sub_ss(log_float_avx2_c_2hi, tmp90);
    tmp92 = _mm_sub_ss(tmp89, tmp90);
    tmp93 = _mm_sub_ss(tmp88, tmp92);
    tmp94 = _mm_add_ss(tmp91, tmp93);
    tmp95 = _mm_sub_ss(tmp88, tmp82);
    tmp96 = _mm_sub_ss(tmp87, tmp95);
    tmp97 = _mm_add_ss(log_float_avx2_c_2lo, tmp96);
    tmp98 = _mm_add_ss(tmp94, tmp97);
    tmp99 = _mm_add_ss(tmp89, tmp98);
    tmp100 = _mm_mul_ss(tmp47, tmp99);
    tmp101 = _mm_fmsub_ss(u, u, tmp47);
    tmp102 = _mm_sub_ss(tmp99, tmp89);
    tmp103 = _mm_sub_ss(tmp98, tmp102);
    tmp104 = _mm_fmsub_ss(tmp47, tmp99, tmp100);
    tmp105 = _mm_fmadd_ss(tmp47, tmp103, tmp104);
    tmp106 = _mm_fmadd_ss(tmp101, tmp99, tmp105);
    tmp107 = _mm_add_ss(tmp100, tmp106);
    tmp108 = _mm_add_ss(u, tmp107);
    tmp109 = _mm_sub_ss(tmp108, tmp107);
    tmp110 = _mm_sub_ss(u, tmp109);
    tmp111 = _mm_sub_ss(tmp108, tmp109);
    tmp112 = _mm_sub_ss(tmp107, tmp111);
    tmp113 = _mm_add_ss(tmp110, tmp112);
    tmp114 = _mm_sub_ss(tmp107, tmp100);
    tmp115 = _mm_sub_ss(tmp106, tmp114);
    tmp116 = _mm_add_ss(tmp113, tmp115);
    log1pu_poly_hi = _mm_add_ss(tmp108, tmp116);
    tmp117 = _mm_add_ss(tmp44, log1pu_poly_hi);
    tmp118 = _mm_sub_ss(tmp117, log1pu_poly_hi);
    tmp119 = _mm_sub_ss(tmp44, tmp118);
    tmp120 = _mm_sub_ss(tmp117, tmp118);
    tmp121 = _mm_sub_ss(log1pu_poly_hi, tmp120);
    tmp122 = _mm_add_ss(tmp119, tmp121);
    tmp123 = _mm_sub_ss(tmp44, tmp40);
    tmp124 = _mm_sub_ss(tmp43, tmp123);
    tmp125 = _mm_sub_ss(log1pu_poly_hi, tmp108);
    log1pu_poly_lo = _mm_sub_ss(tmp116, tmp125);
    tmp126 = _mm_add_ss(tmp124, log1pu_poly_lo);
    tmp127 = _mm_add_ss(tmp122, tmp126);
    tmp128 = _mm_add_ss(tmp117, tmp127);
    tmp129 = table_index & UINT32_C(127);
    table_index_hi = tmp129 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp130 = _mm_set_ss(tbl_hi);
    tmp131 = _mm_add_ss(tmp128, tmp130);
    tmp132 = _mm_sub_ss(tmp131, tmp130);
    tmp133 = _mm_sub_ss(tmp128, tmp132);
    tmp134 = _mm_sub_ss(tmp131, tmp132);
    tmp135 = _mm_sub_ss(tmp130, tmp134);
    tmp136 = _mm_add_ss(tmp133, tmp135);
    tmp137 = _mm_sub_ss(tmp128, tmp117);
    tmp138 = _mm_sub_ss(tmp127, tmp137);
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp139 = _mm_set_ss(tbl_lo);
    tmp140 = _mm_add_ss(tmp138, tmp139);
    tmp141 = _mm_add_ss(tmp136, tmp140);
    logx_hi = _mm_add_ss(tmp131, tmp141);
    tmp142 = _mm_cvtss_f32(logx_hi);
    return tmp142;
}
