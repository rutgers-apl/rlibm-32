#define INITIAL_RATE 200
#define INITIAL_MAX 7500

#include "PolyGenSampling/PolyGenFromFile.h"

int main(int argc, char** argv) {
    
    // We want 3 additional command line arguments:
    if (argc != 4 && argc != 5) {
        printf("Usage : %s <interval file> <log file> <header file>\n", argv[0]);
        printf("Input : <interval file> - file containing reduced constrains\n");
        printf("Output: <log file> - where we print some logging information\n");
        printf("Output: <header file> - the file containing coefficients\n");
    }

    FILE* f = fopen(argv[1], "r");
    FILE* log = fopen(argv[2], "w");
    FILE* header = fopen(argv[3], "w");
    
    std::vector<int> power({0, 1, 2, 3});
    GeneratePiecewiseFunction(f, log, header,
                              power, 10, "negExp2Coeffs",
                              power, 12, "posExp2Coeffs");
    
    fclose(f);
    fclose(log);
    fclose(header);

    printf("Exp2 Time:\n");
    return 0;
}
