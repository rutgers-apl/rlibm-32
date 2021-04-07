/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix 10 --language c \
 *     --accuracy cr --precision double --target x86 --output \
 *     GeneratedFunctions/cr/x86/log10_double_x86.c --fname log10_double_x86
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <math.h>


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

double log10_double_x86(double);
double log10_double_x86(double x){
    int64_t vx_as_int;
    int64_t tmp;
    int tmp1;
    int64_t is_subnormal;
    uint64_t fp_one_as_uint;
    uint64_t vx_as_uint;
    uint64_t Zi;
    double tmp2;
    double Zf;
    int64_t tmp3;
    uint64_t _srl_cast;
    int64_t tmp4;
    int64_t tmp5;
    int64_t n_value;
    int64_t alpha;
    int64_t tmp6;
    double normal_vx;
    double tmp7;
    float id_tmp;
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
    double id_tmp1;
    int64_t tmp14;
    int64_t tmp15;
    uint64_t id_tmp2;
    uint64_t ri_fast_rndn;
    uint64_t ri_bits;
    uint32_t table_index;
    uint32_t tmp16;
    uint32_t table_index_hi;
    double tbl_hi;
    double tmp17;
    double carg;
    double u;
    double tmp18;
    double carg1;
    double tmp19;
    double tmp20;
    double tmp21;
    double tmp22;
    double tmp23;
    double tmp24;
    double tmp25;
    double tmp26;
    double tmp27;
    double tmp28;
    double tmp29;
    double tmp30;
    double tmp31;
    double tmp32;
    double tmp33;
    double tmp34;
    double carg2;
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
    double tmp48;
    double tmp49;
    double tmp50;
    double tmp51;
    double tmp52;
    double carg3;
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
    double carg4;
    double tmp71;
    double tmp72;
    double tmp73;
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
    double carg5;
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
    double tmp102;
    double tmp103;
    double tmp104;
    double tmp105;
    double tmp106;
    double carg6;
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
    double carg7;
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
    double tmp140;
    double tmp141;
    double tmp142;
    double carg8;
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
    double carg9;
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
    double tmp171;
    double tmp172;
    double tmp173;
    double tmp174;
    double tmp175;
    double tmp176;
    double tmp177;
    double tmp178;
    double carg10;
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
    double tmp194;
    double tmp195;
    double tmp196;
    double carg11;
    double tmp197;
    double tmp198;
    double tmp199;
    double tmp200;
    double tmp201;
    double log1pu_poly_hi;
    int tmp202;
    int32_t tmp203;
    uint64_t exponent_srl_cast;
    int64_t tmp204;
    int64_t tmp205;
    int64_t tmp_eptau;
    int64_t tmp206;
    double fp_exponent;
    double tmp207;
    double carg12;
    double tmp208;
    double tmp209;
    double tmp210;
    double tmp211;
    double tmp212;
    double tmp213;
    double tmp214;
    double tmp215;
    double tmp216;
    double tmp217;
    double tmp218;
    double log1pu_poly_lo;
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
    uint32_t table_index_lo;
    double tbl_lo;
    double tmp230;
    double tmp231;
    double tmp232;
    double tmp233;
    double logx_hi;
    
    vx_as_int = double_to_64b_encoding(x);
    tmp = vx_as_int - INT64_C(1);
    tmp1 = tmp < INT64_C(4503599627370495);
    is_subnormal = tmp1 ? INT64_C(-1) : INT64_C(0);
    fp_one_as_uint = double_to_64b_encoding(1.0);
    vx_as_uint = double_to_64b_encoding(x);
    Zi = vx_as_uint | fp_one_as_uint;
    tmp2 = double_from_64b_encoding(Zi);
    Zf = tmp2 - 1.0;
    tmp3 = double_to_64b_encoding(Zf);
    _srl_cast = tmp3;
    tmp4 = _srl_cast >> INT64_C(52);
    tmp5 = tmp4 + INT64_C(-1023);
    n_value = tmp5 & is_subnormal;
    alpha =  - n_value;
    tmp6 = vx_as_int << alpha;
    normal_vx = double_from_64b_encoding(tmp6);
    tmp7 = ml_mantissa_extraction_fp64(normal_vx);
    id_tmp = tmp7;
    tmp8 = float_to_32b_encoding(id_tmp);
    _srl_cast1 = tmp8;
    tmp9 = _srl_cast1 >> INT32_C(16);
    inv_index = tmp9 & INT32_C(127);
    tmp10 = table[inv_index];
    tmp11 = copysignf(1.0f, id_tmp);
    op_exp = ml_exp_extraction_dirty_fp32(id_tmp);
    tmp12 =  - op_exp;
    approx_exp = ml_exp_insertion_fp32(tmp12);
    tmp13 = approx_exp * tmp11;
    inv_approx = tmp10 * tmp13;
    id_tmp1 = inv_approx;
    tmp14 = double_to_64b_encoding(id_tmp1);
    tmp15 = tmp14 + INT64_C(17592186044416);
    id_tmp2 = tmp15;
    ri_fast_rndn = id_tmp2 & UINT64_C(-35184372088832);
    ri_bits = ri_fast_rndn >> UINT64_C(45);
    table_index = ( (uint32_t) ri_bits) & UINT32_C(255);
    tmp16 = table_index & UINT32_C(127);
    table_index_hi = tmp16 << UINT32_C(1);
    tbl_hi = ml_log1p_table[table_index_hi];
    tmp17 = double_from_64b_encoding(ri_fast_rndn);
    carg =  - 1.0;
    u = fma(tmp7, tmp17, carg);
    tmp18 = u * 0x1.43721e678c758p-5;
    carg1 =  - tmp18;
    tmp19 = fma(u, 0x1.43721e678c758p-5, carg1);
    tmp20 = u * 0x1.4b1fac2c45c7ep-60;
    tmp21 = tmp19 + tmp20;
    tmp22 = tmp18 + tmp21;
    tmp23 = -0x1.63c9ad226aaccp-5 + tmp22;
    tmp24 = tmp23 - tmp22;
    tmp25 = -0x1.63c9ad226aaccp-5 - tmp24;
    tmp26 = tmp23 - tmp24;
    tmp27 = tmp22 - tmp26;
    tmp28 = tmp25 + tmp27;
    tmp29 = tmp22 - tmp18;
    tmp30 = tmp21 - tmp29;
    tmp31 = -0x1.12b117351a3a2p-60 + tmp30;
    tmp32 = tmp28 + tmp31;
    tmp33 = tmp23 + tmp32;
    tmp34 = u * tmp33;
    carg2 =  - tmp34;
    tmp35 = fma(u, tmp33, carg2);
    tmp36 = tmp33 - tmp23;
    tmp37 = tmp32 - tmp36;
    tmp38 = u * tmp37;
    tmp39 = tmp35 + tmp38;
    tmp40 = tmp34 + tmp39;
    tmp41 = 0x1.8b4df2eebcfb3p-5 + tmp40;
    tmp42 = tmp41 - tmp40;
    tmp43 = 0x1.8b4df2eebcfb3p-5 - tmp42;
    tmp44 = tmp41 - tmp42;
    tmp45 = tmp40 - tmp44;
    tmp46 = tmp43 + tmp45;
    tmp47 = tmp40 - tmp34;
    tmp48 = tmp39 - tmp47;
    tmp49 = -0x1.0d5229ad41226p-59 + tmp48;
    tmp50 = tmp46 + tmp49;
    tmp51 = tmp41 + tmp50;
    tmp52 = u * tmp51;
    carg3 =  - tmp52;
    tmp53 = fma(u, tmp51, carg3);
    tmp54 = tmp51 - tmp41;
    tmp55 = tmp50 - tmp54;
    tmp56 = u * tmp55;
    tmp57 = tmp53 + tmp56;
    tmp58 = tmp52 + tmp57;
    tmp59 = -0x1.bcb7b14e72305p-5 + tmp58;
    tmp60 = tmp59 - tmp58;
    tmp61 = -0x1.bcb7b14e72305p-5 - tmp60;
    tmp62 = tmp59 - tmp60;
    tmp63 = tmp58 - tmp62;
    tmp64 = tmp61 + tmp63;
    tmp65 = tmp58 - tmp52;
    tmp66 = tmp57 - tmp65;
    tmp67 = 0x1.81941204622acp-60 + tmp66;
    tmp68 = tmp64 + tmp67;
    tmp69 = tmp59 + tmp68;
    tmp70 = u * tmp69;
    carg4 =  - tmp70;
    tmp71 = fma(u, tmp69, carg4);
    tmp72 = tmp69 - tmp59;
    tmp73 = tmp68 - tmp72;
    tmp74 = u * tmp73;
    tmp75 = tmp71 + tmp74;
    tmp76 = tmp70 + tmp75;
    tmp77 = 0x1.fc3fa615105fep-5 + tmp76;
    tmp78 = tmp77 - tmp76;
    tmp79 = 0x1.fc3fa615105fep-5 - tmp78;
    tmp80 = tmp77 - tmp78;
    tmp81 = tmp76 - tmp80;
    tmp82 = tmp79 + tmp81;
    tmp83 = tmp76 - tmp70;
    tmp84 = tmp75 - tmp83;
    tmp85 = -0x1.6ca0627978a4ap-60 + tmp84;
    tmp86 = tmp82 + tmp85;
    tmp87 = tmp77 + tmp86;
    tmp88 = u * tmp87;
    carg5 =  - tmp88;
    tmp89 = fma(u, tmp87, carg5);
    tmp90 = tmp87 - tmp77;
    tmp91 = tmp86 - tmp90;
    tmp92 = u * tmp91;
    tmp93 = tmp89 + tmp92;
    tmp94 = tmp88 + tmp93;
    tmp95 = -0x1.287a7636f436fp-4 + tmp94;
    tmp96 = tmp95 - tmp94;
    tmp97 = -0x1.287a7636f436fp-4 - tmp96;
    tmp98 = tmp95 - tmp96;
    tmp99 = tmp94 - tmp98;
    tmp100 = tmp97 + tmp99;
    tmp101 = tmp94 - tmp88;
    tmp102 = tmp93 - tmp101;
    tmp103 = -0x1.5d4fda08566ccp-59 + tmp102;
    tmp104 = tmp100 + tmp103;
    tmp105 = tmp95 + tmp104;
    tmp106 = u * tmp105;
    carg6 =  - tmp106;
    tmp107 = fma(u, tmp105, carg6);
    tmp108 = tmp105 - tmp95;
    tmp109 = tmp104 - tmp108;
    tmp110 = u * tmp109;
    tmp111 = tmp107 + tmp110;
    tmp112 = tmp106 + tmp111;
    tmp113 = 0x1.63c62775250d8p-4 + tmp112;
    tmp114 = tmp113 - tmp112;
    tmp115 = 0x1.63c62775250d8p-4 - tmp114;
    tmp116 = tmp113 - tmp114;
    tmp117 = tmp112 - tmp116;
    tmp118 = tmp115 + tmp117;
    tmp119 = tmp112 - tmp106;
    tmp120 = tmp111 - tmp119;
    tmp121 = 0x1.43e50af6205a6p-59 + tmp120;
    tmp122 = tmp118 + tmp121;
    tmp123 = tmp113 + tmp122;
    tmp124 = u * tmp123;
    carg7 =  - tmp124;
    tmp125 = fma(u, tmp123, carg7);
    tmp126 = tmp123 - tmp113;
    tmp127 = tmp122 - tmp126;
    tmp128 = u * tmp127;
    tmp129 = tmp125 + tmp128;
    tmp130 = tmp124 + tmp129;
    tmp131 = -0x1.bcb7b1526e50ep-4 + tmp130;
    tmp132 = tmp131 - tmp130;
    tmp133 = -0x1.bcb7b1526e50ep-4 - tmp132;
    tmp134 = tmp131 - tmp132;
    tmp135 = tmp130 - tmp134;
    tmp136 = tmp133 + tmp135;
    tmp137 = tmp130 - tmp124;
    tmp138 = tmp129 - tmp137;
    tmp139 = -0x1.951800bd0e9e8p-59 + tmp138;
    tmp140 = tmp136 + tmp139;
    tmp141 = tmp131 + tmp140;
    tmp142 = u * tmp141;
    carg8 =  - tmp142;
    tmp143 = fma(u, tmp141, carg8);
    tmp144 = tmp141 - tmp131;
    tmp145 = tmp140 - tmp144;
    tmp146 = u * tmp145;
    tmp147 = tmp143 + tmp146;
    tmp148 = tmp142 + tmp147;
    tmp149 = 0x1.287a7636f435fp-3 + tmp148;
    tmp150 = tmp149 - tmp148;
    tmp151 = 0x1.287a7636f435fp-3 - tmp150;
    tmp152 = tmp149 - tmp150;
    tmp153 = tmp148 - tmp152;
    tmp154 = tmp151 + tmp153;
    tmp155 = tmp148 - tmp142;
    tmp156 = tmp147 - tmp155;
    tmp157 = -0x1.9c8718343fd18p-58 + tmp156;
    tmp158 = tmp154 + tmp157;
    tmp159 = tmp149 + tmp158;
    tmp160 = u * tmp159;
    carg9 =  - tmp160;
    tmp161 = fma(u, tmp159, carg9);
    tmp162 = tmp159 - tmp149;
    tmp163 = tmp158 - tmp162;
    tmp164 = u * tmp163;
    tmp165 = tmp161 + tmp164;
    tmp166 = tmp160 + tmp165;
    tmp167 = -0x1.bcb7b1526e50ep-3 + tmp166;
    tmp168 = tmp167 - tmp166;
    tmp169 = -0x1.bcb7b1526e50ep-3 - tmp168;
    tmp170 = tmp167 - tmp168;
    tmp171 = tmp166 - tmp170;
    tmp172 = tmp169 + tmp171;
    tmp173 = tmp166 - tmp160;
    tmp174 = tmp165 - tmp173;
    tmp175 = -0x1.95355babc1284p-58 + tmp174;
    tmp176 = tmp172 + tmp175;
    tmp177 = tmp167 + tmp176;
    tmp178 = u * tmp177;
    carg10 =  - tmp178;
    tmp179 = fma(u, tmp177, carg10);
    tmp180 = tmp177 - tmp167;
    tmp181 = tmp176 - tmp180;
    tmp182 = u * tmp181;
    tmp183 = tmp179 + tmp182;
    tmp184 = tmp178 + tmp183;
    tmp185 = 0x1.bcb7b1526e50ep-2 + tmp184;
    tmp186 = tmp185 - tmp184;
    tmp187 = 0x1.bcb7b1526e50ep-2 - tmp186;
    tmp188 = tmp185 - tmp186;
    tmp189 = tmp184 - tmp188;
    tmp190 = tmp187 + tmp189;
    tmp191 = tmp184 - tmp178;
    tmp192 = tmp183 - tmp191;
    tmp193 = 0x1.95355baaafad2p-57 + tmp192;
    tmp194 = tmp190 + tmp193;
    tmp195 = tmp185 + tmp194;
    tmp196 = u * tmp195;
    carg11 =  - tmp196;
    tmp197 = fma(u, tmp195, carg11);
    tmp198 = tmp195 - tmp185;
    tmp199 = tmp194 - tmp198;
    tmp200 = u * tmp199;
    tmp201 = tmp197 + tmp200;
    log1pu_poly_hi = tmp196 + tmp201;
    tmp202 = ( (int32_t) table_index) > INT32_C(53);
    tmp203 = tmp202 ? INT32_C(-1) : INT32_C(0);
    exponent_srl_cast = tmp6;
    tmp204 = exponent_srl_cast >> INT64_C(52);
    tmp205 = tmp204 + INT64_C(-1023);
    tmp_eptau = tmp205 + ( (int64_t) tmp203);
    tmp206 = tmp_eptau - alpha;
    fp_exponent = tmp206;
    tmp207 = fp_exponent * 0x1.34413509f79ffp-2;
    carg12 =  - tmp207;
    tmp208 = fma(fp_exponent, 0x1.34413509f79ffp-2, carg12);
    tmp209 = fp_exponent * -0x1.9dc1da994fd21p-59;
    tmp210 = tmp208 + tmp209;
    tmp211 = tmp207 + tmp210;
    tmp212 = tmp211 + log1pu_poly_hi;
    tmp213 = tmp212 - log1pu_poly_hi;
    tmp214 = tmp211 - tmp213;
    tmp215 = tmp212 - tmp213;
    tmp216 = log1pu_poly_hi - tmp215;
    tmp217 = tmp214 + tmp216;
    tmp218 = log1pu_poly_hi - tmp196;
    log1pu_poly_lo = tmp201 - tmp218;
    tmp219 = tmp211 - tmp207;
    tmp220 = tmp210 - tmp219;
    tmp221 = tmp220 + log1pu_poly_lo;
    tmp222 = tmp217 + tmp221;
    tmp223 = tmp212 + tmp222;
    tmp224 = tmp223 + tbl_hi;
    tmp225 = tmp224 - tbl_hi;
    tmp226 = tmp223 - tmp225;
    tmp227 = tmp224 - tmp225;
    tmp228 = tbl_hi - tmp227;
    tmp229 = tmp226 + tmp228;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp230 = tmp223 - tmp212;
    tmp231 = tmp222 - tmp230;
    tmp232 = tmp231 + tbl_lo;
    tmp233 = tmp229 + tmp232;
    logx_hi = tmp224 + tmp233;
    return logx_hi;
}
