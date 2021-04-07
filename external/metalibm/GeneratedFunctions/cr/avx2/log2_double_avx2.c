/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 2 --language c \
 *     --accuracy cr --precision double --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/log2_double_avx2.c --fname log2_double_avx2 \
 *     --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <xmmintrin.h>
#include <math.h>
#include <emmintrin.h>
#include <immintrin.h>


static const __m128d log2_double_avx2_fp_one = {1.0}/*sse*/;
static const __m128i log2_double_avx2_cst = {INT32_C(53)}/*sse*/;
static const __m128i log2_double_avx2_cst1 = {INT32_C(-1)}/*sse*/;
static const __m128i log2_double_avx2_cst2 = {INT32_C(0)}/*sse*/;
static const __m128d log2_double_avx2_c_11hi = {0x1.0c9dc776fcc8ap-3}/*sse*/;
static const __m128d log2_double_avx2_c_11lo = {0x1.f83a4d293427fp-57}/*sse*/;
static const __m128d log2_double_avx2_c_10hi = {-0x1.2779b1e27f67cp-3}/*sse*/;
static const __m128d log2_double_avx2_c_10lo = {0x1.b02da63a1ad44p-58}/*sse*/;
static const __m128d log2_double_avx2_c_9hi = {0x1.484b13d31a77p-3}/*sse*/;
static const __m128d log2_double_avx2_c_9lo = {-0x1.9590c0ccdcc61p-57}/*sse*/;
static const __m128d log2_double_avx2_c_8hi = {-0x1.7154764f68fd7p-3}/*sse*/;
static const __m128d log2_double_avx2_c_8lo = {-0x1.3023adeab24b7p-57}/*sse*/;
static const __m128d log2_double_avx2_c_7hi = {0x1.a61762a7adf0dp-3}/*sse*/;
static const __m128d log2_double_avx2_c_7lo = {-0x1.63db6cf18c0d4p-57}/*sse*/;
static const __m128d log2_double_avx2_c_6hi = {-0x1.ec709dc3a0419p-3}/*sse*/;
static const __m128d log2_double_avx2_c_6lo = {0x1.67996ada057c2p-57}/*sse*/;
static const __m128d log2_double_avx2_c_5hi = {0x1.2776c50ef9bfep-2}/*sse*/;
static const __m128d log2_double_avx2_c_5lo = {0x1.e48f96420b1fcp-56}/*sse*/;
static const __m128d log2_double_avx2_c_4hi = {-0x1.71547652b82fep-2}/*sse*/;
static const __m128d log2_double_avx2_c_4lo = {-0x1.774c4dfbea4ap-58}/*sse*/;
static const __m128d log2_double_avx2_c_3hi = {0x1.ec709dc3a03fdp-2}/*sse*/;
static const __m128d log2_double_avx2_c_3lo = {0x1.d27f0559c0f02p-56}/*sse*/;
static const __m128d log2_double_avx2_c_2hi = {-0x1.71547652b82fep-1}/*sse*/;
static const __m128d log2_double_avx2_c_2lo = {-0x1.777d0fff670fcp-57}/*sse*/;
static const __m128d log2_double_avx2_c_1hi = {0x1.71547652b82fep0}/*sse*/;
static const __m128d log2_double_avx2_c_1lo = {0x1.777d0ffda0d2p-56}/*sse*/;
static const double ml_log1p_table[256]  = {
     0.0, 0.0, -0x1.6fe50b6ef0851p-7, -0x1.fe38dec005e54p-61, -0x1.6e79685c2d22ap-6,
     0x1.d6476077b9fbdp-60, -0x1.11cd1d5133413p-5, 0x1.27ebafb056cb9p-61,
     -0x1.6bad3758efd87p-5, -0x1.89b03784b5be1p-60, -0x1.c4dfab90aab5fp-5,
     0x1.60e0f2c3388fp-62, -0x1.0eb389fa29f9bp-4, 0x1.30c22d15199b8p-58,
     -0x1.3aa2fdd27f1c3p-4, 0x1.3fd9776f25acfp-59, -0x1.663f6fac91316p-4,
     -0x1.f3314e0985116p-58, -0x1.918a16e46335bp-4, 0x1.463736dac9317p-58,
     -0x1.bc84240adabbap-4, -0x1.8ecb169b9465fp-58, -0x1.e72ec117fa5b2p-4,
     -0x1.cbdb5d9dc29f2p-60, -0x1.08c588cda79e4p-3, 0x1.a7610e40bd6abp-57,
     -0x1.1dcd197552b7bp-3, -0x1.7a9150c1e0e58p-57, -0x1.32ae9e278ae1ap-3,
     -0x1.f51f2c075a74cp-59, -0x1.476a9f983f74dp-3, -0x1.89c74a0b21fb6p-58,
     -0x1.5c01a39fbd688p-3, 0x1.817fd3b7d7e5dp-57, -0x1.70742d4ef027fp-3,
     -0x1.4e00e7d6bbf3ep-58, -0x1.84c2bd02f03b3p-3, 0x1.16edb88c4e2b5p-62,
     -0x1.98edd077e70dfp-3, -0x1.7d6746548b95cp-62, -0x1.acf5e2db4ec94p-3,
     0x1.01ee1343fe7cap-59, -0x1.c0db6cdd94deep-3, -0x1.0389b662673fcp-57,
     -0x1.d49ee4c32597p-3, 0x1.b85a54d7ee2fdp-58, -0x1.e840be74e6a4dp-3,
     0x1.c1b061571081ep-58, -0x1.fbc16b902680ap-3, -0x1.1d46ccc53c278p-58,
     -0x1.0790adbb03009p-2, -0x1.bc0c69a675517p-56, -0x1.11307dad30b76p-2,
     0x1.a7b47d2c352d9p-57, -0x1.1ac05b291f07p-2, -0x1.4a31ce1b7e328p-56,
     -0x1.24407ab0e073ap-2, 0x1.f6e91ad16ecffp-56, -0x1.2db10fc4d9aafp-2,
     -0x1.bc4de8f631bcfp-56, -0x1.37124cea4cdedp-2, 0x1.3376649b4fc09p-57,
     -0x1.406463b1b0449p-2, -0x1.d6cbcd10948cdp-56, -0x1.49a784bcd1b8bp-2,
     0x1.b6d40900b2502p-62, -0x1.52dbdfc4c96b3p-2, -0x1.f73d83987f26dp-56,
     -0x1.5c01a39fbd688p-2, 0x1.817fd3b7d7e5dp-56, -0x1.6518fe4677ba7p-2,
     0x1.add8712376167p-58, -0x1.6e221cd9d0cdep-2, -0x1.5e35482d13dc1p-56,
     -0x1.771d2ba7efb3cp-2, 0x1.b90132aeddb58p-58, -0x1.800a563161c54p-2,
     -0x1.9575b04fa6fbdp-57, -0x1.88e9c72e0b226p-2, 0x1.6d266d6cdc959p-56,
     -0x1.91bba891f1709p-2, 0x1.2d352bea51e59p-56, -0x1.9a802391e232fp-2,
     -0x1.a5db68721ca61p-57, -0x1.a33760a7f6051p-2, 0x1.8a0efca1a184fp-56,
     -0x1.abe18797f1f49p-2, 0x1.e5b8daaa73a43p-58, -0x1.b47ebf73882a1p-2,
     0x1.6fae441c09d76p-56, -0x1.bd0f2e9e79031p-2, 0x1.52ef4c737fba5p-56,
     -0x1.c592fad295b56p-2, -0x1.f9fb952bbbcccp-56, -0x1.ce0a4923a587dp-2,
     0x1.b517ae88c2fd3p-57, -0x1.d6753e032ea0fp-2, 0x1.c141e66faaaadp-62,
     -0x1.ded3fd442364cp-2, -0x1.3aec658457c41p-56, -0x1.e726aa1e754d2p-2,
     -0x1.8a33c25e8e226p-59, -0x1.ef6d67328e22p-2, -0x1.f47806a0e4105p-56,
     -0x1.f7a8568cb06cfp-2, 0x1.8f3673ffdd785p-57, -0x1.ffd799a83ff9bp-2,
     0x1.18ce032f41d1ep-56, 0x1.f804ae8d0cd02p-2, -0x1.9ca1a3202b3d7p-56,
     0x1.efec61b011f85p-2, 0x1.6d261f1753e0bp-56, 0x1.e7df5fe538ab3p-2,
     0x1.3bed456b24ed1p-56, 0x1.dfdd89d586e2bp-2, 0x1.38c8946414c6ap-59,
     0x1.d7e6c0abc3579p-2, -0x1.e15a52a31604ap-57, 0x1.cffae611ad12bp-2,
     0x1.8a38b4175d665p-56, 0x1.c819dc2d45fe4p-2, 0x1.c4aec56233279p-57,
     0x1.c043859e2fdb3p-2, 0x1.edf515c63dd87p-56, 0x1.b877c57b1b07p-2,
     -0x1.01d98c3531027p-58, 0x1.b0b67f4f4681p-2, -0x1.5e13b838eba7dp-59,
     0x1.a8ff971810a5ep-2, 0x1.817fd3b7d7e5dp-58, 0x1.a152f142981b4p-2,
     -0x1.4278cd1699312p-57, 0x1.99b072a96c6b2p-2, 0x1.bca36fd02defp-56,
     0x1.921800924dd3bp-2, 0x1.fdc46af571993p-56, 0x1.8a8980abfbd32p-2,
     0x1.99aa6df8b7d83p-56, 0x1.8304d90c11fd3p-2, 0x1.51d58525aad39p-57,
     0x1.7b89f02cf2aadp-2, 0x1.8f89e2eb553b2p-57, 0x1.7418acebbf18fp-2,
     -0x1.26bfff0133975p-56, 0x1.6cb0f6865c8eap-2, 0x1.b6d40900b2502p-61,
     0x1.6552b49986277p-2, 0x1.ac9080333c605p-56, 0x1.5dfdcf1eeae0ep-2,
     0x1.10b5b643a6ecbp-56, 0x1.56b22e6b578e5p-2, -0x1.8d86531d55da2p-56,
     0x1.4f6fbb2cec598p-2, 0x1.e393a16b94b52p-56, 0x1.48365e695d797p-2,
     -0x1.5759f8091112dp-56, 0x1.4106017c3eca3p-2, -0x1.c658d602e66bp-56,
     0x1.39de8e1559f6fp-2, 0x1.fcad2f4710ep-56, 0x1.32bfee370ee68p-2,
     0x1.968925e378d68p-56, 0x1.2baa0c34be1ecp-2, -0x1.0132ae5e417cdp-58,
     0x1.249cd2b13cd6cp-2, 0x1.34107c0e54aedp-56, 0x1.1d982c9d52708p-2,
     0x1.ae9804237ec8ep-57, 0x1.169c05363f158p-2, 0x1.c8d43e017579bp-56,
     0x1.0fa848044b351p-2, 0x1.0de07b685556fp-59, 0x1.08bce0d95fa38p-2,
     -0x1.3d56efe4338fep-58, 0x1.01d9bbcfa61d4p-2, 0x1.768994400ca0ap-56,
     0x1.f5fd8a9063e35p-3, -0x1.bdc0426c3c274p-57, 0x1.e857d3d361368p-3,
     -0x1.086fce864a1f6p-57, 0x1.dac22d3e441d3p-3, -0x1.ba8b1f646ab12p-63,
     0x1.cd3c712d31109p-3, 0x1.92eeaf409cc88p-58, 0x1.bfc67a7fff4ccp-3,
     0x1.bc0af7b82e7d7p-61, 0x1.b2602497d5346p-3, -0x1.cc865b3dd0dbbp-57,
     0x1.a5094b54d2828p-3, 0x1.013b6eaceb921p-57, 0x1.97c1cb13c7ec1p-3,
     -0x1.e95734abd2fccp-57, 0x1.8a8980abfbd32p-3, 0x1.99aa6df8b7d83p-57,
     0x1.7d60496cfbb4cp-3, 0x1.9ced1447e30adp-57, 0x1.7046031c79f85p-3,
     -0x1.0798d1aa21694p-57, 0x1.633a8bf437ce1p-3, 0x1.54fae008fbb59p-60,
     0x1.563dc29ffacb2p-3, 0x1.90e41bca6ef96p-60, 0x1.494f863b8df35p-3,
     -0x1.1562d61af73f8p-57, 0x1.3c6fb650cde51p-3, -0x1.7a6ed4e1b0936p-57,
     0x1.2f9e32d5bfdd1p-3, -0x1.978b98f7dedf9p-57, 0x1.22dadc2ab3497p-3,
     -0x1.696e2866c718ep-58, 0x1.162593186da7p-3, -0x1.df0fdbc295d19p-58,
     0x1.097e38ce60649p-3, 0x1.5d243efd93259p-58, 0x1.f9c95dc1d1165p-4,
     -0x1.6cd4d2ae3a2f6p-60, 0x1.e0b1ae8f2fd56p-4, 0x1.92ce9636c90ap-58,
     0x1.c7b528b70f1c5p-4, -0x1.7936311889913p-62, 0x1.aed391ab6674ep-4,
     0x1.40238de7ea9f1p-58, 0x1.960caf9abb7cap-4, -0x1.21ba488a62577p-60,
     0x1.7d60496cfbb4cp-4, 0x1.9ced1447e30adp-58, 0x1.64ce26c067157p-4,
     -0x1.2f06f5b695b1dp-58, 0x1.4c560fe68af88p-4, 0x1.c141e66faaaadp-61,
     0x1.33f7cde14cf5ap-4, -0x1.e20375a3220bap-60, 0x1.1bb32a600549dp-4,
     0x1.98c5452bbce74p-61, 0x1.0387efbca869ep-4, -0x1.7de9078d157a3p-58,
     0x1.d6ebd1f1febfep-5, 0x1.155660710eb2ap-63, 0x1.a6f9c377dd31bp-5,
     -0x1.86446a6eb19b1p-59, 0x1.77394c9d958d5p-5, 0x1.77970e03f821cp-59,
     0x1.47aa07357704fp-5, 0x1.5a51cc6227b89p-60, 0x1.184b8e4c56af8p-5,
     0x1.491f06c085bc2p-60, 0x1.d23afc49139f9p-6, -0x1.90c94610afb5fp-60,
     0x1.743ee861f3556p-6, 0x1.b2a41b08fbe06p-61, 0x1.16a21e20a0a45p-6,
     0x1.79268271cbde1p-63, 0x1.72c7ba20f7327p-7, 0x1.6d746128b1857p-61,
     0x1.720d9c06a835fp-8, -0x1.64439c1a2068ap-62
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

double log2_double_avx2(double);
double log2_double_avx2(double x){
    int64_t vx_as_int;
    int64_t tmp;
    int tmp1;
    int64_t is_subnormal;
    double tmp2;
    uint64_t fp_one_as_uint;
    uint64_t vx_as_uint;
    uint64_t Zi;
    double tmp3;
    double Zf;
    int64_t tmp4;
    uint64_t _srl_cast;
    int64_t tmp5;
    int64_t tmp6;
    int64_t n_value;
    int64_t alpha;
    int64_t tmp7;
    double normal_vx;
    double tmp8;
    float id_tmp;
    int32_t tmp9;
    uint32_t _srl_cast1;
    int32_t tmp10;
    int32_t inv_index;
    float tmp11;
    float tmp12;
    int32_t op_exp;
    int32_t tmp13;
    float approx_exp;
    __m128 carg;
    __m128 carg1;
    __m128 carg2;
    float tmp14;
    __m128 carg3;
    __m128 carg4;
    __m128 carg5;
    float inv_approx;
    double id_tmp1;
    int64_t tmp15;
    int64_t tmp16;
    uint64_t id_tmp2;
    uint64_t ri_fast_rndn;
    uint64_t ri_bits;
    uint32_t table_index;
    uint32_t tmp17;
    uint32_t table_index_hi;
    double tbl_hi;
    int32_t tmp18;
    int tmp19;
    int32_t tmp20;
    int32_t tmp21;
    int32_t tmp22;
    uint64_t exponent_srl_cast;
    int64_t tmp23;
    int64_t tmp24;
    int64_t tmp_eptau;
    int64_t tmp25;
    double fp_exponent;
    __m128d tmp26;
    double tmp27;
    __m128d tmp28;
    __m128d u;
    double tmp29;
    double tmp30;
    double tmp31;
    double tmp32;
    double tmp33;
    __m128d tmp34;
    __m128d tmp35;
    double tmp36;
    double tmp37;
    double tmp38;
    double tmp39;
    double tmp40;
    double tmp41;
    double tmp42;
    double tmp43;
    double tmp44;
    double tmp45;
    double tmp46;
    double tmp47;
    double tmp48;
    double tmp49;
    double tmp50;
    double tmp51;
    double tmp52;
    double tmp53;
    double tmp54;
    double tmp55;
    __m128d tmp56;
    __m128d tmp57;
    __m128d tmp58;
    double tmp59;
    double tmp60;
    double tmp61;
    double tmp62;
    double tmp63;
    double tmp64;
    double tmp65;
    double tmp66;
    double tmp67;
    double tmp68;
    double tmp69;
    double tmp70;
    double tmp71;
    double tmp72;
    double tmp73;
    double tmp74;
    double tmp75;
    double tmp76;
    double tmp77;
    double tmp78;
    __m128d tmp79;
    __m128d tmp80;
    __m128d tmp81;
    double tmp82;
    double tmp83;
    double tmp84;
    double tmp85;
    double tmp86;
    double tmp87;
    double tmp88;
    double tmp89;
    double tmp90;
    double tmp91;
    double tmp92;
    double tmp93;
    double tmp94;
    double tmp95;
    double tmp96;
    double tmp97;
    double tmp98;
    double tmp99;
    double tmp100;
    double tmp101;
    __m128d tmp102;
    __m128d tmp103;
    __m128d tmp104;
    double tmp105;
    double tmp106;
    double tmp107;
    double tmp108;
    double tmp109;
    double tmp110;
    double tmp111;
    double tmp112;
    double tmp113;
    double tmp114;
    double tmp115;
    double tmp116;
    double tmp117;
    double tmp118;
    double tmp119;
    double tmp120;
    double tmp121;
    double tmp122;
    double tmp123;
    double tmp124;
    __m128d tmp125;
    __m128d tmp126;
    __m128d tmp127;
    double tmp128;
    double tmp129;
    double tmp130;
    double tmp131;
    double tmp132;
    double tmp133;
    double tmp134;
    double tmp135;
    double tmp136;
    double tmp137;
    double tmp138;
    double tmp139;
    double tmp140;
    double tmp141;
    double tmp142;
    double tmp143;
    double tmp144;
    double tmp145;
    double tmp146;
    double tmp147;
    __m128d tmp148;
    __m128d tmp149;
    __m128d tmp150;
    double tmp151;
    double tmp152;
    double tmp153;
    double tmp154;
    double tmp155;
    double tmp156;
    double tmp157;
    double tmp158;
    double tmp159;
    double tmp160;
    double tmp161;
    double tmp162;
    double tmp163;
    double tmp164;
    double tmp165;
    double tmp166;
    double tmp167;
    double tmp168;
    double tmp169;
    double tmp170;
    __m128d tmp171;
    __m128d tmp172;
    __m128d tmp173;
    double tmp174;
    double tmp175;
    double tmp176;
    double tmp177;
    double tmp178;
    double tmp179;
    double tmp180;
    double tmp181;
    double tmp182;
    double tmp183;
    double tmp184;
    double tmp185;
    double tmp186;
    double tmp187;
    double tmp188;
    double tmp189;
    double tmp190;
    double tmp191;
    double tmp192;
    double tmp193;
    __m128d tmp194;
    __m128d tmp195;
    __m128d tmp196;
    double tmp197;
    double tmp198;
    double tmp199;
    double tmp200;
    double tmp201;
    double tmp202;
    double tmp203;
    double tmp204;
    double tmp205;
    double tmp206;
    double tmp207;
    double tmp208;
    double tmp209;
    double tmp210;
    double tmp211;
    double tmp212;
    double tmp213;
    double tmp214;
    double tmp215;
    double tmp216;
    __m128d tmp217;
    __m128d tmp218;
    __m128d tmp219;
    double tmp220;
    double tmp221;
    double tmp222;
    double tmp223;
    double tmp224;
    double tmp225;
    double tmp226;
    double tmp227;
    double tmp228;
    double tmp229;
    double tmp230;
    double tmp231;
    double tmp232;
    double tmp233;
    double tmp234;
    double tmp235;
    double tmp236;
    double tmp237;
    double tmp238;
    double tmp239;
    __m128d tmp240;
    __m128d tmp241;
    __m128d tmp242;
    double tmp243;
    double tmp244;
    double tmp245;
    double tmp246;
    double tmp247;
    double tmp248;
    double tmp249;
    double tmp250;
    double tmp251;
    double tmp252;
    double tmp253;
    double tmp254;
    double tmp255;
    double tmp256;
    double tmp257;
    double tmp258;
    double tmp259;
    double tmp260;
    double tmp261;
    double tmp262;
    __m128d tmp263;
    __m128d tmp264;
    __m128d tmp265;
    double tmp266;
    double tmp267;
    double log1pu_poly_hi;
    double tmp268;
    double tmp269;
    double log1pu_poly_lo;
    double tmp270;
    double tmp271;
    double tmp272;
    double tmp273;
    double tmp274;
    double tmp275;
    double tmp276;
    double tmp277;
    double tmp278;
    double tmp279;
    double tmp280;
    double tmp281;
    double tmp282;
    uint32_t table_index_lo;
    double tbl_lo;
    double tmp283;
    double tmp284;
    double tmp285;
    double tmp286;
    double logx_hi;
    
    vx_as_int = double_to_64b_encoding(x);
    tmp = vx_as_int - INT64_C(1);
    tmp1 = tmp < INT64_C(4503599627370495);
    is_subnormal = tmp1 ? INT64_C(-1) : INT64_C(0);
    tmp2 = _mm_cvtsd_f64(log2_double_avx2_fp_one);
    fp_one_as_uint = double_to_64b_encoding(tmp2);
    vx_as_uint = double_to_64b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp3 = double_from_64b_encoding(Zi);
    Zf = tmp3 - tmp2;
    tmp4 = double_to_64b_encoding(Zf);
    _srl_cast = tmp4;
    tmp5 = _srl_cast >> INT64_C(52);
    tmp6 = tmp5 + INT64_C(-1023);
    n_value = tmp6 & is_subnormal;
    alpha =  - n_value;
    tmp7 = vx_as_int << alpha;
    normal_vx = double_from_64b_encoding(tmp7);
    tmp8 = ml_mantissa_extraction_fp64(normal_vx);
    id_tmp = tmp8;
    tmp9 = float_to_32b_encoding(id_tmp);
    _srl_cast1 = tmp9;
    tmp10 = _srl_cast1 >> INT32_C(16);
    inv_index = tmp10 & INT32_C(127);
    tmp11 = table[inv_index];
    tmp12 = copysignf(1.0f, id_tmp);
    op_exp = ml_exp_extraction_dirty_fp32(id_tmp);
    tmp13 =  - op_exp;
    approx_exp = ml_exp_insertion_fp32(tmp13);
    carg = _mm_set_ss(approx_exp);
    carg1 = _mm_set_ss(tmp12);
    carg2 = _mm_mul_ss(carg, carg1);
    tmp14 = _mm_cvtss_f32(carg2);
    carg3 = _mm_set_ss(tmp11);
    carg4 = _mm_set_ss(tmp14);
    carg5 = _mm_mul_ss(carg3, carg4);
    inv_approx = _mm_cvtss_f32(carg5);
    id_tmp1 = inv_approx;
    tmp15 = double_to_64b_encoding(id_tmp1);
    tmp16 = tmp15 + INT64_C(17592186044416);
    id_tmp2 = tmp16;
    ri_fast_rndn = id_tmp2 & UINT64_C(-35184372088832);
    ri_bits = ri_fast_rndn >> UINT64_C(45);
    table_index = ( (uint32_t) ri_bits) & UINT32_C(255);
    tmp17 = table_index & UINT32_C(127);
    table_index_hi = tmp17 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp18 = _mm_cvtsi128_si32(log2_double_avx2_cst);
    tmp19 = ( (int32_t) table_index) > tmp18;
    tmp20 = _mm_cvtsi128_si32(log2_double_avx2_cst1);
    tmp21 = _mm_cvtsi128_si32(log2_double_avx2_cst2);
    tmp22 = tmp19 ? tmp20 : tmp21;
    exponent_srl_cast = tmp7;
    tmp23 = exponent_srl_cast >> INT64_C(52);
    tmp24 = tmp23 + INT64_C(-1023);
    tmp_eptau = tmp24 + ( (int64_t) tmp22);
    tmp25 = tmp_eptau - alpha;
    fp_exponent = tmp25;
    tmp26 = _mm_set_sd(tmp8);
    tmp27 = double_from_64b_encoding(ri_fast_rndn);
    tmp28 = _mm_set_sd(tmp27);
    u = _mm_fmsub_sd(tmp26, tmp28, log2_double_avx2_fp_one);
    tmp29 = _mm_cvtsd_f64(u);
    tmp30 = _mm_cvtsd_f64(log2_double_avx2_c_11hi);
    tmp31 = tmp29 * tmp30;
    tmp32 = _mm_cvtsd_f64(log2_double_avx2_c_11lo);
    tmp33 = tmp29 * tmp32;
    tmp34 = _mm_set_sd(tmp31);
    tmp35 = _mm_fmsub_sd(u, log2_double_avx2_c_11hi, tmp34);
    tmp36 = _mm_cvtsd_f64(tmp35);
    tmp37 = tmp36 + tmp33;
    tmp38 = tmp31 + tmp37;
    tmp39 = _mm_cvtsd_f64(log2_double_avx2_c_10hi);
    tmp40 = tmp39 + tmp38;
    tmp41 = tmp40 - tmp38;
    tmp42 = tmp39 - tmp41;
    tmp43 = tmp40 - tmp41;
    tmp44 = tmp38 - tmp43;
    tmp45 = tmp42 + tmp44;
    tmp46 = tmp38 - tmp31;
    tmp47 = tmp37 - tmp46;
    tmp48 = _mm_cvtsd_f64(log2_double_avx2_c_10lo);
    tmp49 = tmp48 + tmp47;
    tmp50 = tmp45 + tmp49;
    tmp51 = tmp40 + tmp50;
    tmp52 = tmp29 * tmp51;
    tmp53 = tmp51 - tmp40;
    tmp54 = tmp50 - tmp53;
    tmp55 = tmp29 * tmp54;
    tmp56 = _mm_set_sd(tmp51);
    tmp57 = _mm_set_sd(tmp52);
    tmp58 = _mm_fmsub_sd(u, tmp56, tmp57);
    tmp59 = _mm_cvtsd_f64(tmp58);
    tmp60 = tmp59 + tmp55;
    tmp61 = tmp52 + tmp60;
    tmp62 = _mm_cvtsd_f64(log2_double_avx2_c_9hi);
    tmp63 = tmp62 + tmp61;
    tmp64 = tmp63 - tmp61;
    tmp65 = tmp62 - tmp64;
    tmp66 = tmp63 - tmp64;
    tmp67 = tmp61 - tmp66;
    tmp68 = tmp65 + tmp67;
    tmp69 = tmp61 - tmp52;
    tmp70 = tmp60 - tmp69;
    tmp71 = _mm_cvtsd_f64(log2_double_avx2_c_9lo);
    tmp72 = tmp71 + tmp70;
    tmp73 = tmp68 + tmp72;
    tmp74 = tmp63 + tmp73;
    tmp75 = tmp29 * tmp74;
    tmp76 = tmp74 - tmp63;
    tmp77 = tmp73 - tmp76;
    tmp78 = tmp29 * tmp77;
    tmp79 = _mm_set_sd(tmp74);
    tmp80 = _mm_set_sd(tmp75);
    tmp81 = _mm_fmsub_sd(u, tmp79, tmp80);
    tmp82 = _mm_cvtsd_f64(tmp81);
    tmp83 = tmp82 + tmp78;
    tmp84 = tmp75 + tmp83;
    tmp85 = _mm_cvtsd_f64(log2_double_avx2_c_8hi);
    tmp86 = tmp85 + tmp84;
    tmp87 = tmp86 - tmp84;
    tmp88 = tmp85 - tmp87;
    tmp89 = tmp86 - tmp87;
    tmp90 = tmp84 - tmp89;
    tmp91 = tmp88 + tmp90;
    tmp92 = tmp84 - tmp75;
    tmp93 = tmp83 - tmp92;
    tmp94 = _mm_cvtsd_f64(log2_double_avx2_c_8lo);
    tmp95 = tmp94 + tmp93;
    tmp96 = tmp91 + tmp95;
    tmp97 = tmp86 + tmp96;
    tmp98 = tmp29 * tmp97;
    tmp99 = tmp97 - tmp86;
    tmp100 = tmp96 - tmp99;
    tmp101 = tmp29 * tmp100;
    tmp102 = _mm_set_sd(tmp97);
    tmp103 = _mm_set_sd(tmp98);
    tmp104 = _mm_fmsub_sd(u, tmp102, tmp103);
    tmp105 = _mm_cvtsd_f64(tmp104);
    tmp106 = tmp105 + tmp101;
    tmp107 = tmp98 + tmp106;
    tmp108 = _mm_cvtsd_f64(log2_double_avx2_c_7hi);
    tmp109 = tmp108 + tmp107;
    tmp110 = tmp109 - tmp107;
    tmp111 = tmp108 - tmp110;
    tmp112 = tmp109 - tmp110;
    tmp113 = tmp107 - tmp112;
    tmp114 = tmp111 + tmp113;
    tmp115 = tmp107 - tmp98;
    tmp116 = tmp106 - tmp115;
    tmp117 = _mm_cvtsd_f64(log2_double_avx2_c_7lo);
    tmp118 = tmp117 + tmp116;
    tmp119 = tmp114 + tmp118;
    tmp120 = tmp109 + tmp119;
    tmp121 = tmp29 * tmp120;
    tmp122 = tmp120 - tmp109;
    tmp123 = tmp119 - tmp122;
    tmp124 = tmp29 * tmp123;
    tmp125 = _mm_set_sd(tmp120);
    tmp126 = _mm_set_sd(tmp121);
    tmp127 = _mm_fmsub_sd(u, tmp125, tmp126);
    tmp128 = _mm_cvtsd_f64(tmp127);
    tmp129 = tmp128 + tmp124;
    tmp130 = tmp121 + tmp129;
    tmp131 = _mm_cvtsd_f64(log2_double_avx2_c_6hi);
    tmp132 = tmp131 + tmp130;
    tmp133 = tmp132 - tmp130;
    tmp134 = tmp131 - tmp133;
    tmp135 = tmp132 - tmp133;
    tmp136 = tmp130 - tmp135;
    tmp137 = tmp134 + tmp136;
    tmp138 = tmp130 - tmp121;
    tmp139 = tmp129 - tmp138;
    tmp140 = _mm_cvtsd_f64(log2_double_avx2_c_6lo);
    tmp141 = tmp140 + tmp139;
    tmp142 = tmp137 + tmp141;
    tmp143 = tmp132 + tmp142;
    tmp144 = tmp29 * tmp143;
    tmp145 = tmp143 - tmp132;
    tmp146 = tmp142 - tmp145;
    tmp147 = tmp29 * tmp146;
    tmp148 = _mm_set_sd(tmp143);
    tmp149 = _mm_set_sd(tmp144);
    tmp150 = _mm_fmsub_sd(u, tmp148, tmp149);
    tmp151 = _mm_cvtsd_f64(tmp150);
    tmp152 = tmp151 + tmp147;
    tmp153 = tmp144 + tmp152;
    tmp154 = _mm_cvtsd_f64(log2_double_avx2_c_5hi);
    tmp155 = tmp154 + tmp153;
    tmp156 = tmp155 - tmp153;
    tmp157 = tmp154 - tmp156;
    tmp158 = tmp155 - tmp156;
    tmp159 = tmp153 - tmp158;
    tmp160 = tmp157 + tmp159;
    tmp161 = tmp153 - tmp144;
    tmp162 = tmp152 - tmp161;
    tmp163 = _mm_cvtsd_f64(log2_double_avx2_c_5lo);
    tmp164 = tmp163 + tmp162;
    tmp165 = tmp160 + tmp164;
    tmp166 = tmp155 + tmp165;
    tmp167 = tmp29 * tmp166;
    tmp168 = tmp166 - tmp155;
    tmp169 = tmp165 - tmp168;
    tmp170 = tmp29 * tmp169;
    tmp171 = _mm_set_sd(tmp166);
    tmp172 = _mm_set_sd(tmp167);
    tmp173 = _mm_fmsub_sd(u, tmp171, tmp172);
    tmp174 = _mm_cvtsd_f64(tmp173);
    tmp175 = tmp174 + tmp170;
    tmp176 = tmp167 + tmp175;
    tmp177 = _mm_cvtsd_f64(log2_double_avx2_c_4hi);
    tmp178 = tmp177 + tmp176;
    tmp179 = tmp178 - tmp176;
    tmp180 = tmp177 - tmp179;
    tmp181 = tmp178 - tmp179;
    tmp182 = tmp176 - tmp181;
    tmp183 = tmp180 + tmp182;
    tmp184 = tmp176 - tmp167;
    tmp185 = tmp175 - tmp184;
    tmp186 = _mm_cvtsd_f64(log2_double_avx2_c_4lo);
    tmp187 = tmp186 + tmp185;
    tmp188 = tmp183 + tmp187;
    tmp189 = tmp178 + tmp188;
    tmp190 = tmp29 * tmp189;
    tmp191 = tmp189 - tmp178;
    tmp192 = tmp188 - tmp191;
    tmp193 = tmp29 * tmp192;
    tmp194 = _mm_set_sd(tmp189);
    tmp195 = _mm_set_sd(tmp190);
    tmp196 = _mm_fmsub_sd(u, tmp194, tmp195);
    tmp197 = _mm_cvtsd_f64(tmp196);
    tmp198 = tmp197 + tmp193;
    tmp199 = tmp190 + tmp198;
    tmp200 = _mm_cvtsd_f64(log2_double_avx2_c_3hi);
    tmp201 = tmp200 + tmp199;
    tmp202 = tmp201 - tmp199;
    tmp203 = tmp200 - tmp202;
    tmp204 = tmp201 - tmp202;
    tmp205 = tmp199 - tmp204;
    tmp206 = tmp203 + tmp205;
    tmp207 = tmp199 - tmp190;
    tmp208 = tmp198 - tmp207;
    tmp209 = _mm_cvtsd_f64(log2_double_avx2_c_3lo);
    tmp210 = tmp209 + tmp208;
    tmp211 = tmp206 + tmp210;
    tmp212 = tmp201 + tmp211;
    tmp213 = tmp29 * tmp212;
    tmp214 = tmp212 - tmp201;
    tmp215 = tmp211 - tmp214;
    tmp216 = tmp29 * tmp215;
    tmp217 = _mm_set_sd(tmp212);
    tmp218 = _mm_set_sd(tmp213);
    tmp219 = _mm_fmsub_sd(u, tmp217, tmp218);
    tmp220 = _mm_cvtsd_f64(tmp219);
    tmp221 = tmp220 + tmp216;
    tmp222 = tmp213 + tmp221;
    tmp223 = _mm_cvtsd_f64(log2_double_avx2_c_2hi);
    tmp224 = tmp223 + tmp222;
    tmp225 = tmp224 - tmp222;
    tmp226 = tmp223 - tmp225;
    tmp227 = tmp224 - tmp225;
    tmp228 = tmp222 - tmp227;
    tmp229 = tmp226 + tmp228;
    tmp230 = tmp222 - tmp213;
    tmp231 = tmp221 - tmp230;
    tmp232 = _mm_cvtsd_f64(log2_double_avx2_c_2lo);
    tmp233 = tmp232 + tmp231;
    tmp234 = tmp229 + tmp233;
    tmp235 = tmp224 + tmp234;
    tmp236 = tmp29 * tmp235;
    tmp237 = tmp235 - tmp224;
    tmp238 = tmp234 - tmp237;
    tmp239 = tmp29 * tmp238;
    tmp240 = _mm_set_sd(tmp235);
    tmp241 = _mm_set_sd(tmp236);
    tmp242 = _mm_fmsub_sd(u, tmp240, tmp241);
    tmp243 = _mm_cvtsd_f64(tmp242);
    tmp244 = tmp243 + tmp239;
    tmp245 = tmp236 + tmp244;
    tmp246 = _mm_cvtsd_f64(log2_double_avx2_c_1hi);
    tmp247 = tmp246 + tmp245;
    tmp248 = tmp247 - tmp245;
    tmp249 = tmp246 - tmp248;
    tmp250 = tmp247 - tmp248;
    tmp251 = tmp245 - tmp250;
    tmp252 = tmp249 + tmp251;
    tmp253 = tmp245 - tmp236;
    tmp254 = tmp244 - tmp253;
    tmp255 = _mm_cvtsd_f64(log2_double_avx2_c_1lo);
    tmp256 = tmp255 + tmp254;
    tmp257 = tmp252 + tmp256;
    tmp258 = tmp247 + tmp257;
    tmp259 = tmp29 * tmp258;
    tmp260 = tmp258 - tmp247;
    tmp261 = tmp257 - tmp260;
    tmp262 = tmp29 * tmp261;
    tmp263 = _mm_set_sd(tmp258);
    tmp264 = _mm_set_sd(tmp259);
    tmp265 = _mm_fmsub_sd(u, tmp263, tmp264);
    tmp266 = _mm_cvtsd_f64(tmp265);
    tmp267 = tmp266 + tmp262;
    log1pu_poly_hi = tmp259 + tmp267;
    tmp268 = fp_exponent + log1pu_poly_hi;
    tmp269 = log1pu_poly_hi - tmp259;
    log1pu_poly_lo = tmp267 - tmp269;
    tmp270 = tmp268 - log1pu_poly_hi;
    tmp271 = fp_exponent - tmp270;
    tmp272 = tmp268 - tmp270;
    tmp273 = log1pu_poly_hi - tmp272;
    tmp274 = tmp271 + tmp273;
    tmp275 = tmp274 + log1pu_poly_lo;
    tmp276 = tmp268 + tmp275;
    tmp277 = tmp276 + tbl_hi;
    tmp278 = tmp277 - tbl_hi;
    tmp279 = tmp276 - tmp278;
    tmp280 = tmp277 - tmp278;
    tmp281 = tbl_hi - tmp280;
    tmp282 = tmp279 + tmp281;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp283 = tmp276 - tmp268;
    tmp284 = tmp275 - tmp283;
    tmp285 = tmp284 + tbl_lo;
    tmp286 = tmp282 + tmp285;
    logx_hi = tmp277 + tmp286;
    return logx_hi;
}
