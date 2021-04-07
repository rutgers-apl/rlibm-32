#include "PolyGenSampling.hpp"
#include "Helper.h"
#include "string.h"

/*##############################################################################
 PolyGenFromFile.h
 Summary: If there is a file including all the reduced inputs/interval, then use
 this file to generate piece-wise polynomial that satisfies all the constraints.
 For general case, use the function GeneratePiecewiseFunction. All other
 functions can be considered as "helper" functions. For more specifics on the
 usage of the function, refer to the comment section above the function
 declaration.
 
 Throughout the code in PolyGenFromFile.h, there are three files that are used.
 (1) File* data: Data containing a list of reduced input/interval. Each pair
                 of reduced input/interval is 24 bytes big. The constraints
                 should be in an ascending order of reduced input.
 (2) File* log: A file to save all logging information
 (3) File* header: *.h file where I save the # of common bits in the reduced
                   inputs, # of polynomials in piecewise polynomial, and the
                   coefficients of each polynomial.
 
 Note on the arguments "power" and "termSize" that is used throughout this file:
 The vector "power" is specified by the user. "power" describes the type of
 polynomial that the user desires to generate. For example, power = {1, 2, 4, 5}
 means that it will generate polynomial P(x) = c1x + c2x^2 + c4x^4 + c5x^5.
 This method allows to define any type of polynomial to be generated:
 (1) odd polynomial of up to degree 9: power = {1, 3, 5, 7, 9}
 (2) even polynomial of up to degree 14: power = {0, 2, 4, 6, 8, 10, 12, 14}
 (3) normal polynomial of up to degree 5: power = {0, 1, 2, 3, 4, 5}
 and so on...
 
 The argument "termSize" is used internally to determine the degree of
 polynomial to generate, based on the terms in "power" argument. For example, if
 power = {0, 1, 2, 3, 4, 5} and termSize = 3, then the code will try to generate
 a polynomial P(x) = c0 + c1x + c2x^2.
 #############################################################################*/



/*##############################################################################
 #############################################################################*/



/*##############################################################################
 Finds the index of the constraint in the data file where the reduced input is
 strictly less than "target." The function searches for the index between 0 and
 "end." If there is no index that where reduced input is strictly less, then
 it returns -1. The code essentially does binary search through "data" file.
 #############################################################################*/
long int StrictlyLessThan(FILE* data,
                          double target,
                          long int end) {
    long int start = 0;
    long int ans = -1;
    while (start <= end) {
        long int mid = (start + end) / 2;
        // Find the reduced X at mid index.
        fseek(data, 3 * sizeof(double) * mid, SEEK_SET);
        double midVal;
        fread(&midVal, sizeof(double), 1, data);
        
        if (midVal >= target) {
            end = mid - 1;
        } else {
            ans = mid;
            start = mid + 1;
        }
    }
    return ans;
}

/*##############################################################################
 Finds the index of the constraint in the data file where the reduced input is
 less than or equal to "target." The function searches for the index between
 "start" and "end." If there is no index that where reduced input is less than
 or equal, then it returns -1. The code essentially does binary search through
 "data" file.
 #############################################################################*/
long int LessThanEqual(FILE* data,
                               double target,
                               long int start,
                               long int end) {
    long int ans = -1;
    while (start <= end) {
        long int mid = (start + end) / 2;
        // Find the reduced X at mid index.
        fseek(data, 3 * sizeof(double) * mid, SEEK_SET);
        double midVal;
        fread(&midVal, sizeof(double), 1, data);
        
        if (midVal == target) {
            return mid;
        } else if (midVal > target) {
            end = mid - 1;
        } else {
            ans = mid;
            start = mid + 1;
        }
    }
    
    return ans;
}

/*##############################################################################
 Finds the index of the constraint in the data file where the reduced input is
 greater than or equal to "target." The function searches for the index between
 "start" and "end." If there is no index that where reduced input is greater
 than or equal, then it returns -1. The code essentially does binary search
 through "data" file.
 #############################################################################*/
