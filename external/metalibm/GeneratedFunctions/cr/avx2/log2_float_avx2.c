/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 2 --language c \
 *     --accuracy cr --precision float --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/log2_float_avx2.c --fname log2_float_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <ml_support_lib.h>
#include <emmintrin.h>


static const __m128 log2_float_avx2_fp_one = {1.0f}/*sse*/;
static const __m128i log2_float_avx2_cst = {INT32_C(1)}/*sse*/;
static const __m128i log2_float_avx2_subnormal_mask = {INT32_C(8388607)}/*sse*/;
static const __m128i log2_float_avx2_cst1 = {INT32_C(-1)}/*sse*/;
static const __m128i log2_float_avx2_cst2 = {INT32_C(0)}/*sse*/;
static const __m128i log2_float_avx2_cst3 = {INT32_C(-127)}/*sse*/;
static const __m128i log2_float_avx2_field_size = {INT32_C(23)}/*sse*/;
static const __m128i log2_float_avx2_cst4 = {INT32_C(32768)}/*sse*/;
static const __m128 log2_float_avx2_c_1hi = {0x1.715476p0f}/*sse*/;
static const __m128 log2_float_avx2_c_2hi = {-0x1.715476p-1f}/*sse*/;
static const __m128 log2_float_avx2_c_3hi = {0x1.ec709ep-2f}/*sse*/;
static const __m128 log2_float_avx2_c_4hi = {-0x1.71561p-2f}/*sse*/;
static const __m128 log2_float_avx2_c_5hi = {0x1.27791ep-2f}/*sse*/;
static const __m128 log2_float_avx2_c_5lo = {-0x1.62e9cp-29f}/*sse*/;
static const __m128 log2_float_avx2_c_4lo = {-0x1.6a353cp-27f}/*sse*/;
static const __m128 log2_float_avx2_c_3lo = {-0x1.f30a38p-29f}/*sse*/;
static const __m128 log2_float_avx2_c_2lo = {-0x1.49b0cp-27f}/*sse*/;
static const __m128 log2_float_avx2_c_1lo = {0x1.4ae0cp-26f}/*sse*/;
static const __m128i log2_float_avx2_cst5 = {INT32_C(-127)}/*sse*/;
static const __m128i log2_float_avx2_field_size1 = {INT32_C(23)}/*sse*/;
static const __m128i log2_float_avx2_cst6 = {INT32_C(1)}/*sse*/;
static const __m128i log2_float_avx2_cst7 = {INT32_C(53)}/*sse*/;
static const __m128i log2_float_avx2_cst8 = {INT32_C(-1)}/*sse*/;
static const __m128i log2_float_avx2_cst9 = {INT32_C(0)}/*sse*/;
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

