/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 10 --language c \
 *     --accuracy cr --precision float --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/log10_float_avx2.c --fname log10_float_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <xmmintrin.h>
#include <ml_support_lib.h>
#include <emmintrin.h>
#include <immintrin.h>


static const __m128 log10_float_avx2_log2_hi = {0x1.344136p-2f}/*sse*/;
static const __m128i log10_float_avx2_cst = {INT32_C(1)}/*sse*/;
static const __m128i log10_float_avx2_subnormal_mask = {INT32_C(8388607)}/*sse*/;
static const __m128i log10_float_avx2_cst1 = {INT32_C(-1)}/*sse*/;
static const __m128i log10_float_avx2_cst2 = {INT32_C(0)}/*sse*/;
static const __m128i log10_float_avx2_cst3 = {INT32_C(-127)}/*sse*/;
static const __m128i log10_float_avx2_field_size = {INT32_C(23)}/*sse*/;
static const __m128 log10_float_avx2_fp_one = {1.0f}/*sse*/;
static const __m128i log10_float_avx2_cst4 = {INT32_C(-127)}/*sse*/;
static const __m128i log10_float_avx2_field_size1 = {INT32_C(23)}/*sse*/;
static const __m128i log10_float_avx2_cst5 = {INT32_C(1)}/*sse*/;
static const __m128i log10_float_avx2_cst6 = {INT32_C(32768)}/*sse*/;
static const __m128i log10_float_avx2_cst7 = {INT32_C(53)}/*sse*/;
static const __m128i log10_float_avx2_cst8 = {INT32_C(-1)}/*sse*/;
static const __m128i log10_float_avx2_cst9 = {INT32_C(0)}/*sse*/;
static const __m128 log10_float_avx2_log2_lo = {-0x1.ec10cp-27f}/*sse*/;
static const __m128 log10_float_avx2_c_1hi = {0x1.bcb7b2p-2f}/*sse*/;
static const __m128 log10_float_avx2_c_2hi = {-0x1.bcb7b2p-3f}/*sse*/;
static const __m128 log10_float_avx2_c_3hi = {0x1.287b8p-3f}/*sse*/;
static const __m128 log10_float_avx2_c_4hi = {-0x1.bcb9fcp-4f}/*sse*/;
static const __m128 log10_float_avx2_c_4lo = {-0x1.e505acp-30f}/*sse*/;
static const __m128 log10_float_avx2_c_3lo = {0x1.3cf4f8p-29f}/*sse*/;
static const __m128 log10_float_avx2_c_2lo = {0x1.5c396p-28f}/*sse*/;
static const __m128 log10_float_avx2_c_1lo = {-0x1.5b72fp-27f}/*sse*/;
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

