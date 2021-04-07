#include "PolyGenSampling/PolyGenFromFile.h"

int main(int argc, char** argv) {
    
    // We want 3 additional command line arguments:
    if (argc != 4 && argc != 5) {
        printf("Usage : %s <interval file> <log file> <header file>\n", argv[0]);
        printf("Input : <interval file> - file containing reduced constrains\n");
        printf("Output: <log file> - where we print some logging information\n");
        printf("Output: <header file> - the file containing coefficients\n");
        exit(0);
    }

    FILE* f = fopen(argv[1], "r");
    FILE* log = fopen(argv[2], "w");
    FILE* header = fopen(argv[3], "w");
    
    std::vector<int> power({1, 3, 5});
    GeneratePiecewiseFunction(f, log, header,
                              power, 0, "SinpiCoeffs");
    
    fclose(f);
    fclose(log);
    fclose(header);


    return 0;
}