float log2_float_avx2(float);
float log2_float_avx2(float x){
    int32_t vx_as_int;
    __m128i tmp;
    int32_t tmp1;
    int32_t tmp2;
    int32_t tmp3;
    int tmp4;
    int32_t tmp5;
    int32_t tmp6;
    int32_t is_subnormal;
    int32_t tmp7;
    float tmp8;
    uint32_t fp_one_as_uint;
    uint32_t vx_as_uint;
    uint32_t Zi;
    float tmp9;
    __m128 tmp10;
    __m128 Zf;
    float tmp11;
    int32_t tmp12;
    uint32_t _srl_cast;
    int32_t tmp13;
    __m128i tmp14;
    __m128i tmp15;
    int32_t tmp16;
    int32_t n_value;
    int32_t alpha;
    __m128i tmp17;
    __m128i tmp18;
    int32_t tmp19;
    float normal_vx;
    float tmp20;
    __m128 tmp21;
    __m128 rcp_m;
    float tmp22;
    int32_t tmp23;
    __m128i tmp24;
    __m128i tmp25;
    int32_t tmp26;
    uint32_t id_tmp;
    uint32_t ri_fast_rndn;
    float tmp27;
    __m128 tmp28;
    __m128 u;
    __m128 tmp29;
    __m128 tmp30;
    __m128 tmp31;
    __m128 tmp32;
    __m128 tmp33;
    __m128 tmp34;
    __m128 tmp35;
    __m128 tmp36;
    __m128 tmp37;
    __m128 tmp38;
    __m128 tmp39;
    __m128 tmp40;
    __m128 tmp41;
    __m128 tmp42;
    __m128 tmp43;
    __m128 tmp44;
    __m128 tmp45;
    __m128 tmp46;
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
    __m128 log1pu_poly_hi;
    int32_t tmp105;
    uint32_t exponent_srl_cast;
    int32_t tmp106;
    __m128i tmp107;
    __m128i tmp108;
    uint32_t ri_bits;
    uint32_t table_index;
    int32_t tmp109;
    int tmp110;
    int32_t tmp111;
    int32_t tmp112;
    int32_t tmp113;
    __m128i tmp114;
    __m128i tau;
    __m128i tmp_eptau;
    int32_t tmp115;
    int32_t tmp116;
    float fp_exponent;
    __m128 tmp117;
    __m128 tmp118;
    __m128 tmp119;
    __m128 tmp120;
    __m128 tmp121;
    __m128 tmp122;
    __m128 tmp123;
    __m128 tmp124;
    __m128 log1pu_poly_lo;
    __m128 tmp125;
    __m128 tmp126;
    uint32_t tmp127;
    uint32_t table_index_hi;
    float tbl_hi;
    __m128 tmp128;
    __m128 tmp129;
    __m128 tmp130;
    __m128 tmp131;
    __m128 tmp132;
    __m128 tmp133;
    __m128 tmp134;
    __m128 tmp135;
    __m128 tmp136;
    uint32_t table_index_lo;
    float tbl_lo;
    __m128 tmp137;
    __m128 tmp138;
    __m128 tmp139;
    __m128 logx_hi;
    float tmp140;
    
    vx_as_int = float_to_32b_encoding(x);
    tmp = _mm_set1_epi32(vx_as_int);
    tmp1 = _mm_cvtsi128_si32(log2_float_avx2_cst);
    tmp2 = vx_as_int - tmp1;
    tmp3 = _mm_cvtsi128_si32(log2_float_avx2_subnormal_mask);
    tmp4 = tmp2 < tmp3;
    tmp5 = _mm_cvtsi128_si32(log2_float_avx2_cst1);
    tmp6 = _mm_cvtsi128_si32(log2_float_avx2_cst2);
    is_subnormal = tmp4 ? tmp5 : tmp6;
    tmp7 = _mm_cvtsi128_si32(log2_float_avx2_field_size);
    tmp8 = _mm_cvtss_f32(log2_float_avx2_fp_one);
    fp_one_as_uint = float_to_32b_encoding(tmp8);
    vx_as_uint = float_to_32b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp9 = float_from_32b_encoding(Zi);
    tmp10 = _mm_set_ss(tmp9);
    Zf = _mm_sub_ss(tmp10, log2_float_avx2_fp_one);
    tmp11 = _mm_cvtss_f32(Zf);
    tmp12 = float_to_32b_encoding(tmp11);
    _srl_cast = tmp12;
    tmp13 = _srl_cast >> tmp7;
    tmp14 = _mm_set1_epi32(tmp13);
    tmp15 = _mm_add_epi32(tmp14, log2_float_avx2_cst3);
    tmp16 = _mm_cvtsi128_si32(tmp15);
    n_value = tmp16 & is_subnormal;
    alpha =  - n_value;
    tmp17 = _mm_set1_epi32(alpha);
    tmp18 = tmp << tmp17;
    tmp19 = _mm_cvtsi128_si32(tmp18);
    normal_vx = float_from_32b_encoding(tmp19);
    tmp20 = ml_mantissa_extraction_fp32(normal_vx);
    tmp21 = _mm_set_ss(tmp20);
    rcp_m = _mm_rcp_ss(tmp21);
    tmp22 = _mm_cvtss_f32(rcp_m);
    tmp23 = float_to_32b_encoding(tmp22);
    tmp24 = _mm_set1_epi32(tmp23);
    tmp25 = _mm_add_epi32(tmp24, log2_float_avx2_cst4);
    tmp26 = _mm_cvtsi128_si32(tmp25);
    id_tmp = tmp26;
    ri_fast_rndn = id_tmp & UINT32_C(-65536);
    tmp27 = float_from_32b_encoding(ri_fast_rndn);
    tmp28 = _mm_set_ss(tmp27);
    u = _mm_fmsub_ss(tmp21, tmp28, log2_float_avx2_fp_one);
    tmp29 = _mm_mul_ss(u, log2_float_avx2_c_5hi);
    tmp30 = _mm_fmsub_ss(u, log2_float_avx2_c_5hi, tmp29);
    tmp31 = _mm_mul_ss(u, log2_float_avx2_c_5lo);
    tmp32 = _mm_add_ss(tmp30, tmp31);
    tmp33 = _mm_add_ss(tmp29, tmp32);
    tmp34 = _mm_add_ss(log2_float_avx2_c_4hi, tmp33);
    tmp35 = _mm_sub_ss(tmp34, tmp33);
    tmp36 = _mm_sub_ss(log2_float_avx2_c_4hi, tmp35);
    tmp37 = _mm_sub_ss(tmp34, tmp35);
    tmp38 = _mm_sub_ss(tmp33, tmp37);
    tmp39 = _mm_add_ss(tmp36, tmp38);
    tmp40 = _mm_sub_ss(tmp33, tmp29);
    tmp41 = _mm_sub_ss(tmp32, tmp40);
    tmp42 = _mm_add_ss(log2_float_avx2_c_4lo, tmp41);
    tmp43 = _mm_add_ss(tmp39, tmp42);
    tmp44 = _mm_add_ss(tmp34, tmp43);
    tmp45 = _mm_mul_ss(u, tmp44);
    tmp46 = _mm_fmsub_ss(u, tmp44, tmp45);
    tmp47 = _mm_sub_ss(tmp44, tmp34);
    tmp48 = _mm_sub_ss(tmp43, tmp47);
    tmp49 = _mm_mul_ss(u, tmp48);
    tmp50 = _mm_add_ss(tmp46, tmp49);
    tmp51 = _mm_add_ss(tmp45, tmp50);
    tmp52 = _mm_add_ss(log2_float_avx2_c_3hi, tmp51);
    tmp53 = _mm_sub_ss(tmp52, tmp51);
    tmp54 = _mm_sub_ss(log2_float_avx2_c_3hi, tmp53);
    tmp55 = _mm_sub_ss(tmp52, tmp53);
    tmp56 = _mm_sub_ss(tmp51, tmp55);
    tmp57 = _mm_add_ss(tmp54, tmp56);
    tmp58 = _mm_sub_ss(tmp51, tmp45);
    tmp59 = _mm_sub_ss(tmp50, tmp58);
    tmp60 = _mm_add_ss(log2_float_avx2_c_3lo, tmp59);
    tmp61 = _mm_add_ss(tmp57, tmp60);
    tmp62 = _mm_add_ss(tmp52, tmp61);
    tmp63 = _mm_mul_ss(u, tmp62);
    tmp64 = _mm_fmsub_ss(u, tmp62, tmp63);
    tmp65 = _mm_sub_ss(tmp62, tmp52);
    tmp66 = _mm_sub_ss(tmp61, tmp65);
    tmp67 = _mm_mul_ss(u, tmp66);
    tmp68 = _mm_add_ss(tmp64, tmp67);
    tmp69 = _mm_add_ss(tmp63, tmp68);
    tmp70 = _mm_add_ss(log2_float_avx2_c_2hi, tmp69);
    tmp71 = _mm_sub_ss(tmp70, tmp69);
    tmp72 = _mm_sub_ss(log2_float_avx2_c_2hi, tmp71);
    tmp73 = _mm_sub_ss(tmp70, tmp71);
    tmp74 = _mm_sub_ss(tmp69, tmp73);
    tmp75 = _mm_add_ss(tmp72, tmp74);
    tmp76 = _mm_sub_ss(tmp69, tmp63);
    tmp77 = _mm_sub_ss(tmp68, tmp76);
    tmp78 = _mm_add_ss(log2_float_avx2_c_2lo, tmp77);
    tmp79 = _mm_add_ss(tmp75, tmp78);
    tmp80 = _mm_add_ss(tmp70, tmp79);
    tmp81 = _mm_mul_ss(u, tmp80);
    tmp82 = _mm_fmsub_ss(u, tmp80, tmp81);
    tmp83 = _mm_sub_ss(tmp80, tmp70);
    tmp84 = _mm_sub_ss(tmp79, tmp83);
    tmp85 = _mm_mul_ss(u, tmp84);
    tmp86 = _mm_add_ss(tmp82, tmp85);
    tmp87 = _mm_add_ss(tmp81, tmp86);
    tmp88 = _mm_add_ss(log2_float_avx2_c_1hi, tmp87);
    tmp89 = _mm_sub_ss(tmp88, tmp87);
    tmp90 = _mm_sub_ss(log2_float_avx2_c_1hi, tmp89);
    tmp91 = _mm_sub_ss(tmp88, tmp89);
    tmp92 = _mm_sub_ss(tmp87, tmp91);
    tmp93 = _mm_add_ss(tmp90, tmp92);
    tmp94 = _mm_sub_ss(tmp87, tmp81);
    tmp95 = _mm_sub_ss(tmp86, tmp94);
    tmp96 = _mm_add_ss(log2_float_avx2_c_1lo, tmp95);
    tmp97 = _mm_add_ss(tmp93, tmp96);
    tmp98 = _mm_add_ss(tmp88, tmp97);
    tmp99 = _mm_mul_ss(u, tmp98);
    tmp100 = _mm_fmsub_ss(u, tmp98, tmp99);
    tmp101 = _mm_sub_ss(tmp98, tmp88);
    tmp102 = _mm_sub_ss(tmp97, tmp101);
    tmp103 = _mm_mul_ss(u, tmp102);
    tmp104 = _mm_add_ss(tmp100, tmp103);
    log1pu_poly_hi = _mm_add_ss(tmp99, tmp104);
    tmp105 = _mm_cvtsi128_si32(log2_float_avx2_field_size1);
    exponent_srl_cast = tmp19;
    tmp106 = exponent_srl_cast >> tmp105;
    tmp107 = _mm_set1_epi32(tmp106);
    tmp108 = _mm_add_epi32(tmp107, log2_float_avx2_cst5);
    ri_bits = ri_fast_rndn >> UINT32_C(16);
    table_index = ri_bits & UINT32_C(255);
    tmp109 = _mm_cvtsi128_si32(log2_float_avx2_cst7);
    tmp110 = ( (int32_t) table_index) > tmp109;
    tmp111 = _mm_cvtsi128_si32(log2_float_avx2_cst8);
    tmp112 = _mm_cvtsi128_si32(log2_float_avx2_cst9);
    tmp113 = tmp110 ? tmp111 : tmp112;
    tmp114 = _mm_set1_epi32(tmp113);
    tau = _mm_add_epi32(tmp114, log2_float_avx2_cst6);
    tmp_eptau = _mm_add_epi32(tmp108, tau);
    tmp115 = _mm_cvtsi128_si32(tmp_eptau);
    tmp116 = tmp115 - alpha;
    fp_exponent = tmp116;
    tmp117 = _mm_set_ss(fp_exponent);
    tmp118 = _mm_add_ss(tmp117, log1pu_poly_hi);
    tmp119 = _mm_sub_ss(tmp118, log1pu_poly_hi);
    tmp120 = _mm_sub_ss(tmp117, tmp119);
    tmp121 = _mm_sub_ss(tmp118, tmp119);
    tmp122 = _mm_sub_ss(log1pu_poly_hi, tmp121);
    tmp123 = _mm_add_ss(tmp120, tmp122);
    tmp124 = _mm_sub_ss(log1pu_poly_hi, tmp99);
    log1pu_poly_lo = _mm_sub_ss(tmp104, tmp124);
    tmp125 = _mm_add_ss(tmp123, log1pu_poly_lo);
    tmp126 = _mm_add_ss(tmp118, tmp125);
    tmp127 = table_index & UINT32_C(127);
    table_index_hi = tmp127 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp128 = _mm_set_ss(tbl_hi);
    tmp129 = _mm_add_ss(tmp126, tmp128);
    tmp130 = _mm_sub_ss(tmp129, tmp128);
    tmp131 = _mm_sub_ss(tmp126, tmp130);
    tmp132 = _mm_sub_ss(tmp129, tmp130);
    tmp133 = _mm_sub_ss(tmp128, tmp132);
    tmp134 = _mm_add_ss(tmp131, tmp133);
    tmp135 = _mm_sub_ss(tmp126, tmp118);
    tmp136 = _mm_sub_ss(tmp125, tmp135);
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp137 = _mm_set_ss(tbl_lo);
    tmp138 = _mm_add_ss(tmp136, tmp137);
    tmp139 = _mm_add_ss(tmp134, tmp138);
    logx_hi = _mm_add_ss(tmp129, tmp139);
    tmp140 = _mm_cvtss_f32(logx_hi);
    return tmp140;
}
