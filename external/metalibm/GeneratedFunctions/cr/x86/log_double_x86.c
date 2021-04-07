/**
 * generated using metalibm 1.1
 * sha1 git: b'"44931432e12dbbda32ae5520e55557ff367a96bb"'(clean)
 * 
 * INFO: git status was clean when file was generated.
 * 
 * command used for generation:
 *   metalibm_functions/ml_vectorizable_log.py --log-radix e --language c \
 *     --accuracy cr --precision double --target x86 --output \
 *     GeneratedFunctions/cr/x86/log_double_x86.c --fname log_double_x86
 * 
**/
#include <stdint.h>
#include <ml_support_lib.h>
#include <math.h>


static const double ml_log1p_table[256]  = {
     0.0, 0.0, -0x1.fe02a6b106789p-8, 0x1.e44b7e3711ebfp-67, -0x1.fc0a8b0fc03e4p-7,
     0x1.83092c59642a1p-62, -0x1.7b91b07d5b11bp-6, 0x1.5b602ace3a51p-60,
     -0x1.f829b0e7833p-6, -0x1.33e3f04f1ef23p-60, -0x1.39e87b9febd6p-5,
     0x1.5bfa937f551bbp-59, -0x1.77458f632dcfcp-5, -0x1.18d3ca87b9296p-59,
     -0x1.b42dd711971bfp-5, 0x1.eb9759c130499p-60, -0x1.f0a30c01162a6p-5,
     -0x1.85f325c5bbacdp-59, -0x1.16536eea37ae1p-4, 0x1.79da3e8c22cdap-60,
     -0x1.341d7961bd1d1p-4, 0x1.b599f227becbbp-58, -0x1.51b073f06183fp-4,
     -0x1.a49e39a1a8be4p-58, -0x1.6f0d28ae56b4cp-4, 0x1.906d99184b992p-58,
     -0x1.8c345d6319b21p-4, 0x1.4a697ab3424a9p-61, -0x1.a926d3a4ad563p-4,
     -0x1.942f48aa70ea9p-58, -0x1.c5e548f5bc743p-4, -0x1.5d617ef8161b1p-60,
     -0x1.e27076e2af2e6p-4, 0x1.61578001e0162p-60, -0x1.fec9131dbeabbp-4,
     0x1.5746b9981b36cp-58, -0x1.0d77e7cd08e59p-3, -0x1.9a5dc5e9030acp-57,
     -0x1.1b72ad52f67ap-3, -0x1.483023472cd74p-58, -0x1.29552f81ff523p-3,
     -0x1.301771c407dbfp-57, -0x1.371fc201e8f74p-3, -0x1.de6cb62af18ap-58,
     -0x1.44d2b6ccb7d1ep-3, -0x1.9f4f6543e1f88p-57, -0x1.526e5e3a1b438p-3,
     0x1.746ff8a470d3ap-57, -0x1.5ff3070a793d4p-3, 0x1.bc60efafc6f6ep-58,
     -0x1.6d60fe719d21dp-3, 0x1.caae268ecd179p-57, -0x1.7ab890210d909p-3,
     -0x1.be36b2d6a0608p-59, -0x1.87fa06520c911p-3, 0x1.bf7fdbfa08d9ap-57,
     -0x1.9525a9cf456b4p-3, -0x1.d904c1d4e2e26p-57, -0x1.a23bc1fe2b563p-3,
     -0x1.93711b07a998cp-59, -0x1.af3c94e80bff3p-3, 0x1.398cff3641985p-58,
     -0x1.bc286742d8cd6p-3, -0x1.4fce744870f55p-58, -0x1.c8ff7c79a9a22p-3,
     0x1.4f689f8434012p-57, -0x1.d5c216b4fbb91p-3, -0x1.6e443597e4d4p-57,
     -0x1.e27076e2af2e6p-3, 0x1.61578001e0162p-59, -0x1.ef0adcbdc5936p-3,
     -0x1.48637950dc20dp-57, -0x1.fb9186d5e3e2bp-3, 0x1.caaae64f21acbp-57,
     -0x1.0402594b4d041p-2, 0x1.28ec217a5022dp-57, -0x1.0a324e27390e3p-2,
     -0x1.7dcfde8061c03p-56, -0x1.1058bf9ae4ad5p-2, -0x1.89fa0ab4cb31dp-58,
     -0x1.1675cababa60ep-2, -0x1.ce63eab883717p-61, -0x1.1c898c16999fbp-2,
     0x1.0e5c62aff1c44p-60, -0x1.22941fbcf7966p-2, 0x1.76f5eb09628afp-56,
     -0x1.2895a13de86a3p-2, -0x1.7ad24c13f040ep-56, -0x1.2e8e2bae11d31p-2,
     0x1.8f4cdb95ebdf9p-56, -0x1.347dd9a987d55p-2, 0x1.4dd4c580919f8p-57,
     -0x1.3a64c556945eap-2, 0x1.c68651945f97cp-57, -0x1.404308686a7e4p-2,
     0x1.0bcfb6082ce6dp-56, -0x1.4618bc21c5ec2p-2, -0x1.f42decdeccf1dp-56,
     -0x1.4be5f957778a1p-2, 0x1.259b35b04813dp-57, -0x1.51aad872df82dp-2,
     -0x1.3927ac19f55e3p-59, -0x1.5767717455a6cp-2, -0x1.526adb283660cp-56,
     -0x1.5d1bdbf5809cap-2, -0x1.4236383dc7fe1p-56, -0x1.62c82f2b9c795p-2,
     -0x1.7b7af915300e5p-57, 0x1.5d5bddf595f3p-2, -0x1.6541148cbb8a2p-56,
     0x1.57bf753c8d1fbp-2, -0x1.0908d15f88b63p-57, 0x1.522ae0738a3d8p-2,
     -0x1.8f7e9b38a6979p-57, 0x1.4c9e09e172c3cp-2, -0x1.123615b147a5dp-58,
     0x1.4718dc271c41bp-2, 0x1.8fb4c14c56eefp-60, 0x1.419b423d5e8c7p-2,
     0x1.0dbb243827392p-57, 0x1.3c25277333184p-2, -0x1.2ad27e50a8ec6p-56,
     0x1.36b6776be1117p-2, -0x1.324f0e883858ep-58, 0x1.314f1e1d35ce4p-2,
     -0x1.3d69909e5c3dcp-56, 0x1.2bef07cdc9354p-2, -0x1.82dad7fd86088p-56,
     0x1.269621134db92p-2, 0x1.e0efadd9db02bp-56, 0x1.214456d0eb8d4p-2,
     0x1.f7ae91aeba60ap-57, 0x1.1bf99635a6b95p-2, -0x1.12aeb84249223p-57,
     0x1.16b5ccbacfb73p-2, 0x1.66fbd28b40935p-56, 0x1.1178e8227e47cp-2,
     -0x1.0e63a5f01c691p-57, 0x1.0c42d676162e3p-2, 0x1.162c79d5d11eep-58,
     0x1.07138604d5862p-2, 0x1.cdb16ed4e9138p-56, 0x1.01eae5626c691p-2,
     -0x1.18290bd2932e2p-59, 0x1.f991c6cb3b379p-3, 0x1.f665066f980a2p-57,
     0x1.ef5ade4dcffe6p-3, -0x1.08ab2ddc708ap-58, 0x1.e530effe71012p-3,
     0x1.2276041f43042p-59, 0x1.db13db0d4894p-3, 0x1.aa11d49f96cb9p-58,
     0x1.d1037f2655e7bp-3, 0x1.60629242471a2p-57, 0x1.c6ffbc6f00f71p-3,
     -0x1.8e58b2c57a4a5p-57, 0x1.bd087383bd8adp-3, 0x1.dd355f6a516d7p-60,
     0x1.b31d8575bce3dp-3, -0x1.6353ab386a94dp-57, 0x1.a93ed3c8ad9e3p-3,
     0x1.bcafa9de97203p-57, 0x1.9f6c407089664p-3, 0x1.35a19605e67efp-59,
     0x1.95a5adcf7017fp-3, 0x1.142c507fb7a3dp-58, 0x1.8beafeb38fe8cp-3,
     0x1.55aa8b6997a4p-58, 0x1.823c16551a3c2p-3, -0x1.1232ce70be781p-57,
     0x1.7898d85444c73p-3, 0x1.ef8f6ebcfb201p-58, 0x1.6f0128b756abcp-3,
     -0x1.8de59c21e166cp-57, 0x1.6574ebe8c133ap-3, -0x1.d34f0f4621bedp-60,
     0x1.5bf406b543db2p-3, -0x1.1f5b44c0df7e7p-61, 0x1.527e5e4a1b58dp-3,
     -0x1.71a9682395bfdp-61, 0x1.4913d8333b561p-3, -0x1.0d5604930f135p-58,
     0x1.3fb45a59928ccp-3, -0x1.d87e6a354d056p-57, 0x1.365fcb0159016p-3,
     0x1.7d411a5b944adp-58, 0x1.2d1610c86813ap-3, -0x1.499a3f25af95fp-58,
     0x1.23d712a49c202p-3, -0x1.6e38161051d69p-57, 0x1.1aa2b7e23f72ap-3,
     -0x1.c6ef1d9b2ef7ep-59, 0x1.1178e8227e47cp-3, -0x1.0e63a5f01c691p-58,
     0x1.08598b59e3a07p-3, -0x1.dd7009902bf32p-57, 0x1.fe89139dbd566p-4,
     -0x1.ac9f4215f9393p-58, 0x1.ec739830a112p-4, -0x1.a2bf991780d3fp-59,
     0x1.da727638446a2p-4, 0x1.401fa71733019p-58, 0x1.c885801bc4b23p-4,
     0x1.a38cb559a6706p-58, 0x1.b6ac88dad5b1cp-4, -0x1.0057eed1ca59fp-59,
     0x1.a4e7640b1bc38p-4, -0x1.5b5ca203e4259p-58, 0x1.9335e5d594989p-4,
     -0x1.478a85704ccb7p-58, 0x1.8197e2f40e3fp-4, 0x1.b9f2dffbeed43p-60,
     0x1.700d30aeac0e1p-4, -0x1.72566212cdd05p-61, 0x1.5e95a4d9791cbp-4,
     0x1.f38745c5c450ap-58, 0x1.4d3115d207eacp-4, 0x1.769f42c7842ccp-58,
     0x1.3bdf5a7d1ee64p-4, 0x1.7a976d3b5b45fp-59, 0x1.2aa04a44717a5p-4,
     -0x1.d15d38d2fa3f7p-58, 0x1.1973bd1465567p-4, -0x1.7558367a6acf6p-59,
     0x1.08598b59e3a07p-4, -0x1.dd7009902bf32p-58, 0x1.eea31c006b87cp-5,
     -0x1.3e4fc93b7b66cp-59, 0x1.ccb73cdddb2ccp-5, -0x1.e48fb0500efd4p-59,
     0x1.aaef2d0fb10fcp-5, 0x1.a353bb42e0addp-61, 0x1.894aa149fb343p-5,
     0x1.a8be97660a23dp-60, 0x1.67c94f2d4bb58p-5, 0x1.0413e6505e603p-59,
     0x1.466aed42de3eap-5, -0x1.cdd6f7f4a137ep-59, 0x1.252f32f8d183fp-5,
     -0x1.947f792615916p-59, 0x1.0415d89e74444p-5, 0x1.c05cf1d753622p-59,
     0x1.c63d2ec14aaf2p-6, -0x1.ce030a686bd86p-60, 0x1.8492528c8cabfp-6,
     -0x1.d192d0619fa67p-60, 0x1.432a925980cc1p-6, -0x1.8cdaf39004192p-60,
     0x1.0205658935847p-6, 0x1.27c8e8416e71fp-60, 0x1.82448a388a2aap-7,
     0x1.04b16137f09ap-62, 0x1.010157588de71p-7, 0x1.46662d417cedp-62,
     0x1.0080559588b35p-8, 0x1.f96638cf63677p-62
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

double log_double_x86(double);
double log_double_x86(double x){
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
    double tmp19;
    double carg1;
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
    double tmp35;
    double carg2;
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
    double carg3;
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
    double tmp71;
    double carg4;
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
    double tmp89;
    double carg5;
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
    double tmp107;
    double carg6;
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
    double tmp125;
    double carg7;
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
    double tmp143;
    double carg8;
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
    double carg9;
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
    double tmp179;
    double carg10;
    double tmp180;
    double tmp181;
    double tmp182;
    double carg11;
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
    double log1pu_poly_hi;
    int tmp196;
    int32_t tmp197;
    uint64_t exponent_srl_cast;
    int64_t tmp198;
    int64_t tmp199;
    int64_t tmp_eptau;
    int64_t tmp200;
    double fp_exponent;
    double tmp201;
    double carg12;
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
    double log1pu_poly_lo;
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
    uint32_t table_index_lo;
    double tbl_lo;
    double tmp224;
    double tmp225;
    double tmp226;
    double tmp227;
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
    tmp18 = u * u;
    tmp19 = u * 0x1.74616a4bec9cap-4;
    carg1 =  - tmp19;
    tmp20 = fma(u, 0x1.74616a4bec9cap-4, carg1);
    tmp21 = u * 0x1.9dab1b1f9803p-60;
    tmp22 = tmp20 + tmp21;
    tmp23 = tmp19 + tmp22;
    tmp24 = -0x1.999da78fa5e07p-4 + tmp23;
    tmp25 = tmp24 - tmp23;
    tmp26 = -0x1.999da78fa5e07p-4 - tmp25;
    tmp27 = tmp24 - tmp25;
    tmp28 = tmp23 - tmp27;
    tmp29 = tmp26 + tmp28;
    tmp30 = tmp23 - tmp19;
    tmp31 = tmp22 - tmp30;
    tmp32 = -0x1.8eb25ed84333p-59 + tmp31;
    tmp33 = tmp29 + tmp32;
    tmp34 = tmp24 + tmp33;
    tmp35 = u * tmp34;
    carg2 =  - tmp35;
    tmp36 = fma(u, tmp34, carg2);
    tmp37 = tmp34 - tmp24;
    tmp38 = tmp33 - tmp37;
    tmp39 = u * tmp38;
    tmp40 = tmp36 + tmp39;
    tmp41 = tmp35 + tmp40;
    tmp42 = 0x1.c71c71c14c143p-4 + tmp41;
    tmp43 = tmp42 - tmp41;
    tmp44 = 0x1.c71c71c14c143p-4 - tmp43;
    tmp45 = tmp42 - tmp43;
    tmp46 = tmp41 - tmp45;
    tmp47 = tmp44 + tmp46;
    tmp48 = tmp41 - tmp35;
    tmp49 = tmp40 - tmp48;
    tmp50 = -0x1.ee4c80b64e4bfp-58 + tmp49;
    tmp51 = tmp47 + tmp50;
    tmp52 = tmp42 + tmp51;
    tmp53 = u * tmp52;
    carg3 =  - tmp53;
    tmp54 = fma(u, tmp52, carg3);
    tmp55 = tmp52 - tmp42;
    tmp56 = tmp51 - tmp55;
    tmp57 = u * tmp56;
    tmp58 = tmp54 + tmp57;
    tmp59 = tmp53 + tmp58;
    tmp60 = -0x1.fffffffb69e54p-4 + tmp59;
    tmp61 = tmp60 - tmp59;
    tmp62 = -0x1.fffffffb69e54p-4 - tmp61;
    tmp63 = tmp60 - tmp61;
    tmp64 = tmp59 - tmp63;
    tmp65 = tmp62 + tmp64;
    tmp66 = tmp59 - tmp53;
    tmp67 = tmp58 - tmp66;
    tmp68 = -0x1.873f34019036ep-58 + tmp67;
    tmp69 = tmp65 + tmp68;
    tmp70 = tmp60 + tmp69;
    tmp71 = u * tmp70;
    carg4 =  - tmp71;
    tmp72 = fma(u, tmp70, carg4);
    tmp73 = tmp70 - tmp60;
    tmp74 = tmp69 - tmp73;
    tmp75 = u * tmp74;
    tmp76 = tmp72 + tmp75;
    tmp77 = tmp71 + tmp76;
    tmp78 = 0x1.24924924924bp-3 + tmp77;
    tmp79 = tmp78 - tmp77;
    tmp80 = 0x1.24924924924bp-3 - tmp79;
    tmp81 = tmp78 - tmp79;
    tmp82 = tmp77 - tmp81;
    tmp83 = tmp80 + tmp82;
    tmp84 = tmp77 - tmp71;
    tmp85 = tmp76 - tmp84;
    tmp86 = -0x1.440137392b13cp-58 + tmp85;
    tmp87 = tmp83 + tmp86;
    tmp88 = tmp78 + tmp87;
    tmp89 = u * tmp88;
    carg5 =  - tmp89;
    tmp90 = fma(u, tmp88, carg5);
    tmp91 = tmp88 - tmp78;
    tmp92 = tmp87 - tmp91;
    tmp93 = u * tmp92;
    tmp94 = tmp90 + tmp93;
    tmp95 = tmp89 + tmp94;
    tmp96 = -0x1.5555555555568p-3 + tmp95;
    tmp97 = tmp96 - tmp95;
    tmp98 = -0x1.5555555555568p-3 - tmp97;
    tmp99 = tmp96 - tmp97;
    tmp100 = tmp95 - tmp99;
    tmp101 = tmp98 + tmp100;
    tmp102 = tmp95 - tmp89;
    tmp103 = tmp94 - tmp102;
    tmp104 = -0x1.5f1d7519edebap-58 + tmp103;
    tmp105 = tmp101 + tmp104;
    tmp106 = tmp96 + tmp105;
    tmp107 = u * tmp106;
    carg6 =  - tmp107;
    tmp108 = fma(u, tmp106, carg6);
    tmp109 = tmp106 - tmp96;
    tmp110 = tmp105 - tmp109;
    tmp111 = u * tmp110;
    tmp112 = tmp108 + tmp111;
    tmp113 = tmp107 + tmp112;
    tmp114 = 0x1.999999999999ap-3 + tmp113;
    tmp115 = tmp114 - tmp113;
    tmp116 = 0x1.999999999999ap-3 - tmp115;
    tmp117 = tmp114 - tmp115;
    tmp118 = tmp113 - tmp117;
    tmp119 = tmp116 + tmp118;
    tmp120 = tmp113 - tmp107;
    tmp121 = tmp112 - tmp120;
    tmp122 = -0x1.99bc7d3b0460ap-57 + tmp121;
    tmp123 = tmp119 + tmp122;
    tmp124 = tmp114 + tmp123;
    tmp125 = u * tmp124;
    carg7 =  - tmp125;
    tmp126 = fma(u, tmp124, carg7);
    tmp127 = tmp124 - tmp114;
    tmp128 = tmp123 - tmp127;
    tmp129 = u * tmp128;
    tmp130 = tmp126 + tmp129;
    tmp131 = tmp125 + tmp130;
    tmp132 = -0x1p-2 + tmp131;
    tmp133 = tmp132 - tmp131;
    tmp134 = -0x1p-2 - tmp133;
    tmp135 = tmp132 - tmp133;
    tmp136 = tmp131 - tmp135;
    tmp137 = tmp134 + tmp136;
    tmp138 = tmp131 - tmp125;
    tmp139 = tmp130 - tmp138;
    tmp140 = 0x1.0e1892a99ap-69 + tmp139;
    tmp141 = tmp137 + tmp140;
    tmp142 = tmp132 + tmp141;
    tmp143 = u * tmp142;
    carg8 =  - tmp143;
    tmp144 = fma(u, tmp142, carg8);
    tmp145 = tmp142 - tmp132;
    tmp146 = tmp141 - tmp145;
    tmp147 = u * tmp146;
    tmp148 = tmp144 + tmp147;
    tmp149 = tmp143 + tmp148;
    tmp150 = 0x1.5555555555555p-2 + tmp149;
    tmp151 = tmp150 - tmp149;
    tmp152 = 0x1.5555555555555p-2 - tmp151;
    tmp153 = tmp150 - tmp151;
    tmp154 = tmp149 - tmp153;
    tmp155 = tmp152 + tmp154;
    tmp156 = tmp149 - tmp143;
    tmp157 = tmp148 - tmp156;
    tmp158 = 0x1.5555555731bb7p-56 + tmp157;
    tmp159 = tmp155 + tmp158;
    tmp160 = tmp150 + tmp159;
    tmp161 = u * tmp160;
    carg9 =  - tmp161;
    tmp162 = fma(u, tmp160, carg9);
    tmp163 = tmp160 - tmp150;
    tmp164 = tmp159 - tmp163;
    tmp165 = u * tmp164;
    tmp166 = tmp162 + tmp165;
    tmp167 = tmp161 + tmp166;
    tmp168 = -0x1p-1 + tmp167;
    tmp169 = tmp168 - tmp167;
    tmp170 = -0x1p-1 - tmp169;
    tmp171 = tmp168 - tmp169;
    tmp172 = tmp167 - tmp171;
    tmp173 = tmp170 + tmp172;
    tmp174 = tmp167 - tmp161;
    tmp175 = tmp166 - tmp174;
    tmp176 = -0x1.3a44p-89 + tmp175;
    tmp177 = tmp173 + tmp176;
    tmp178 = tmp168 + tmp177;
    tmp179 = tmp18 * tmp178;
    carg10 =  - tmp18;
    tmp180 = fma(u, u, carg10);
    tmp181 = tmp178 - tmp168;
    tmp182 = tmp177 - tmp181;
    carg11 =  - tmp179;
    tmp183 = fma(tmp18, tmp178, carg11);
    tmp184 = fma(tmp18, tmp182, tmp183);
    tmp185 = fma(tmp180, tmp178, tmp184);
    tmp186 = tmp179 + tmp185;
    tmp187 = u + tmp186;
    tmp188 = tmp186 - tmp179;
    tmp189 = tmp185 - tmp188;
    tmp190 = tmp187 - tmp186;
    tmp191 = u - tmp190;
    tmp192 = tmp187 - tmp190;
    tmp193 = tmp186 - tmp192;
    tmp194 = tmp191 + tmp193;
    tmp195 = tmp194 + tmp189;
    log1pu_poly_hi = tmp187 + tmp195;
    tmp196 = ( (int32_t) table_index) > INT32_C(53);
    tmp197 = tmp196 ? INT32_C(-1) : INT32_C(0);
    exponent_srl_cast = tmp6;
    tmp198 = exponent_srl_cast >> INT64_C(52);
    tmp199 = tmp198 + INT64_C(-1023);
    tmp_eptau = tmp199 + ( (int64_t) tmp197);
    tmp200 = tmp_eptau - alpha;
    fp_exponent = tmp200;
    tmp201 = fp_exponent * 0x1.62e42fefa39efp-1;
    carg12 =  - tmp201;
    tmp202 = fma(fp_exponent, 0x1.62e42fefa39efp-1, carg12);
    tmp203 = fp_exponent * 0x1.abc9e3b39803fp-56;
    tmp204 = tmp202 + tmp203;
    tmp205 = tmp201 + tmp204;
    tmp206 = tmp205 + log1pu_poly_hi;
    tmp207 = tmp206 - log1pu_poly_hi;
    tmp208 = tmp205 - tmp207;
    tmp209 = tmp206 - tmp207;
    tmp210 = log1pu_poly_hi - tmp209;
    tmp211 = tmp208 + tmp210;
    tmp212 = log1pu_poly_hi - tmp187;
    log1pu_poly_lo = tmp195 - tmp212;
    tmp213 = tmp205 - tmp201;
    tmp214 = tmp204 - tmp213;
    tmp215 = tmp214 + log1pu_poly_lo;
    tmp216 = tmp211 + tmp215;
    tmp217 = tmp206 + tmp216;
    tmp218 = tmp217 + tbl_hi;
    tmp219 = tmp218 - tbl_hi;
    tmp220 = tmp217 - tmp219;
    tmp221 = tmp218 - tmp219;
    tmp222 = tbl_hi - tmp221;
    tmp223 = tmp220 + tmp222;
    table_index_lo = table_index_hi + UINT32_C(1);
    tbl_lo = ml_log1p_table[table_index_lo];
    tmp224 = tmp217 - tmp206;
    tmp225 = tmp216 - tmp224;
    tmp226 = tmp225 + tbl_lo;
    tmp227 = tmp223 + tmp226;
    logx_hi = tmp218 + tmp227;
    return logx_hi;
}