float log10_float_avx2(float);
float log10_float_avx2(float x){
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
    __m128 log1pu_poly_hi;
    __m128 tmp105;
    __m128 tmp106;
    __m128 tmp107;
    __m128 tmp108;
    __m128 tmp109;
    __m128 tmp110;
    __m128 tmp111;
    __m128 tmp112;
    __m128 tmp113;
    __m128 log1pu_poly_lo;
    __m128 tmp114;
    __m128 tmp115;
    __m128 tmp116;
    uint32_t tmp117;
    uint32_t table_index_hi;
    float tbl_hi;
    __m128 tmp118;
    __m128 tmp119;
    __m128 tmp120;
    __m128 tmp121;
    __m128 tmp122;
    __m128 tmp123;
    __m128 tmp124;
    __m128 tmp125;
    __m128 tmp126;
    uint32_t table_index_lo;
    float tbl_lo;
    __m128 tmp127;
    __m128 tmp128;
    __m128 tmp129;
    __m128 logx_hi;
    float tmp130;
    
    vx_as_int = float_to_32b_encoding(x);
    tmp = _mm_cvtsi128_si32(log10_float_avx2_cst);
    tmp1 = vx_as_int - tmp;
    tmp2 = _mm_cvtsi128_si32(log10_float_avx2_subnormal_mask);
    tmp3 = tmp1 < tmp2;
    tmp4 = _mm_cvtsi128_si32(log10_float_avx2_cst1);
    tmp5 = _mm_cvtsi128_si32(log10_float_avx2_cst2);
    is_subnormal = tmp3 ? tmp4 : tmp5;
    tmp6 = _mm_cvtsi128_si32(log10_float_avx2_field_size);
    tmp7 = _mm_cvtss_f32(log10_float_avx2_fp_one);
    fp_one_as_uint = float_to_32b_encoding(tmp7);
    vx_as_uint = float_to_32b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp8 = float_from_32b_encoding(Zi);
    tmp9 = _mm_set_ss(tmp8);
    Zf = _mm_sub_ss(tmp9, log10_float_avx2_fp_one);
    tmp10 = _mm_cvtss_f32(Zf);
    tmp11 = float_to_32b_encoding(tmp10);
    _srl_cast = tmp11;
    tmp12 = _srl_cast >> tmp6;
    tmp13 = _mm_set1_epi32(tmp12);
    tmp14 = _mm_add_epi32(tmp13, log10_float_avx2_cst3);
    tmp15 = _mm_cvtsi128_si32(tmp14);
    n_value = tmp15 & is_subnormal;
    alpha =  - n_value;
    tmp16 = _mm_cvtsi128_si32(log10_float_avx2_field_size1);
    tmp17 = _mm_set1_epi32(vx_as_int);
    tmp18 = _mm_set1_epi32(alpha);
    tmp19 = tmp17 << tmp18;
    tmp20 = _mm_cvtsi128_si32(tmp19);
    exponent_srl_cast = tmp20;
    tmp21 = exponent_srl_cast >> tmp16;
    tmp22 = _mm_set1_epi32(tmp21);
    tmp23 = _mm_add_epi32(tmp22, log10_float_avx2_cst4);
    normal_vx = float_from_32b_encoding(tmp20);
    tmp24 = ml_mantissa_extraction_fp32(normal_vx);
    tmp25 = _mm_set_ss(tmp24);
    rcp_m = _mm_rcp_ss(tmp25);
    tmp26 = _mm_cvtss_f32(rcp_m);
    tmp27 = float_to_32b_encoding(tmp26);
    tmp28 = _mm_set1_epi32(tmp27);
    tmp29 = _mm_add_epi32(tmp28, log10_float_avx2_cst6);
    tmp30 = _mm_cvtsi128_si32(tmp29);
    id_tmp = tmp30;
    ri_fast_rndn = id_tmp & UINT32_C(-65536);
    ri_bits = ri_fast_rndn >> UINT32_C(16);
    table_index = ri_bits & UINT32_C(255);
    tmp31 = _mm_cvtsi128_si32(log10_float_avx2_cst7);
    tmp32 = ( (int32_t) table_index) > tmp31;
    tmp33 = _mm_cvtsi128_si32(log10_float_avx2_cst8);
    tmp34 = _mm_cvtsi128_si32(log10_float_avx2_cst9);
    tmp35 = tmp32 ? tmp33 : tmp34;
    tmp36 = _mm_set1_epi32(tmp35);
    tau = _mm_add_epi32(tmp36, log10_float_avx2_cst5);
    tmp_eptau = _mm_add_epi32(tmp23, tau);
    tmp37 = _mm_cvtsi128_si32(tmp_eptau);
    tmp38 = tmp37 - alpha;
    fp_exponent = tmp38;
    tmp39 = _mm_set_ss(fp_exponent);
    tmp40 = _mm_mul_ss(tmp39, log10_float_avx2_log2_hi);
    tmp41 = _mm_fmsub_ss(tmp39, log10_float_avx2_log2_hi, tmp40);
    tmp42 = _mm_mul_ss(tmp39, log10_float_avx2_log2_lo);
    tmp43 = _mm_add_ss(tmp41, tmp42);
    tmp44 = _mm_add_ss(tmp40, tmp43);
    tmp45 = float_from_32b_encoding(ri_fast_rndn);
    tmp46 = _mm_set_ss(tmp45);
    u = _mm_fmsub_ss(tmp25, tmp46, log10_float_avx2_fp_one);
    tmp47 = _mm_mul_ss(u, log10_float_avx2_c_4hi);
    tmp48 = _mm_fmsub_ss(u, log10_float_avx2_c_4hi, tmp47);
    tmp49 = _mm_mul_ss(u, log10_float_avx2_c_4lo);
    tmp50 = _mm_add_ss(tmp48, tmp49);
    tmp51 = _mm_add_ss(tmp47, tmp50);
    tmp52 = _mm_add_ss(log10_float_avx2_c_3hi, tmp51);
    tmp53 = _mm_sub_ss(tmp52, tmp51);
    tmp54 = _mm_sub_ss(log10_float_avx2_c_3hi, tmp53);
    tmp55 = _mm_sub_ss(tmp52, tmp53);
    tmp56 = _mm_sub_ss(tmp51, tmp55);
    tmp57 = _mm_add_ss(tmp54, tmp56);
    tmp58 = _mm_sub_ss(tmp51, tmp47);
    tmp59 = _mm_sub_ss(tmp50, tmp58);
    tmp60 = _mm_add_ss(log10_float_avx2_c_3lo, tmp59);
    tmp61 = _mm_add_ss(tmp57, tmp60);
    tmp62 = _mm_add_ss(tmp52, tmp61);
    tmp63 = _mm_mul_ss(u, tmp62);
    tmp64 = _mm_fmsub_ss(u, tmp62, tmp63);
    tmp65 = _mm_sub_ss(tmp62, tmp52);
    tmp66 = _mm_sub_ss(tmp61, tmp65);
    tmp67 = _mm_mul_ss(u, tmp66);
    tmp68 = _mm_add_ss(tmp64, tmp67);
    tmp69 = _mm_add_ss(tmp63, tmp68);
    tmp70 = _mm_add_ss(log10_float_avx2_c_2hi, tmp69);
    tmp71 = _mm_sub_ss(tmp70, tmp69);
    tmp72 = _mm_sub_ss(log10_float_avx2_c_2hi, tmp71);
    tmp73 = _mm_sub_ss(tmp70, tmp71);
    tmp74 = _mm_sub_ss(tmp69, tmp73);
    tmp75 = _mm_add_ss(tmp72, tmp74);
    tmp76 = _mm_sub_ss(tmp69, tmp63);
    tmp77 = _mm_sub_ss(tmp68, tmp76);
    tmp78 = _mm_add_ss(log10_float_avx2_c_2lo, tmp77);
    tmp79 = _mm_add_ss(tmp75, tmp78);
    tmp80 = _mm_add_ss(tmp70, tmp79);
    tmp81 = _mm_mul_ss(u, tmp80);
    tmp82 = _mm_fmsub_ss(u, tmp80, tmp81);
    tmp83 = _mm_sub_ss(tmp80, tmp70);
    tmp84 = _mm_sub_ss(tmp79, tmp83);
    tmp85 = _mm_mul_ss(u, tmp84);
    tmp86 = _mm_add_ss(tmp82, tmp85);
    tmp87 = _mm_add_ss(tmp81, tmp86);
    tmp88 = _mm_add_ss(log10_float_avx2_c_1hi, tmp87);
    tmp89 = _mm_sub_ss(tmp88, tmp87);
    tmp90 = _mm_sub_ss(log10_float_avx2_c_1hi, tmp89);
    tmp91 = _mm_sub_ss(tmp88, tmp89);
    tmp92 = _mm_sub_ss(tmp87, tmp91);
    tmp93 = _mm_add_ss(tmp90, tmp92);
    tmp94 = _mm_sub_ss(tmp87, tmp81);
    tmp95 = _mm_sub_ss(tmp86, tmp94);
    tmp96 = _mm_add_ss(log10_float_avx2_c_1lo, tmp95);
    tmp97 = _mm_add_ss(tmp93, tmp96);
    tmp98 = _mm_add_ss(tmp88, tmp97);
    tmp99 = _mm_mul_ss(u, tmp98);
    tmp100 = _mm_fmsub_ss(u, tmp98, tmp99);
    tmp101 = _mm_sub_ss(tmp98, tmp88);
    tmp102 = _mm_sub_ss(tmp97, tmp101);
    tmp103 = _mm_mul_ss(u, tmp102);
    tmp104 = _mm_add_ss(tmp100, tmp103);
    log1pu_poly_hi = _mm_add_ss(tmp99, tmp104);
    tmp105 = _mm_add_ss(tmp44, log1pu_poly_hi);
    tmp106 = _mm_sub_ss(tmp105, log1pu_poly_hi);
    tmp107 = _mm_sub_ss(tmp44, tmp106);
    tmp108 = _mm_sub_ss(tmp105, tmp106);
    tmp109 = _mm_sub_ss(log1pu_poly_hi, tmp108);
    tmp110 = _mm_add_ss(tmp107, tmp109);
    tmp111 = _mm_sub_ss(tmp44, tmp40);
    tmp112 = _mm_sub_ss(tmp43, tmp111);
    tmp113 = _mm_sub_ss(log1pu_poly_hi, tmp99);
    log1pu_poly_lo = _mm_sub_ss(tmp104, tmp113);
    tmp114 = _mm_add_ss(tmp112, log1pu_poly_lo);
    tmp115 = _mm_add_ss(tmp110, tmp114);
    tmp116 = _mm_add_ss(tmp105, tmp115);
    tmp117 = table_index & UINT32_C(127);
    table_index_hi = tmp117 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp118 = _mm_set_ss(tbl_hi);
    tmp119 = _mm_add_ss(tmp116, tmp118);
    tmp120 = _mm_sub_ss(tmp119, tmp118);
    tmp121 = _mm_sub_ss(tmp116, tmp120);
    tmp122 = _mm_sub_ss(tmp119, tmp120);
    tmp123 = _mm_sub_ss(tmp118, tmp122);
    tmp124 = _mm_add_ss(tmp121, tmp123);
    tmp125 = _mm_sub_ss(tmp116, tmp105);
    tmp126 = _mm_sub_ss(tmp115, tmp125);
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp127 = _mm_set_ss(tbl_lo);
    tmp128 = _mm_add_ss(tmp126, tmp127);
    tmp129 = _mm_add_ss(tmp124, tmp128);
    logx_hi = _mm_add_ss(tmp119, tmp129);
    tmp130 = _mm_cvtss_f32(logx_hi);
    return tmp130;
}
