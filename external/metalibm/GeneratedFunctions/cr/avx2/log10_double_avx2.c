/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 10 --language c \
 *     --accuracy cr --precision double --target x86_avx2 --output \
 *     GeneratedFunctions/cr/avx2/log10_double_avx2.c --fname \
 *     log10_double_avx2 --extra-passes \
 *     beforecodegen:basic_legalization,beforecodegen:expand_multi_precision,beforecodegen:virtual_vector_bool_legalization,beforecodegen:m128_promotion,beforecodegen:m256_promotion,beforecodegen:vector_mask_test_legalization
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <xmmintrin.h>
#include <math.h>
#include <immintrin.h>
#include <emmintrin.h>


static const __m128d log10_double_avx2_fp_one = {1.0}/*sse*/;
static const __m128d log10_double_avx2_c_11hi = {0x1.43721e678c758p-5}/*sse*/;
static const __m128d log10_double_avx2_c_11lo = {0x1.4b1fac2c45c7ep-60}/*sse*/;
static const __m128d log10_double_avx2_c_10hi = {-0x1.63c9ad226aaccp-5}/*sse*/;
static const __m128d log10_double_avx2_c_10lo = {-0x1.12b117351a3a2p-60}/*sse*/;
static const __m128d log10_double_avx2_c_9hi = {0x1.8b4df2eebcfb3p-5}/*sse*/;
static const __m128d log10_double_avx2_c_9lo = {-0x1.0d5229ad41226p-59}/*sse*/;
static const __m128d log10_double_avx2_c_8hi = {-0x1.bcb7b14e72305p-5}/*sse*/;
static const __m128d log10_double_avx2_c_8lo = {0x1.81941204622acp-60}/*sse*/;
static const __m128d log10_double_avx2_c_7hi = {0x1.fc3fa615105fep-5}/*sse*/;
static const __m128d log10_double_avx2_c_7lo = {-0x1.6ca0627978a4ap-60}/*sse*/;
static const __m128d log10_double_avx2_c_6hi = {-0x1.287a7636f436fp-4}/*sse*/;
static const __m128d log10_double_avx2_c_6lo = {-0x1.5d4fda08566ccp-59}/*sse*/;
static const __m128d log10_double_avx2_c_5hi = {0x1.63c62775250d8p-4}/*sse*/;
static const __m128d log10_double_avx2_c_5lo = {0x1.43e50af6205a6p-59}/*sse*/;
static const __m128d log10_double_avx2_c_4hi = {-0x1.bcb7b1526e50ep-4}/*sse*/;
static const __m128d log10_double_avx2_c_4lo = {-0x1.951800bd0e9e8p-59}/*sse*/;
static const __m128d log10_double_avx2_c_3hi = {0x1.287a7636f435fp-3}/*sse*/;
static const __m128d log10_double_avx2_c_3lo = {-0x1.9c8718343fd18p-58}/*sse*/;
static const __m128d log10_double_avx2_c_2hi = {-0x1.bcb7b1526e50ep-3}/*sse*/;
static const __m128d log10_double_avx2_c_2lo = {-0x1.95355babc1284p-58}/*sse*/;
static const __m128d log10_double_avx2_c_1hi = {0x1.bcb7b1526e50ep-2}/*sse*/;
static const __m128d log10_double_avx2_c_1lo = {0x1.95355baaafad2p-57}/*sse*/;
static const __m128i log10_double_avx2_cst = {INT32_C(53)}/*sse*/;
static const __m128i log10_double_avx2_cst1 = {INT32_C(-1)}/*sse*/;
static const __m128i log10_double_avx2_cst2 = {INT32_C(0)}/*sse*/;
static const __m128d log10_double_avx2_log2_hi = {0x1.34413509f79ffp-2}/*sse*/;
static const __m128d log10_double_avx2_log2_lo = {-0x1.9dc1da994fd21p-59}/*sse*/;
static const double ml_log1p_table[256]  = {
     0.0, 0.0, -0x1.bafd47221ed26p-9, -0x1.9706ea523f0a5p-63, -0x1.b9476a4fcd10fp-8,
     0x1.3b252df477a75p-63, -0x1.49b0851443684p-7, 0x1.8f207a6d0d0b1p-62,
     -0x1.b5e908eb1379p-7, -0x1.f2e9fe367a511p-64, -0x1.10a83a8446c78p-6,
     0x1.7b9fd5428084fp-60, -0x1.45f4f5acb8bep-6, -0x1.dda7897a55eb5p-60,
     -0x1.7adc3df3b1ff8p-6, -0x1.b980714c596a3p-62, -0x1.af5f92b00e61p-6,
     0x1.6487d64961833p-60, -0x1.e3806acbd058fp-6, -0x1.af3eb3b443356p-63,
     -0x1.0ba01a817p-5, -0x1.5f1d45244f437p-60, -0x1.25502c0fc314cp-5,
     0x1.ff894a084ae68p-59, -0x1.3ed1199a5e425p-5, -0x1.ba93eba3e387fp-64,
     -0x1.58238eeb353dap-5, -0x1.efd454f7ea69ap-59, -0x1.71483427d2a99p-5,
     0x1.8f0f77fcff1d9p-60, -0x1.8a3fadeb847f4p-5, 0x1.b144b06126f68p-59,
     -0x1.a30a9d609efeap-5, 0x1.ebf33e9410429p-60, -0x1.bba9a058dfd84p-5,
     -0x1.a9796c3448989p-61, -0x1.d41d5164facb4p-5, 0x1.7f9dc537bfbfbp-59,
     -0x1.ec6647eb58808p-5, -0x1.1f406230b3528p-59, -0x1.02428c1f08016p-4,
     0x1.5943d4373d44ap-60, -0x1.0e3d29d81165ep-4, -0x1.89565863c8cf4p-58,
     -0x1.1a23445501816p-4, 0x1.f990c2c07d3b5p-59, -0x1.25f5215eb594ap-4,
     0x1.06ad025ca3a44p-59, -0x1.31b3055c47118p-4, -0x1.b420b9b202eddp-64,
     -0x1.3d5d335c53179p-4, 0x1.a83d8a6eb8e2ep-59, -0x1.48f3ed1df48fbp-4,
     -0x1.782120ed9fd02p-58, -0x1.5477731973e85p-4, 0x1.e1bcfb0476f5dp-58,
     -0x1.5fe80488af4fdp-4, 0x1.5b6acfce71752p-58, -0x1.6b45df6f3e2c9p-4,
     -0x1.643835531d8eep-58, -0x1.769140a2526fdp-4, 0x1.ac4c370ae3c1dp-58,
     -0x1.81ca63d05a44ap-4, 0x1.f639ecb00a83ap-58, -0x1.8cf183886480dp-4,
     0x1.935d381a0844fp-58, -0x1.9806d9414a209p-4, -0x1.c81cca3dd9b7bp-58,
     -0x1.a30a9d609efeap-4, 0x1.ebf33e9410429p-59, -0x1.adfd07416be07p-4,
     0x1.448acb08c4bcap-63, -0x1.b8de4d3ab3d98p-4, 0x1.446d00b829ad4p-61,
     -0x1.c3aea4a5c6effp-4, 0x1.8b9190212e5bap-58, -0x1.ce6e41e463da5p-4,
     0x1.6f0603909a181p-61, -0x1.d91d5866aa99cp-4, 0x1.ce84c9eaee37ap-58,
     -0x1.e3bc1ab0e19fep-4, -0x1.eab1529f83ac7p-59, -0x1.ee4aba610f204p-4,
     -0x1.c427300821266p-58, -0x1.f8c9683468191p-4, 0x1.ec7f2dac60a5cp-58,
     -0x1.019c2a064b486p-3, -0x1.c5e9d9a0e1fd9p-57, -0x1.06cbd67a6c3b6p-3,
     -0x1.5163143f60061p-57, -0x1.0bf3d0937c41cp-3, -0x1.e17a06836db63p-58,
     -0x1.11142f0811357p-3, 0x1.b8c4f1b08949bp-59, -0x1.162d082ac9d1p-3,
     0x1.c6397435bc5b6p-57, -0x1.1b3e71ec94f7bp-3, 0x1.1113336d7c017p-57,
     -0x1.204881dee8777p-3, -0x1.54b04da9d7f6dp-57, -0x1.254b4d35e7d3cp-3,
     -0x1.d7958ffee72acp-59, -0x1.2a46e8ca7ba2ap-3, 0x1.aa8c8a1f1c5fbp-57,
     -0x1.2f3b691c5a001p-3, 0x1.072d03df862acp-57, -0x1.3428e2540096dp-3,
     -0x1.db19f0230af8bp-58, 0x1.2f7301cf4e87bp-3, -0x1.c7972ce5f8b57p-59,
     0x1.2a935ba5f1479p-3, -0x1.f613823fd2a19p-62, 0x1.25ba8215af7fcp-3,
     0x1.0349d03e16325p-58, 0x1.20e8624038fedp-3, -0x1.7299601268298p-57,
     0x1.1c1ce9955c0c6p-3, -0x1.db924be9633b4p-58, 0x1.175805d1587c1p-3,
     0x1.ac676f20a87abp-58, 0x1.1299a4fb3e306p-3, -0x1.ce6c847a6598dp-57,
     0x1.0de1b56356b04p-3, 0x1.5b619c844d28bp-57, 0x1.093025a19976cp-3,
     -0x1.a12a1c0cb3d7fp-57, 0x1.0484e4942aa43p-3, 0x1.f318aa302171p-58,
     0x1.ffbfc2bbc7803p-4, 0x1.d60df12c2e13dp-58, 0x1.f68216c9cc727p-4,
     -0x1.c42f76e4345bp-58, 0x1.ed50a4a26eafcp-4, -0x1.0a89525f3e005p-61,
     0x1.e42b4c16caaf3p-4, -0x1.e018e5642e2efp-58, 0x1.db11ed766abf4p-4,
     0x1.96e1e0dda0b3dp-59, 0x1.d204698cb42bdp-4, -0x1.667bf89866ccap-58,
     0x1.c902a19e65111p-4, 0x1.ce424933542a9p-58, 0x1.c00c7767225cbp-4,
     -0x1.b1e2e67b6f4bfp-58, 0x1.b721cd17157e3p-4, -0x1.a8267d18975f3p-58,
     0x1.ae4285509950bp-4, 0x1.5ea40ecd9899p-58, 0x1.a56e8325f5c87p-4,
     -0x1.113a1fc340179p-60, 0x1.9ca5aa1729f45p-4, -0x1.62d3ed69292bp-58,
     0x1.93e7de0fc3e8p-4, -0x1.d0d01941798b6p-58, 0x1.8b350364c6257p-4,
     0x1.da13d5c8cb232p-59, 0x1.828cfed29a215p-4, -0x1.3f06091db645p-58,
     0x1.79efb57b0f803p-4, 0x1.7e469fe31a42fp-58, 0x1.715d0ce367afcp-4,
     -0x1.49840eaa6487bp-58, 0x1.68d4eaf26d7eep-4, 0x1.4c74f6a7880e3p-58,
     0x1.605735ee985f1p-4, -0x1.86e2f4130bd29p-61, 0x1.57e3d47c3af7bp-4,
     -0x1.87decde1893f1p-62, 0x1.4f7aad9bbcbafp-4, -0x1.5d69e39196f27p-59,
     0x1.471ba8a7de2b7p-4, 0x1.ce8e795b6ed98p-61, 0x1.3ec6ad5407868p-4,
     0x1.c4c753d98645ap-58, 0x1.367ba3aaa1883p-4, -0x1.de49ddb15fb04p-58,
     0x1.2e3a740b7800fp-4, -0x1.aef53f2ecddb9p-58, 0x1.2603072a25f82p-4,
     0x1.68307643adbbcp-59, 0x1.1dd5460c8b16fp-4, -0x1.f587e7a233c8p-59,
     0x1.15b11a094a1aap-4, -0x1.6a232c37f20c5p-58, 0x1.0d966cc6500fap-4,
     -0x1.195d4e57a7a13p-58, 0x1.0585283764178p-4, -0x1.e0c43230184dcp-59,
     0x1.fafa6d397efdbp-5, 0x1.62f731cfeb27bp-61, 0x1.eafd05035bd3bp-5,
     0x1.2d38dc40c4fe1p-60, 0x1.db11ed766abf4p-5, 0x1.96e1e0dda0b3dp-60,
     0x1.cb38fccd8bfdbp-5, 0x1.a5aca518d962ep-59, 0x1.bb7209d1e24e5p-5,
     0x1.4af56a02aee6fp-59, 0x1.abbcebd84fcap-5, -0x1.97d2cb982dac2p-60,
     0x1.9c197abf00dd7p-5, -0x1.86148dd4cfbf5p-61, 0x1.8c878eeb05074p-5,
     0x1.38ba93c4a0776p-59, 0x1.7d070145f4fd7p-5, 0x1.2d4e10b03cee8p-59,
     0x1.6d97ab3ba5e1p-5, 0x1.77b340fa390ecp-60, 0x1.5e3966b7e9295p-5,
     0x1.bb9cd2fb75402p-61, 0x1.4eec0e2458f3p-5, -0x1.978c592e6c139p-63,
     0x1.3faf7c663060ep-5, -0x1.9d0e7e0ac0ee2p-59, 0x1.30838cdc2fbfdp-5,
     -0x1.2f7a1b585d96fp-63, 0x1.21681b5c8c213p-5, 0x1.63610c66f42b2p-59,
     0x1.125d0432ea20ep-5, -0x1.f6975f23b8a99p-60, 0x1.0362241e638ecp-5,
     0x1.7db4db93811b8p-59, 0x1.e8eeb09f2f6cbp-6, -0x1.90eef0812d3efp-60,
     0x1.cb38fccd8bfdbp-6, 0x1.a5aca518d962ep-60, 0x1.ada2e8e3e546fp-6,
     0x1.19e6e701995fdp-60, 0x1.902c31d62a843p-6, 0x1.d5af81a520735p-60,
     0x1.72d4956ca2067p-6, -0x1.9fc37c4e4e576p-61, 0x1.559bd2406c3bap-6,
     0x1.521ad5fa98432p-63, 0x1.3881a7b818f9ep-6, 0x1.7b38a223627b5p-60,
     0x1.1b85d6044e9aep-6, -0x1.646ebcccb6894p-66, 0x1.fd503c3904f1dp-7,
     0x1.7d5b73769b64cp-61, 0x1.c3d0837784c41p-7, -0x1.8d01e8ac8a78bp-61,
     0x1.8a8c06bb1d2f4p-7, 0x1.f758cf20ab67dp-65, 0x1.51824c7587ebp-7,
     -0x1.4c944fe8f1a45p-62, 0x1.18b2dc8d2bb91p-7, -0x1.bcae68eaf213fp-63,
     0x1.c03a80ae5e054p-8, -0x1.f4ab82393c268p-62, 0x1.4f8205235102dp-8,
     -0x1.a8fc8e6f1cac2p-62, 0x1.be76bd77b4fc3p-9, 0x1.ad96bce53f818p-66,
     0x1.bd96a1d7d9cbcp-10, 0x1.468f6c475cc38p-65
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

double log10_double_avx2(double);
double log10_double_avx2(double x){
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
    __m128d tmp18;
    double tmp19;
    __m128d tmp20;
    __m128d u;
    double tmp21;
    double tmp22;
    double tmp23;
    double tmp24;
    double tmp25;
    __m128d tmp26;
    __m128d tmp27;
    double tmp28;
    double tmp29;
    double tmp30;
    double tmp31;
    double tmp32;
    double tmp33;
    double tmp34;
    double tmp35;
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
    __m128d tmp48;
    __m128d tmp49;
    __m128d tmp50;
    double tmp51;
    double tmp52;
    double tmp53;
    double tmp54;
    double tmp55;
    double tmp56;
    double tmp57;
    double tmp58;
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
    __m128d tmp71;
    __m128d tmp72;
    __m128d tmp73;
    double tmp74;
    double tmp75;
    double tmp76;
    double tmp77;
    double tmp78;
    double tmp79;
    double tmp80;
    double tmp81;
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
    __m128d tmp94;
    __m128d tmp95;
    __m128d tmp96;
    double tmp97;
    double tmp98;
    double tmp99;
    double tmp100;
    double tmp101;
    double tmp102;
    double tmp103;
    double tmp104;
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
    __m128d tmp117;
    __m128d tmp118;
    __m128d tmp119;
    double tmp120;
    double tmp121;
    double tmp122;
    double tmp123;
    double tmp124;
    double tmp125;
    double tmp126;
    double tmp127;
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
    __m128d tmp140;
    __m128d tmp141;
    __m128d tmp142;
    double tmp143;
    double tmp144;
    double tmp145;
    double tmp146;
    double tmp147;
    double tmp148;
    double tmp149;
    double tmp150;
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
    __m128d tmp163;
    __m128d tmp164;
    __m128d tmp165;
    double tmp166;
    double tmp167;
    double tmp168;
    double tmp169;
    double tmp170;
    double tmp171;
    double tmp172;
    double tmp173;
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
    __m128d tmp186;
    __m128d tmp187;
    __m128d tmp188;
    double tmp189;
    double tmp190;
    double tmp191;
    double tmp192;
    double tmp193;
    double tmp194;
    double tmp195;
    double tmp196;
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
    __m128d tmp209;
    __m128d tmp210;
    __m128d tmp211;
    double tmp212;
    double tmp213;
    double tmp214;
    double tmp215;
    double tmp216;
    double tmp217;
    double tmp218;
    double tmp219;
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
    __m128d tmp232;
    __m128d tmp233;
    __m128d tmp234;
    double tmp235;
    double tmp236;
    double tmp237;
    double tmp238;
    double tmp239;
    double tmp240;
    double tmp241;
    double tmp242;
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
    __m128d tmp255;
    __m128d tmp256;
    __m128d tmp257;
    double tmp258;
    double tmp259;
    double log1pu_poly_hi;
    int32_t tmp260;
    int tmp261;
    int32_t tmp262;
    int32_t tmp263;
    int32_t tmp264;
    uint64_t exponent_srl_cast;
    int64_t tmp265;
    int64_t tmp266;
    int64_t tmp_eptau;
    int64_t tmp267;
    double fp_exponent;
    double tmp268;
    double tmp269;
    double tmp270;
    double tmp271;
    __m128d tmp272;
    __m128d tmp273;
    __m128d tmp274;
    double tmp275;
    double tmp276;
    double tmp277;
    double tmp278;
    double tmp279;
    double tmp280;
    double tmp281;
    double tmp282;
    double tmp283;
    double tmp284;
    double log1pu_poly_lo;
    double tmp285;
    double tmp286;
    double tmp287;
    double tmp288;
    double tmp289;
    double tmp290;
    double tmp291;
    double tmp292;
    double tmp293;
    double tmp294;
    double tmp295;
    uint32_t table_index_lo;
    double tbl_lo;
    double tmp296;
    double tmp297;
    double tmp298;
    double tmp299;
    double logx_hi;
    
    vx_as_int = double_to_64b_encoding(x);
    tmp = vx_as_int - INT64_C(1);
    tmp1 = tmp < INT64_C(4503599627370495);
    is_subnormal = tmp1 ? INT64_C(-1) : INT64_C(0);
    tmp2 = _mm_cvtsd_f64(log10_double_avx2_fp_one);
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
    tmp18 = _mm_set_sd(tmp8);
    tmp19 = double_from_64b_encoding(ri_fast_rndn);
    tmp20 = _mm_set_sd(tmp19);
    u = _mm_fmsub_sd(tmp18, tmp20, log10_double_avx2_fp_one);
    tmp21 = _mm_cvtsd_f64(u);
    tmp22 = _mm_cvtsd_f64(log10_double_avx2_c_11hi);
    tmp23 = tmp21 * tmp22;
    tmp24 = _mm_cvtsd_f64(log10_double_avx2_c_11lo);
    tmp25 = tmp21 * tmp24;
    tmp26 = _mm_set_sd(tmp23);
    tmp27 = _mm_fmsub_sd(u, log10_double_avx2_c_11hi, tmp26);
    tmp28 = _mm_cvtsd_f64(tmp27);
    tmp29 = tmp28 + tmp25;
    tmp30 = tmp23 + tmp29;
    tmp31 = _mm_cvtsd_f64(log10_double_avx2_c_10hi);
    tmp32 = tmp31 + tmp30;
    tmp33 = tmp32 - tmp30;
    tmp34 = tmp31 - tmp33;
    tmp35 = tmp32 - tmp33;
    tmp36 = tmp30 - tmp35;
    tmp37 = tmp34 + tmp36;
    tmp38 = tmp30 - tmp23;
    tmp39 = tmp29 - tmp38;
    tmp40 = _mm_cvtsd_f64(log10_double_avx2_c_10lo);
    tmp41 = tmp40 + tmp39;
    tmp42 = tmp37 + tmp41;
    tmp43 = tmp32 + tmp42;
    tmp44 = tmp21 * tmp43;
    tmp45 = tmp43 - tmp32;
    tmp46 = tmp42 - tmp45;
    tmp47 = tmp21 * tmp46;
    tmp48 = _mm_set_sd(tmp43);
    tmp49 = _mm_set_sd(tmp44);
    tmp50 = _mm_fmsub_sd(u, tmp48, tmp49);
    tmp51 = _mm_cvtsd_f64(tmp50);
    tmp52 = tmp51 + tmp47;
    tmp53 = tmp44 + tmp52;
    tmp54 = _mm_cvtsd_f64(log10_double_avx2_c_9hi);
    tmp55 = tmp54 + tmp53;
    tmp56 = tmp55 - tmp53;
    tmp57 = tmp54 - tmp56;
    tmp58 = tmp55 - tmp56;
    tmp59 = tmp53 - tmp58;
    tmp60 = tmp57 + tmp59;
    tmp61 = tmp53 - tmp44;
    tmp62 = tmp52 - tmp61;
    tmp63 = _mm_cvtsd_f64(log10_double_avx2_c_9lo);
    tmp64 = tmp63 + tmp62;
    tmp65 = tmp60 + tmp64;
    tmp66 = tmp55 + tmp65;
    tmp67 = tmp21 * tmp66;
    tmp68 = tmp66 - tmp55;
    tmp69 = tmp65 - tmp68;
    tmp70 = tmp21 * tmp69;
    tmp71 = _mm_set_sd(tmp66);
    tmp72 = _mm_set_sd(tmp67);
    tmp73 = _mm_fmsub_sd(u, tmp71, tmp72);
    tmp74 = _mm_cvtsd_f64(tmp73);
    tmp75 = tmp74 + tmp70;
    tmp76 = tmp67 + tmp75;
    tmp77 = _mm_cvtsd_f64(log10_double_avx2_c_8hi);
    tmp78 = tmp77 + tmp76;
    tmp79 = tmp78 - tmp76;
    tmp80 = tmp77 - tmp79;
    tmp81 = tmp78 - tmp79;
    tmp82 = tmp76 - tmp81;
    tmp83 = tmp80 + tmp82;
    tmp84 = tmp76 - tmp67;
    tmp85 = tmp75 - tmp84;
    tmp86 = _mm_cvtsd_f64(log10_double_avx2_c_8lo);
    tmp87 = tmp86 + tmp85;
    tmp88 = tmp83 + tmp87;
    tmp89 = tmp78 + tmp88;
    tmp90 = tmp21 * tmp89;
    tmp91 = tmp89 - tmp78;
    tmp92 = tmp88 - tmp91;
    tmp93 = tmp21 * tmp92;
    tmp94 = _mm_set_sd(tmp89);
    tmp95 = _mm_set_sd(tmp90);
    tmp96 = _mm_fmsub_sd(u, tmp94, tmp95);
    tmp97 = _mm_cvtsd_f64(tmp96);
    tmp98 = tmp97 + tmp93;
    tmp99 = tmp90 + tmp98;
    tmp100 = _mm_cvtsd_f64(log10_double_avx2_c_7hi);
    tmp101 = tmp100 + tmp99;
    tmp102 = tmp101 - tmp99;
    tmp103 = tmp100 - tmp102;
    tmp104 = tmp101 - tmp102;
    tmp105 = tmp99 - tmp104;
    tmp106 = tmp103 + tmp105;
    tmp107 = tmp99 - tmp90;
    tmp108 = tmp98 - tmp107;
    tmp109 = _mm_cvtsd_f64(log10_double_avx2_c_7lo);
    tmp110 = tmp109 + tmp108;
    tmp111 = tmp106 + tmp110;
    tmp112 = tmp101 + tmp111;
    tmp113 = tmp21 * tmp112;
    tmp114 = tmp112 - tmp101;
    tmp115 = tmp111 - tmp114;
    tmp116 = tmp21 * tmp115;
    tmp117 = _mm_set_sd(tmp112);
    tmp118 = _mm_set_sd(tmp113);
    tmp119 = _mm_fmsub_sd(u, tmp117, tmp118);
    tmp120 = _mm_cvtsd_f64(tmp119);
    tmp121 = tmp120 + tmp116;
    tmp122 = tmp113 + tmp121;
    tmp123 = _mm_cvtsd_f64(log10_double_avx2_c_6hi);
    tmp124 = tmp123 + tmp122;
    tmp125 = tmp124 - tmp122;
    tmp126 = tmp123 - tmp125;
    tmp127 = tmp124 - tmp125;
    tmp128 = tmp122 - tmp127;
    tmp129 = tmp126 + tmp128;
    tmp130 = tmp122 - tmp113;
    tmp131 = tmp121 - tmp130;
    tmp132 = _mm_cvtsd_f64(log10_double_avx2_c_6lo);
    tmp133 = tmp132 + tmp131;
    tmp134 = tmp129 + tmp133;
    tmp135 = tmp124 + tmp134;
    tmp136 = tmp21 * tmp135;
    tmp137 = tmp135 - tmp124;
    tmp138 = tmp134 - tmp137;
    tmp139 = tmp21 * tmp138;
    tmp140 = _mm_set_sd(tmp135);
    tmp141 = _mm_set_sd(tmp136);
    tmp142 = _mm_fmsub_sd(u, tmp140, tmp141);
    tmp143 = _mm_cvtsd_f64(tmp142);
    tmp144 = tmp143 + tmp139;
    tmp145 = tmp136 + tmp144;
    tmp146 = _mm_cvtsd_f64(log10_double_avx2_c_5hi);
    tmp147 = tmp146 + tmp145;
    tmp148 = tmp147 - tmp145;
    tmp149 = tmp146 - tmp148;
    tmp150 = tmp147 - tmp148;
    tmp151 = tmp145 - tmp150;
    tmp152 = tmp149 + tmp151;
    tmp153 = tmp145 - tmp136;
    tmp154 = tmp144 - tmp153;
    tmp155 = _mm_cvtsd_f64(log10_double_avx2_c_5lo);
    tmp156 = tmp155 + tmp154;
    tmp157 = tmp152 + tmp156;
    tmp158 = tmp147 + tmp157;
    tmp159 = tmp21 * tmp158;
    tmp160 = tmp158 - tmp147;
    tmp161 = tmp157 - tmp160;
    tmp162 = tmp21 * tmp161;
    tmp163 = _mm_set_sd(tmp158);
    tmp164 = _mm_set_sd(tmp159);
    tmp165 = _mm_fmsub_sd(u, tmp163, tmp164);
    tmp166 = _mm_cvtsd_f64(tmp165);
    tmp167 = tmp166 + tmp162;
    tmp168 = tmp159 + tmp167;
    tmp169 = _mm_cvtsd_f64(log10_double_avx2_c_4hi);
    tmp170 = tmp169 + tmp168;
    tmp171 = tmp170 - tmp168;
    tmp172 = tmp169 - tmp171;
    tmp173 = tmp170 - tmp171;
    tmp174 = tmp168 - tmp173;
    tmp175 = tmp172 + tmp174;
    tmp176 = tmp168 - tmp159;
    tmp177 = tmp167 - tmp176;
    tmp178 = _mm_cvtsd_f64(log10_double_avx2_c_4lo);
    tmp179 = tmp178 + tmp177;
    tmp180 = tmp175 + tmp179;
    tmp181 = tmp170 + tmp180;
    tmp182 = tmp21 * tmp181;
    tmp183 = tmp181 - tmp170;
    tmp184 = tmp180 - tmp183;
    tmp185 = tmp21 * tmp184;
    tmp186 = _mm_set_sd(tmp181);
    tmp187 = _mm_set_sd(tmp182);
    tmp188 = _mm_fmsub_sd(u, tmp186, tmp187);
    tmp189 = _mm_cvtsd_f64(tmp188);
    tmp190 = tmp189 + tmp185;
    tmp191 = tmp182 + tmp190;
    tmp192 = _mm_cvtsd_f64(log10_double_avx2_c_3hi);
    tmp193 = tmp192 + tmp191;
    tmp194 = tmp193 - tmp191;
    tmp195 = tmp192 - tmp194;
    tmp196 = tmp193 - tmp194;
    tmp197 = tmp191 - tmp196;
    tmp198 = tmp195 + tmp197;
    tmp199 = tmp191 - tmp182;
    tmp200 = tmp190 - tmp199;
    tmp201 = _mm_cvtsd_f64(log10_double_avx2_c_3lo);
    tmp202 = tmp201 + tmp200;
    tmp203 = tmp198 + tmp202;
    tmp204 = tmp193 + tmp203;
    tmp205 = tmp21 * tmp204;
    tmp206 = tmp204 - tmp193;
    tmp207 = tmp203 - tmp206;
    tmp208 = tmp21 * tmp207;
    tmp209 = _mm_set_sd(tmp204);
    tmp210 = _mm_set_sd(tmp205);
    tmp211 = _mm_fmsub_sd(u, tmp209, tmp210);
    tmp212 = _mm_cvtsd_f64(tmp211);
    tmp213 = tmp212 + tmp208;
    tmp214 = tmp205 + tmp213;
    tmp215 = _mm_cvtsd_f64(log10_double_avx2_c_2hi);
    tmp216 = tmp215 + tmp214;
    tmp217 = tmp216 - tmp214;
    tmp218 = tmp215 - tmp217;
    tmp219 = tmp216 - tmp217;
    tmp220 = tmp214 - tmp219;
    tmp221 = tmp218 + tmp220;
    tmp222 = tmp214 - tmp205;
    tmp223 = tmp213 - tmp222;
    tmp224 = _mm_cvtsd_f64(log10_double_avx2_c_2lo);
    tmp225 = tmp224 + tmp223;
    tmp226 = tmp221 + tmp225;
    tmp227 = tmp216 + tmp226;
    tmp228 = tmp21 * tmp227;
    tmp229 = tmp227 - tmp216;
    tmp230 = tmp226 - tmp229;
    tmp231 = tmp21 * tmp230;
    tmp232 = _mm_set_sd(tmp227);
    tmp233 = _mm_set_sd(tmp228);
    tmp234 = _mm_fmsub_sd(u, tmp232, tmp233);
    tmp235 = _mm_cvtsd_f64(tmp234);
    tmp236 = tmp235 + tmp231;
    tmp237 = tmp228 + tmp236;
    tmp238 = _mm_cvtsd_f64(log10_double_avx2_c_1hi);
    tmp239 = tmp238 + tmp237;
    tmp240 = tmp239 - tmp237;
    tmp241 = tmp238 - tmp240;
    tmp242 = tmp239 - tmp240;
    tmp243 = tmp237 - tmp242;
    tmp244 = tmp241 + tmp243;
    tmp245 = tmp237 - tmp228;
    tmp246 = tmp236 - tmp245;
    tmp247 = _mm_cvtsd_f64(log10_double_avx2_c_1lo);
    tmp248 = tmp247 + tmp246;
    tmp249 = tmp244 + tmp248;
    tmp250 = tmp239 + tmp249;
    tmp251 = tmp21 * tmp250;
    tmp252 = tmp250 - tmp239;
    tmp253 = tmp249 - tmp252;
    tmp254 = tmp21 * tmp253;
    tmp255 = _mm_set_sd(tmp250);
    tmp256 = _mm_set_sd(tmp251);
    tmp257 = _mm_fmsub_sd(u, tmp255, tmp256);
    tmp258 = _mm_cvtsd_f64(tmp257);
    tmp259 = tmp258 + tmp254;
    log1pu_poly_hi = tmp251 + tmp259;
    tmp260 = _mm_cvtsi128_si32(log10_double_avx2_cst);
    tmp261 = ( (int32_t) table_index) > tmp260;
    tmp262 = _mm_cvtsi128_si32(log10_double_avx2_cst1);
    tmp263 = _mm_cvtsi128_si32(log10_double_avx2_cst2);
    tmp264 = tmp261 ? tmp262 : tmp263;
    exponent_srl_cast = tmp7;
    tmp265 = exponent_srl_cast >> INT64_C(52);
    tmp266 = tmp265 + INT64_C(-1023);
    tmp_eptau = tmp266 + ( (int64_t) tmp264);
    tmp267 = tmp_eptau - alpha;
    fp_exponent = tmp267;
    tmp268 = _mm_cvtsd_f64(log10_double_avx2_log2_hi);
    tmp269 = fp_exponent * tmp268;
    tmp270 = _mm_cvtsd_f64(log10_double_avx2_log2_lo);
    tmp271 = fp_exponent * tmp270;
    tmp272 = _mm_set_sd(fp_exponent);
    tmp273 = _mm_set_sd(tmp269);
    tmp274 = _mm_fmsub_sd(tmp272, log10_double_avx2_log2_hi, tmp273);
    tmp275 = _mm_cvtsd_f64(tmp274);
    tmp276 = tmp275 + tmp271;
    tmp277 = tmp269 + tmp276;
    tmp278 = tmp277 + log1pu_poly_hi;
    tmp279 = tmp278 - log1pu_poly_hi;
    tmp280 = tmp277 - tmp279;
    tmp281 = tmp278 - tmp279;
    tmp282 = log1pu_poly_hi - tmp281;
    tmp283 = tmp280 + tmp282;
    tmp284 = log1pu_poly_hi - tmp251;
    log1pu_poly_lo = tmp259 - tmp284;
    tmp285 = tmp277 - tmp269;
    tmp286 = tmp276 - tmp285;
    tmp287 = tmp286 + log1pu_poly_lo;
    tmp288 = tmp283 + tmp287;
    tmp289 = tmp278 + tmp288;
    tmp290 = tmp289 + tbl_hi;
    tmp291 = tmp290 - tbl_hi;
    tmp292 = tmp289 - tmp291;
    tmp293 = tmp290 - tmp291;
    tmp294 = tbl_hi - tmp293;
    tmp295 = tmp292 + tmp294;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp296 = tmp289 - tmp278;
    tmp297 = tmp288 - tmp296;
    tmp298 = tmp297 + tbl_lo;
    tmp299 = tmp295 + tmp298;
    logx_hi = tmp290 + tmp299;
    return logx_hi;
}
