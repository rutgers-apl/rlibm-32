#define MPFR_PREC 200
#include "LibTestHelper.h"

posit32_t MpfrCalculate(posit32_t x) {
    /*
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_exp(mval, mval, MPFR_RNDN);
    if (mpfr_inf_p(mval)) return castP32(0x7FFFFFFF);
    if (mpfr_zero_p(mval)) return castP32(0x00000001);
    return FromMPFR(mval);
     */
    
    switch (x.v) {
        case 8388608 :
            return castP32(1073741825);
            
        case 125828352 :
            return castP32(1073766401);
            
        case 146394183 :
            return castP32(1073786491);
            
        case 232703665 :
            return castP32(1073995703);
            
        case 277994243 :
            return castP32(1074342129);
            
        case 278268980 :
            return castP32(1074344285);
            
        case 315218639 :
            return castP32(1074634561);
            
        case 328917479 :
            return castP32(1074742339);
            
        case 353233600 :
            return castP32(1075073357);
            
        case 435196834 :
            return castP32(1076892373);
            
        case 484181783 :
            return castP32(1078935323);
            
        case 531981330:
            return castP32(1082073185);
            
        case 606416336 :
            return castP32(1087100779);
            
        case 695497874 :
            return castP32(1095109715);
            
        case 779740549:
            return castP32(1107808141);
            
        case 886453498 :
            return castP32(1139983475);
            
        case 949274143 :
            return castP32(1168997027);
            
        case 1054622425 :
            return castP32(1243621573);
            
        case 1116551649 :
            return castP32(1324696961);
            
        case 1174121770 :
            return castP32(1400644765);
            
        case 1223001644 :
            return castP32(1497292223);
            
        case 1240851334 :
            return castP32(1544557361);
            
        case 1423867798 :
            return castP32(1919877963);
            
        case 1447561583:
            return castP32(1953965929);
            
        case 3002068727 :
            return castP32(484623899);
            
        case 3014996578 :
            return castP32(502038269);
            
        case 3054755927 :
            return castP32(582384405);
            
        case 3084961894 :
            return castP32(677822899);
            
        case 3128146849 :
            return castP32(734307029);
            
        case 3164503295 :
            return castP32(795732033);
            
        case 3185007842 :
            return castP32(821882737);
            
        case 3201030038 :
            return castP32(841002223);
            
        case 3299499163 :
            return castP32(935458709);
            
        case 3322101822 :
            return castP32(949103599);
            
        case 3326595236 :
            return castP32(951530919);
            
        case 3331050605 :
            return castP32(953978139);
            
        case 3486306597 :
            return castP32(1013062005);
            
        case 3547164607 :
            return castP32(1025865311);
            
        case 3623670055 :
            return castP32(1042153809);
            
        case 3754660895 :
            return castP32(1057075047);
            
        case 3756230542 :
            return castP32(1057259137);
            
        case 3932991725 :
            return castP32(1070834553);
            
        case 4000125047 :
            return castP32(1072284611);
            
        case 4005298404 :
            return castP32(1072365019);
            
        case 4023715328 :
            return castP32(1072651461);
            
        case 4035724792 :
            return castP32(1072838411);
            
        case 4056072201 :
            return castP32(1073155457);
            
        case 4093612714 :
            return castP32(1073479589);
            
        case 4135957665 :
            return castP32(1073627891);
            
        case 4151576335 :
            return castP32(1073658385);
            
        case 4226778991 :
            return castP32(1073737465);
            
        case 4268064767 :
            return castP32(1073741733);
            
        case 4285530112 :
            return castP32(1073741823);

        default :
            double res = exp(convertP32ToDouble(x));
            if (res == 0.0) {
                return castP32(0x00000001);
            } else if (res == 1.0/0.0) {
                return castP32(0x7FFFFFFF);
            }
            return convertDoubleToP32(res);
    }
    
}

posit32_t dMlibTest(posit32_t x) {
    double result = exp(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_exp(x);
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Exp", argv[1]);
    
    return 0;
}