long int GreaterThanEqual(FILE* data,
                          double target,
                          long int start,
                          long int end) {
    long int ans = -1;
    while (start <= end) {
        long int mid = (start + end) / 2;
        // Find the reduced X at mid index.
        fseek(data, 3 * sizeof(double) * mid, SEEK_SET);
        double midVal;
        fread(&midVal, sizeof(double), 1, data);
        
        if (midVal == target) {
            return mid;
        } else if (midVal > target) {
            ans = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return ans;
}

/*##############################################################################
 Generates a polynomial of degree "d" that satisfiess all constraints in the
 "data" file from "lbIndex" to "ubIndex." The degree "d" is determined by two
 arguments, "power" and "termSize." For more information, refer to the general
 comment section at the beginning of the file.
 #############################################################################*/
unique_ptr<Poly> GeneratePolynomialHelper(FILE* data, FILE* log,
                                          long int lbIndex, long int ubIndex,
                                          vector<int> power, int termSize) {
    long int count = ubIndex + 1 - lbIndex;
    fseek(data, lbIndex * 3 * sizeof(double), SEEK_SET);
    std::map<double, MapData> intervals;
    long int nextToRead = lbIndex;
    
    // Add constraints to sample pool. Try to add roughly 0.1% of constraints
    long int divisor = count / 1000;
    // If there's too many constraints, then limit it to 5000 constraints.
    if (divisor > 5000) divisor = 5000;
    // If there's too little constraints, still add at leats 200 constraints
    if (divisor < 200) divisor = 200;
    // step defines the distance between the two constraints to add
    long int step = count / divisor;
    if (step == 0) step++;
    
    // Now add a constraint in every step-size
    for (long int i = 0; i < count; i++) {
        double datas[3];
        fread(datas, sizeof(double), 3, data);
        if (lbIndex + i == nextToRead || i == count - 1) {
            MapData md;
            md.lb = datas[1];
            md.origLb = datas[1];
            md.ub = datas[2];
            md.origUb = datas[2];
            intervals.insert(std::pair<double, MapData>(datas[0], md));
            
            nextToRead += step;
            // Always add the last constraint
            if (nextToRead > ubIndex) nextToRead = ubIndex;
        }
    }
    
    unsigned long wrongCount = 1;
    unique_ptr<Poly> poly;
    while (wrongCount > 0) {
        // Now synthesize a polynomial with "power" and "termSize" using the
        // constraints in sample pool
        PolyFinder synthesizer(log);
        poly = synthesizer.SolvePolynomial(intervals, power, termSize);
        
        // If we can't find it, then return NULL ptr.
        if (!poly) {
            intervals.clear();
            fprintf(log, "Soplex couldn't find solution\n");
            return unique_ptr<Poly>();
        }
        
        // Clear all refined intervals before checking if polynomial satisfies
        // all constraints in this sub-domain
        std::map<double, MapData>::iterator it;
        for (it = intervals.begin(); it != intervals.end(); it++) {
          it->second.lb = it->second.origLb;
          it->second.ub = it->second.origUb;
        }
        
        // Check if generated polynomial satisfies each constrain in sub-domain
        wrongCount = 0;
        fseek(data, lbIndex * 3 * sizeof(double), SEEK_SET);
        for (long int i = 0; i < count; i++) {
            double datas[3];
            fread(datas, sizeof(double), 3, data);
            double tres = synthesizer.PolyEval(datas[0], poly);
            // If not, add it to the sample pool
            if (tres < datas[1] || tres > datas[2]) {
                MapData md;
                md.lb = datas[1];
                md.origLb = datas[1];
                md.ub = datas[2];
                md.origUb = datas[2];
                intervals.insert(std::pair<double, MapData>(datas[0], md));
                wrongCount++;
            }
            
            // If there are too many constraints, then quit. LP solver will
            // take too long
            if (intervals.size() > 35000) {
                fprintf(log, "Too many intervals: %lu\n", intervals.size());
                intervals.clear();
                return unique_ptr<Poly>();
            }
        }
        
        fprintf(log, "Found %lu / %lu wrong input\n", wrongCount, count);
        fprintf(log, "Total size of intervals: %lu\n", intervals.size());
    }
    
    // If generated polynomial satisfies all constraints in sub-domain, return
    // the polynomial.
    intervals.clear();
    return std::move(poly);
}

/*##############################################################################
 Generate polynomial for the sub-domain where the constraints are in the "data"
 file from "lbIndex" to "ubIndex." This function tries to generate a polynomial
 with the smallest termSize. Each term is defined in the vector "power." Returns
 the polynomial if it can be generated, otherwise returns Null pointer.
 #############################################################################*/
unique_ptr<Poly> GeneratePolynomial(FILE* data, FILE* log,
                                    long int lbIndex, long int ubIndex,
                                    vector<int> power) {
    
    for (int i = 0; i < power.size(); i++) {
        fprintf(log, "Trying to create poly for term size %d\n", i + 1);
        unique_ptr<Poly> p = GeneratePolynomialHelper(data, log, lbIndex, ubIndex, power, i + 1);
        if (p) return std::move(p);
    }
    
    return unique_ptr<Poly>();
}

/*##############################################################################
 All reduced inputs in "data" have "bitsSame" number of significant bits that
 are the same. The bit-pattern is sigBits. Thus, based on these bit-pattern,
 compute which inputs belong to the sub-domain with index "index." Then, return
 the index of the inputs that belong to this sub-domain in "lbIndex" and
 "ubIndex." "lbIndex" is the index of the constraint with the smallets
 reduced input and "ubIndex" is the index of the constraint with the largest
 reduced input that belong to this sub-domain.
 #############################################################################*/
void FindIndexOfSubDomain(FILE* data, FILE* log, FILE* header,
                          unsigned long firstIndex, unsigned long lastIndex,
                          unsigned long bitsSame, unsigned long sigBits,
                          unsigned long N, unsigned long index,
                          long& lbIndex, long& ubIndex) {
    
    // Compute the range of inputs for the selected sub-domain (index)
    unsigned long combined = sigBits | (index << (64 - bitsSame - N));
    double domainLb = *(double*)&combined;
    if (domainLb > 0 && index == 0) domainLb = 0.0;
    combined = combined | ((0x1lu << (64 - bitsSame - N)) - 0x1lu);
    double domainUb = *(double*)&combined;
    
    // domainLB and domainUB could be negative!
    if (domainLb > domainUb) {
        double temp = domainLb;
        domainLb = domainUb;
        domainUb = temp;
    }
    
    // Identify the index of the constraints with smallest/largest reduced
    // input belonging to the sub-domain
    lbIndex = GreaterThanEqual(data, domainLb, firstIndex, lastIndex);
    ubIndex = LessThanEqual(data, domainUb, firstIndex, lastIndex);
}

/*##############################################################################
 The constraints from "firstIndex" to "lastIndex" have either all positive
 inputs or all negative inputs. Generate a piecewise-polynomial that satisfies
 all constraints from "firstIndex" to "lastIndex." If "minN" = 0, then the
 function repeatedly splits the input domain until polynomials can be generated.
 Otherwise, this function will only try to generate a piecewise polynomial with
 2^minN polynomials.
 #############################################################################*/
void SplitDomain(FILE* data, FILE* log, FILE* header, vector<int> power,
                 unsigned long firstIndex, unsigned long lastIndex,
                 unsigned long bitsSame, unsigned long sigBits, int minN,
                 char const* nameOfArray) {
    
    // Determine the minimum and maximum size of piecewise polynomial.
    // By default, it's from 2^NBegin to 2^NEnd.
    unsigned long NBegin = 0;
    unsigned long NEnd = 16;
    if (minN >= 0) {
        NBegin = minN;
        NEnd = minN + 1;
    }
    
    for (unsigned long N = NBegin; N < NEnd; N++) {
        // Split the domain into 2^N domains
        fprintf(log, "SPLITTING TO 2^%lu DOMAINS\n", N);
        double lbIndexMax, ubIndexMax;
        unsigned long totalSplit = 0x1lu << N;
        unsigned long powerSize = power.size();
        
        // Create an array to store the coefficients
        double** coeffs = new double*[totalSplit];
        for (int i = 0; i < totalSplit; i++) {
            coeffs[i] = new double[powerSize];
        }
        
        bool completed = true;
        int maxTermNum = 0;
        for (unsigned long index = 0; index < totalSplit; index++) {
            // Compute the lower and upper indexes of constraints within the
            // sub-domain #index.
            long int lbIndex, ubIndex;
            FindIndexOfSubDomain(data, log, header, firstIndex, lastIndex,
                                 bitsSame, sigBits, N, index,
                                 lbIndex, ubIndex);
            
            // Determine if there are any constraints within the subdomain
            if (lbIndex >= 0 && ubIndex >= 0 && lbIndex <= ubIndex) {
                // There is something in here
                fprintf(log, "\tINDEX %lu\n", index);
                // So generate a polynomial for this subdomain
                unique_ptr<Poly> p =
                GeneratePolynomial(data, log, lbIndex, ubIndex, power);
                
                // If we can't, then break out of this loop and split the domain
                // into smaller sub-domain
                if (!p) {
                    completed = false;
                    break;
                } else {
                    // Otherwise, record the coefficients.
                    for (int j = 0; j < power.size(); j++) {
                        if (j < p->termSize) coeffs[index][j] = p->coeffs[j];
                        else coeffs[index][j] = 0;
                    }
                    if (maxTermNum < p->termSize) {
                        maxTermNum = p->termSize;
                    }
                }
                
            } else {
                // If there are no constraints in the sub-domain, then coeffs
                // are all 0's.
                for (int j = 0; j < powerSize; j++) coeffs[index][j] = 0;
            }
            
        }
        
        // If we successfully generated polynomial with 2^N subdomains, then
        // write the coefficients and other information to the header file.
        if (completed) {
            // Write stuff to header file
            fprintf(header, "#define %sBitsSame = %lu\n", nameOfArray, bitsSame);
            fprintf(header, "#define %sN = %lu\n", nameOfArray, N);
            fprintf(header, "static const double %s[%lu][%d] = {\n",
                    nameOfArray, totalSplit, maxTermNum);
            for (int i = 0; i < totalSplit; i++) {
                fprintf(header, "\t{\n");
                for (int j = 0; j < maxTermNum; j++) {
                    fprintf(header, "\t\t%.100e", coeffs[i][j]);
                    if (j < maxTermNum - 1) fprintf(header, ",\n");
                    else fprintf(header, "\n");
                }
                fprintf(header, "\t}");
                
                if (i < totalSplit - 1) fprintf(header, ",\n");
                else fprintf(header, "\n");
            }
            fprintf(header, "};\n");
            fflush(header);
            fprintf(log, "polynomial coefficient written to file");
        } else {
            fprintf(log, "Could not generate a piece-wise polynomial.");
        }
        
        // Get rid of arrays that stored the coefficients
        for (int i = 0; i < totalSplit; i++) {
            delete[] coeffs[i];
        }
        delete[] coeffs;
        
        fprintf(log, "\n\n");

        // If we successfully created piecewise polynomial, then finish.
        if (completed) return;
    }
}

/*##############################################################################
 Compute the information about how to split the domain. More specifically,
 we compute how many leading bits are common in the reduced inputs (bitsSame)
 and the bit-pattern of those inputs (sigBits).
 #############################################################################*/
void ComputeReducedInputInfo(FILE* data, FILE* log, FILE* header,
                        unsigned long firstIndex, unsigned long lastIndex,
                        vector<int> power, int minN, char const* nameOfArray) {
    // Read the first reduced input
    double firstRedX[3], lastRedX[3];
    fseek(data, 3 * sizeof(double) * firstIndex, SEEK_SET);
    fread(firstRedX, sizeof(double), 3, data);
    // Ignore 0 when computing bitsSame
    if (firstRedX[0] == 0.0) fread(firstRedX, sizeof(double), 3, data);
    
    // read the last reduced input
    fseek(data, 3 * sizeof(double) * lastIndex, SEEK_SET);
    fread(lastRedX, sizeof(double), 3, data);
    
    // Compare the first bits and see if they are the same.
    unsigned long bitsSame = 0;
    unsigned long sigBits = 0;
    unsigned long fRedXBits = *(unsigned long*)&firstRedX[0];
    unsigned long lRedXBits = *(unsigned long*)&lastRedX[0];
    while ((fRedXBits & (0x1lu << (63lu - bitsSame))) ==
           (lRedXBits & (0x1lu << (63lu - bitsSame)))) {
        sigBits |= fRedXBits & (0x1lu << (63lu - bitsSame));
        bitsSame++;
    }
    
    // Using these information, split the domain and generate polynomial
    SplitDomain(data, log, header, power, firstIndex, lastIndex,
                bitsSame, sigBits, minN, nameOfArray);
}

/*##############################################################################
 Generate piecewise function that satisfies all constraints in the "data" file.
 Each polynomial will have up to the # of terms specified in the "power" vector.
 Any logging information will be written to the "log" file and if we successfully
 generate piecewise polynomial, then the coefficients will be written to the
 "header" file.
 #############################################################################*/
void GeneratePiecewiseFunction(FILE* data, FILE* log, FILE* header,
                               vector<int> power, int minN,
                               char const* nameOfArray) {
    // Read the first entry (first 24 bytes) and the last entry (last 24 bytes).
    // If the reduced X's have different signs, then let's just solve them
    // separately.
    fseek(data, 0, SEEK_SET);
    double firstEntry[3];
    long int firstIndex = 0;
    fread(firstEntry, sizeof(double), 3, data);
    
    fseek(data, 0, SEEK_END);
    long int numInts = ftell(data);
    numInts = numInts / (3 * sizeof(double));
    
    fseek(data, -3 * sizeof(double), SEEK_CUR);
    double lastEntry[3];
    fread(lastEntry, sizeof(double), 3, data);
    long int lastIndex = numInts - 1;
    
    // Just a single piecewise polynomial for all reduced inputs.
    fprintf(log, "Generating polynomials\n");
    ComputeReducedInputInfo(data, log, header, firstIndex, lastIndex, power, minN, nameOfArray);
}

// This function is for approximations that contains both positive and negative
// reduced inputs
void GeneratePiecewiseFunction(FILE* data, FILE* log, FILE* header,
                               vector<int> negPower, int negMinN,
                               char const* nameOfNegArray,
                               vector<int> posPower, int posMinN,
                               char const* nameOfPosArray) {
    // Read the first entry (first 24 bytes) and the last entry (last 24 bytes).
    // If the reduced X's have different signs, then let's just solve them
    // separately.
    fseek(data, 0, SEEK_SET);
    double firstEntry[3];
    long int firstIndex = 0;
    fread(firstEntry, sizeof(double), 3, data);
    
    fseek(data, 0, SEEK_END);
    long int numInts = ftell(data);
    numInts = numInts / (3 * sizeof(double));
    
    fseek(data, -3 * sizeof(double), SEEK_CUR);
    double lastEntry[3];
    fread(lastEntry, sizeof(double), 3, data);
    long int lastIndex = numInts - 1;
    
    // If first reduced X is < 0 AND last reduced X > 0, then split it into
    // two parts. One part will negative reduced inputs, and the other part.
    long int lastNegIndex = StrictlyLessThan(data, 0.0, lastIndex);
    long int firstPosIndex = lastNegIndex + 1;
    
    fprintf(log, "Generating for negative reduced inputs\n");
    fflush(log);
    ComputeReducedInputInfo(data, log, header, firstIndex,
                            lastNegIndex, negPower, negMinN, nameOfNegArray);
    fprintf(log, "Finished generating polynomials for negative reduced inputs\n");
    fflush(log);
    fprintf(log, "Generating for positive reduced inputs\n");
    ComputeReducedInputInfo(data, log, header, firstPosIndex,
                            lastIndex, posPower, posMinN, nameOfPosArray);
    fprintf(log, "Finished generating polynomials for positive reduced inputs\n");
    fflush(log);
}
