#define	__ELEM__ rlibm_log2_8
#include "OracleGenerate.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("UsageL %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunTest(argv[1]);
    return 0;
}
