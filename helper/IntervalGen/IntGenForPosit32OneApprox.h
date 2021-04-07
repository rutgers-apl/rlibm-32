#pragma once
#include "Common.h"
#include <string>
#include <queue>
#include <map>
#include <cstdio>
#include "softposit_cpp.h"

mpfr_t mval;

int fileIndex = 0;

/*################################################
 Helper function declaration begin
 ################################################*/

// Rounds a mpfr_t value into float directly. This is to avoid double rounding.
// The rounding mode used is round-to-nearest-tie-goes-to-even
// Argument 1   (mpfr_t) : the mpfr value to round
// return value (float)  : correctly rounded value
posit32 FromMPFRHelper(mpfr_t);

// Compute the rounding interval for a float value passed by argument 1. Lb and
// Ub are returned in 2nd and 3rd argument, respectively
// Argument 1   (float)  : float value v
// Argument 2   (double) : lb of rounding interval
// Argument 3   (double) : ub of rounding interval
void CalculateInterval(posit32, double&, double&);

// Error message when the initial guess on lb and ub leads to a result that is
// outside of the rounding interval
void CalcRedIntErrorMsg1(posit32, double, double, double, double, double);

// Create a new temporary file name based on the largeFileName that is passed
// Argument 1   (string) : a filename used to create a new temporary file name
// return value (string) : a new temporary file name
string GetNewFileName(string largeFileName);

// Copy data from source array to dest array. very simple helper function
void CopyData(double dest[3], double source[3]);

// Read 3 doubles from f. A simple helper function to include some sanity check
bool ReadData(FILE* f, double dest[3]);

// Writes a map of intervals to a file specified by newFileName
// Argument 1   (map)    : a map containing reduced inputs and intervals
// Argument 2   (string) : name of the file to write the reduced inputs and
//                         interval information into.
void SaveIntervalsToAFile(std::map<double, IntData> intervals,
                          string newFileName);

/*################################################
 Helper function declaration end
 ################################################*/


// Description of an elementary function for 32-bit float math library. This
// class should be used if the output compensation function uses 1 approximation
// MpfrCalculateFunction, ComputeSpecialCase, RangeReduction,
// OutputCompensation, GuessInitialLbUb, SpecCaseRedInt must be implemented per
// elementary function.
class IntervalGenerator {
    public :
    
    // The oracle that computes the correctly rounded result.
    // Argument 1   (float) : original input x
    // return value (float) : correctly rounded result of f(x)
    posit32 MpfrCalculateFunction(posit32);
    
    // Defines the special case inputs. Accepts original input x. Returns
    // whether the input is a special case and f(x) for the input x.
    // Argument 1   (posit32) : original input x
    // return value (bool)  : whether x is special case or not
    // return value (posit32&): returned via argument 2. the result of f(x) if
    //                        x is a special case input
    bool ComputeSpecialCase(posit32, posit32&);
    
    // Range reduction function. Accepts original input x and returns the
    // reduced input x'
    // Argument 1   (double) : original input x
    // return value (double) : reduced input x'
    double RangeReduction(double);
    
    // Output compensation function. Accepts y' and original input x and returns
    // the actual output y
    // Argument 1   (double) : original input x
    // Argument 2   (double) : y' = P(x')
    // return value (double) : approximation of f(x)
    double OutputCompensation(double, double);
    
    // Provides an initial guess on what the reduced interval should be. This
    // function should be used when output compensation function only uses one
    // approximation function.
    // Argument 1   (double) : original input x
    // Argument 2   (double) : Lb of the rounding interval
    // Argument 3   (double) : Ub of the rounding interval
    // Argument 4   (double) : reduced input x'
    // return value (double) : via argument 5. the lb of reduced interval
    // return value (double) : via argument 6. the ub of reduced interval
    void GuessInitialLbUb(double, double, double, double, double&, double&);
    
    // In some cases, we may need special treatment for the reduced interval.
    // This function is used to specify whether we should treat the reduced
    // interval as a special case. In that case, the function should return true
    // and also pass the customized [lb, ub] of the reduced input.
    // Argument 1   (double) : original input x
    // Argument 2   (double) : initial lb guess for reduced interval
    // return value (bool)   : returned as argument 3. whether the lb is a
    //                         special case
    // return value (double) : returned as argument 4. Lb of reduced input
    // Argument 5   (double) : initial ub guess for reduced interval
    // return value (bool)   : returned as argument 6. whether the ub is a
    //                         special case
    // return value (double) : returned as argument 7. Ub of reduced input
    void SpecCaseRedInt(double, double, bool&, double&, double, bool&, double&);
    
    // Computes reduced intervals from xlow to xhigh. If xlow > xhigh, then we
    // compute reduced intervals from 0 to 0x100000000. The reduced intervals are
    // added to the file since it is theoretically possible to have 2^32 reduced
    // intervals
    // Argument 1   (ull)   : the lower bound of input domain x
    // Argument 2   (ull)   : the upper bound of input domain x
    // Argument 3   (FILE*) : to store the reduced inputs and range
    // * Note: Function adds reduced input, reduced interval lower bound, and
    //         upperbound in filename. Thus, each input will add 24 bytes to the
    //         file. The resulting file will have duplicate reduced inputs.
    void ComputeReducedIntervals(unsigned long long, unsigned long long, FILE*);
    
    // Computes reduced interval for one input x. The reduced intervals are
    // added to the file
    // Argument 1   (float) : original input x
    // Argument 2   (FILE*) : file in which we write reduced input and interval
    void ComputeReducedInterval(posit32, FILE*);
    
    // Based on special case, range reduction, and output compensation function
    // create a file containing reduced inputs and reduced intervals. This file
    // contains merged reduced intervals sorted by reduced input.
    // Argument 1   (char*) : the name of the file to store reduced inputs and
    //                        intervals
    void CreateReducedIntervalFile(char*);

    // Based on special case, range reduction, and output compensation function
    // create a file containing reduced inputs and reduced intervals. This file
    // contains merged reduced intervals sorted by reduced input.
    // Argument 1   (ull)   : lower bound of the input domain
    // Argument 2   (ull)   : upper bound of the input domain
    // Argument 3   (char*) : the name of the file to store reduced inputs and
    //                        intervals
    void CreateReducedIntervalFile(unsigned long long, unsigned long long, char*);
    
    // Given a file with filename that contains reduced inputs and intervals,
    // merge same reduced inputs and sort them by reduced input.
    // It uses a type of merge sort. This function will also create several
    // temporary files.
    void SortIntervalFile(string, string);
    
    // Given two filenames, take reduced inputs and intervals and merge them
    // in an ascending order by inputs. Then save it to a file with the
    // third filename
    // Argument 1   (string) : a file containing reduced inputs and intervals
    // Argument 2   (string) : another file containing reduced inputs and
    //                         intervals
    // Argument 3   (string) : A file with emrged inputs and intervalss
    void MergeFiles(string, string, string);

    // Rounds an mpfr_t value to a float value using round to nearest tie goes
    // to even mode. This is required to avoid double rounding error.
    posit32 FromMPFR(mpfr_t);
};

/*################################################
 Class function implementation
 ################################################*/

void IntervalGenerator::CreateReducedIntervalFile(char* filename) {
    CreateReducedIntervalFile(0x0llu, 0x100000000llu, filename);
}

void IntervalGenerator::CreateReducedIntervalFile(unsigned long long xlow,
                                                  unsigned long long xhigh,
                                                  char* filename) {
    string fileNameString = filename;
    string largeFileName = fileNameString.append("_large");
    
    FILE* largeFile = fopen(largeFileName.c_str(), "w");
    // Initially create a file with all the reduced inputs and intervals
    ComputeReducedIntervals(xlow, xhigh, largeFile);
    fclose(largeFile);
    
    // Sort the interval file and create a file named "filename"
    SortIntervalFile(largeFileName, filename);
}

void IntervalGenerator::SortIntervalFile(string source, string dest) {
    std::map<double, IntData> intervals;
    std::map<double, IntData>::iterator it;
    std::queue<string> tempFiles;
    
    FILE* f = fopen(source.c_str(), "r");
    if (!f) {
        printf("Could not open file\n");
    }
    double data[3];
    
    // Read intervals into sorted map. Output intervals to temp files, 40M
    // intervals at a time.
    unsigned long long int counter = 0;
    while (fread(data, sizeof(double), 3, f) == 3) {
        if (data[1] <= -1.0e300 && data[2] >= 1.0e300) {
            
        } else {
            it = intervals.find(data[0]);
            if (it != intervals.end()) {
                if (data[1] > it->second.lb) it->second.lb = data[1];
                if (data[2] < it->second.ub) it->second.ub = data[2];
            } else {
                IntData temp;
                temp.lb = data[1];
                temp.ub = data[2];
                intervals[data[0]] = temp;
            }
        }
        
        counter++;
        
        // If there's 40M intervals, then save intervals to a temp file.
        if (intervals.size() == 40000000) {
            string newFileName = GetNewFileName(source);
            SaveIntervalsToAFile(intervals, newFileName);
            tempFiles.push(newFileName);
            intervals.clear();
        }
    }
    
    fclose(f);
    
    // If there's anything else left, then save leftover to a temp file.
    if (intervals.size() > 0) {
        string newFileName = GetNewFileName(source);
        SaveIntervalsToAFile(intervals, newFileName);
        tempFiles.push(newFileName);
        intervals.clear();
    }
    
    remove(source.c_str());
        
    // Once we created temp files, we read two files at a time from the queue,
    // and combine them. Delete the two old files. Add the new file to the queue.
    while (tempFiles.size() > 1) {
        string tempFile1 = tempFiles.front();
        tempFiles.pop();
        string tempFile2 = tempFiles.front();
        tempFiles.pop();
        string newFileName = GetNewFileName(source);
        MergeFiles(tempFile1, tempFile2, newFileName);
        remove(tempFile1.c_str());
        remove(tempFile2.c_str());
        
        tempFiles.push(newFileName);
    }
    
    // If there is only one file left in the queue, then we rename it to filename
    string tempFile1 = tempFiles.front();
    tempFiles.pop();
    rename(tempFile1.c_str(), dest.c_str());
}

void IntervalGenerator::MergeFiles(string s1, string s2, string d) {
    FILE* f1 = fopen(s1.c_str(), "r");
    FILE* f2 = fopen(s2.c_str(), "r");
    FILE* fd = fopen(d.c_str(), "w");
    
    int f1Read = 0, f2Read = 0;
    double toAdd[3], f1data[3], f2data[3];
    bool f1More, f2More;
    
    // Initialize the data:
    f1More = ReadData(f1, f1data);
    f2More = ReadData(f2, f2data);
    
    if (f1data[0] < f2data[0]) CopyData(toAdd, f1data);
    else CopyData(toAdd, f2data);
    unsigned counter = 0;
    
    while(true) {
        counter++;
        
        if (f1More && f1data[0] == toAdd[0]) {
            if (f1data[1] > toAdd[1]) toAdd[1] = f1data[1];
            if (f1data[2] < toAdd[2]) toAdd[2] = f1data[2];
            f1More = ReadData(f1, f1data);
            f1Read++;
            continue;
        }
        if (f2More && f2data[0] == toAdd[0]) {
            if (f2data[1] > toAdd[1]) toAdd[1] = f2data[1];
            if (f2data[2] < toAdd[2]) toAdd[2] = f2data[2];
            f2More = ReadData(f2, f2data);
            f2Read++;
            continue;
        }
        
        // At this point, both f1data[0] and f2data[0] > toAdd[0]. I need to
        // add toAdd[0] to fd file.
        fwrite(toAdd, sizeof(double), 3, fd);
        
        // Now we need to decide to add either f1data or f2data to toAdd:
        if (!f1More && !f2More) break;
        
        if (f1More && !f2More) {
            CopyData(toAdd, f1data);
            f1More = ReadData(f1, f1data);
            f1Read++;
        } else if (!f1More && f2More) {
            CopyData(toAdd, f2data);
            f2More = ReadData(f2, f2data);
            f2Read++;
        } else if (f1data[0] < f2data[0]) {
            CopyData(toAdd, f1data);
            f1More = ReadData(f1, f1data);
            f1Read++;
        } else {
            CopyData(toAdd, f2data);
            f2More = ReadData(f2, f2data);
            f2Read++;
        }
    }
    
    fclose(f1);
    fclose(f2);
    fclose(fd);
}

void IntervalGenerator::ComputeReducedIntervals(unsigned long long xlow,
                                                unsigned long long xhigh,
                                                FILE* file) {
    if (xlow > xhigh) {
        xlow = 0x0llu;
        xhigh = 0x100000000llu;
    }
    
    unsigned long long int inputX;
    for (inputX = xlow; inputX < xhigh; inputX++) {
        posit32 input;
        input.value = inputX;
        ComputeReducedInterval(input, file);
    }
}

void IntervalGenerator::ComputeReducedInterval(posit32 input, FILE* file) {
    // For each input, determine if it's special case or not. If it is, then
    // we continue to the next input
    posit32 specialCaseResult;
    if (ComputeSpecialCase(input, specialCaseResult)) return;
    
    double inputInDouble = input.toDouble();
    
    // Compute the correctly rounded result
    posit32 corrResult = MpfrCalculateFunction(input);
    
    // Compute rounding interval
    double roundingLb, roundingUb;
    CalculateInterval(corrResult, roundingLb, roundingUb);
    
    // Compute reduced input
    double reducedInput = RangeReduction(inputInDouble);
    
    // Get the initial guess for Lb and Ub
    double guessLb, guessUb;
    GuessInitialLbUb(inputInDouble, roundingLb, roundingUb,
                     reducedInput, guessLb, guessUb);
    
    // 6. In a while loop, keep increasing lb and ub using binary search
    //    method to find largest reduced interval
    double redIntLb, redIntUb, tempResult;
    bool lbIsSpecCase = false, ubIsSpecCase = false;

    // Determine if there are any special case reduced interval lb/ub
    SpecCaseRedInt(inputInDouble, guessLb, lbIsSpecCase, redIntLb,
                   guessUb, ubIsSpecCase, redIntUb);
    
    // If lb is not a special case, then we start from guessLb and try to
    // lower the lower bound as much as we can
    if (!lbIsSpecCase) {
        // Check if we can lower the lower bound more
        tempResult = OutputCompensation(inputInDouble, guessLb);
        // If the initial guess puts us outside of rounding interval, there is
        // nothing more we can do
        if (tempResult < roundingLb || tempResult > roundingUb) {
            CalcRedIntErrorMsg1(input, roundingLb, roundingUb,
                                guessLb, guessUb, tempResult);
        }
        // Otherwise, we keep lowering lb and see if we are still inside the
        // rounding interval
        unsigned long long step = 0x1000000000000llu;
        while(step > 0) {
            doubleX dx;
            dx.d = guessLb;
            if (dx.d >= 0) dx.x -= step;
            else dx.x += step;
            
            tempResult = OutputCompensation(inputInDouble, dx.d);
            
            if (tempResult >= roundingLb && tempResult <= roundingUb) {
                // It's safe to lower the lb
                guessLb = dx.d;
            } else {
                // Otherwise decrease the step by half
                step /= 2;
            }
        }
        
        // Finally, set redIntLb
        redIntLb = guessLb;
    }
    
    // Similarly for lb, we do the same thing for ub
    if (!ubIsSpecCase) {
        // Check if we can increase the upper bound more
        tempResult = OutputCompensation(inputInDouble, guessUb);
        // If the initial guess puts us outside of rounding interval, there is
        // nothing more we can do
        if (tempResult < roundingLb || tempResult > roundingUb) {
            CalcRedIntErrorMsg1(input, roundingLb, roundingUb,
                                guessLb, guessUb, tempResult);
        }
        // Otherwise, we keep lowering lb and see if we are still inside the
        // rounding interval
        unsigned long long step = 0x1000000000000llu;
        while(step > 0) {
            doubleX dx;
            dx.d = guessUb;
            if (dx.d >= 0) dx.x += step;
            else dx.x -= step;
            
            tempResult = OutputCompensation(inputInDouble, dx.d);
            if (tempResult >= roundingLb && tempResult <= roundingUb) {
                // It's safe to lower the lb
                guessUb = dx.d;
            } else {
                // Otherwise decrease the step by half
                step /= 2;
            }
        }
        
        // Finally, set redIntLb
        redIntUb = guessUb;
    }
    
    // Save reduced input, lb, and ub to files.
    fwrite(&reducedInput, sizeof(double), 1, file);
    fwrite(&redIntLb, sizeof(double), 1, file);
    fwrite(&redIntUb, sizeof(double), 1, file);
}

posit32 IntervalGenerator::FromMPFR(mpfr_t _mval) {
    posit32 rv;
    // Check for Really special cases
    if (mpfr_nan_p(_mval) != 0) { rv.value = 0x80000000; return rv; }
    if (mpfr_inf_p(_mval) != 0) { rv.value = 0x80000000; return rv; }
    if (mpfr_cmp_d(_mval, 0.0) == 0) { rv.value = 0; return rv; }
    
    // Check for values without fraction bits:
    if (mpfr_cmp_d(_mval, 0) > 0) {
        // Any value smaller than this hast at least 1 fraction bit
        if (mpfr_cmp_d(_mval, ldexp(1.75, 107)) >= 0) { //1.75 * 2^107
            if (mpfr_cmp_d(_mval, ldexp(1.0, 118)) > 0) { rv.value = 0x7FFFFFFF; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.0, 115)) >= 0) { rv.value = 0x7FFFFFFE; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.0, 113)) > 0) { rv.value = 0x7FFFFFFD; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 111)) >= 0) { rv.value = 0x7FFFFFFC; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 110)) > 0) { rv.value = 0x7FFFFFFB; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 109)) >= 0) { rv.value = 0x7FFFFFFA; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, 108)) > 0) { rv.value = 0x7FFFFFF9; return rv; }
            rv.value = 0x7FFFFFF8; return rv;
        }
        if (mpfr_cmp_d(_mval, ldexp(1.25, -108)) <= 0) {
            if (mpfr_cmp_d(_mval, ldexp(1.0, -118)) < 0) { rv.value = 0x00000001; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.0, -115)) <= 0) { rv.value = 0x00000002; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.0, -113)) < 0) { rv.value = 0x00000003; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -112)) <= 0) { rv.value = 0x00000004; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -111)) < 0) { rv.value = 0x00000005; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -110)) <= 0) { rv.value = 0x00000006; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(1.5, -109)) < 0) { rv.value = 0x00000007; return rv; }
            rv.value = 0x00000008; return rv;
        }
    } else {
        if (mpfr_cmp_d(_mval, ldexp(-1.75, 107)) <= 0) { //1.75 * 2^107
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 118)) < 0) { rv.value = 0x80000001; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 115)) <= 0) { rv.value = 0x80000002; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, 113)) < 0) { rv.value = 0x80000003; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 111)) <= 0) { rv.value = 0x80000004; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 110)) < 0) { rv.value = 0x80000005; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 109)) <= 0) { rv.value = 0x80000006; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, 108)) < 0) { rv.value = 0x80000007; return rv; }
            rv.value = 0x80000008; return rv;
        }
        if (mpfr_cmp_d(_mval, ldexp(-1.25, -108)) >= 0) {
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -118)) > 0) { rv.value = 0xFFFFFFFF; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -115)) >= 0) { rv.value = 0xFFFFFFFE; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.0, -113)) > 0) { rv.value = 0xFFFFFFFD; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -112)) >= 0) { rv.value = 0xFFFFFFFC; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -111)) > 0) { rv.value = 0xFFFFFFFB; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -110)) >= 0) { rv.value = 0xFFFFFFFA; return rv; }
            if (mpfr_cmp_d(_mval, ldexp(-1.5, -109)) > 0) { rv.value = 0xFFFFFFF9; return rv; }
            rv.value = 0xFFFFFFF8; return rv;
        }
    }
    
    long exp;
    double fr = mpfr_get_d_2exp(&exp, _mval, MPFR_RNDN);
    long origExp = exp;
    fr *= 2;
    exp--;
    
    if (exp < 0) {
        exp *= -1;
        exp--;
    }
    
    exp >>= 2; //(#regime - 1)
    long p = 28 - exp;
    mpfr_t r;
    mpfr_init2(r, p);
    mpfr_set(r, _mval, MPFR_RNDN);
    double retVal = mpfr_get_d(r, MPFR_RNDN);
    mpfr_clear(r);
    rv = retVal;
    return rv;
}

/*################################################
 Helper function implementation
 ################################################*/
double convertPositToDouble(uint64_t ps, uint64_t nbit, uint64_t es) {
    // Check for special cases:
    if (ps == 0) return 0.0;
    if (ps == (unsigned)(1lu << (nbit - 1lu))) return NAN;

    uint64_t bitsAvail = nbit;

    // (1) Get Sign bit: Logical shift right by (nbit - 1)
    uint64_t sign = ps >> (nbit - 1lu);
    bitsAvail--;

    // (1.5) If Sign bit is 1, perform two's complement
    if (sign == 1) {
        ps = -ps;
        ps = (ps << (64lu - nbit)) >> (64lu - nbit);
    }

    // (2) Get regime bits:
    // Move regime+exponent+fraction bits all the way to the left.
    uint64_t num_regime = 0lu;
    uint64_t temp = ps << (64lu - bitsAvail);
    uint64_t regime_sign = temp >> 63lu;

    while (bitsAvail > 0lu && (temp >> 63lu) == regime_sign) {
        temp = temp << 1lu;
        num_regime++;
        bitsAvail--;
    }

    if (bitsAvail > 0lu) {
        temp = temp << 1lu;
        bitsAvail--;
    }
    
    // (3) Get exponent bits:
    uint64_t shrAmount = 64lu - es;
    uint64_t exp = shrAmount > 63lu ? 0lu : temp >> (64lu - es);

    if (bitsAvail > es) bitsAvail -= es;
    else bitsAvail = 0lu;

    // (4) Get fraction bits:
    // whatever number of bits available is the number of fractions we have.
    uint64_t fraction = (bitsAvail == 0lu) ? 0lu : (ps << (64lu - bitsAvail)) >> (64lu - bitsAvail);

    // Put it all together:
    // (1) sign
    double result = (sign == 0lu) ? 1.0 : -1.0;

    // (2) regime:
    double useed = pow(2.0, pow(2.0, es));
    double regime = (regime_sign == 0lu) ? (-1.0 * num_regime) : (num_regime - 1.0);
    result = result * pow(useed, regime);

    // (3) exponent:
    result = result * pow(2.0, exp);

    // (4) fraction:
    uint64_t fraction64 = fraction;
    fraction64 = fraction64 << (52lu - bitsAvail);
    uint64_t * presult = (uint64_t *)&result;
    *presult = (*presult) | fraction64;

    return result;
}

void CalculateInterval(posit32 py, double& _lb, double& _ub) {
    // Only 0 rounds to 0.
    if (py == 0) {
        _lb = 0.0;
        _ub = 0.0;
        return;
    }
    
    uint64_t hex = py.value;
    hex <<= 1lu;
    doubleX lb, ub;
    
    bool roundAway = false;
    if ((py.value & 0x1) == 0x1) roundAway = true;
    
    if (py > 0) {
        lb.d = convertPositToDouble(hex - 1, 33, 2);
        ub.d = convertPositToDouble(hex + 1, 33, 2);
        
        if (roundAway) {
            lb.x++;
            ub.x--;
        }
        
        if (py.value == 0x1) {
            // If py is positive minpos, then lower bound is > 0
            lb.x = 0x0000000000000001;
        } else if (py.value == 0x7FFFFFFF) {
            // If py is positive maxpos, then upper bound is < infinity
            ub.x = 0x7FEFFFFFFFFFFFFF;
        }
    } else {
        lb.d = convertPositToDouble(hex - 1, 33, 2);
        ub.d = convertPositToDouble(hex + 1, 33, 2);
        
        if (roundAway) {
            lb.x--;
            ub.x++;
        }
        
        if (py.value == 0xFFFFFFFF) {
            // If py is negative minpos, then upper bound is < 0
            ub.x = 0x8000000000000001;
        } else if (py.value == 0x80000001) {
            // If py is positive maxpos, then lower bound is > infinity
            lb.x = 0xFFEFFFFFFFFFFFFF;
        }
    }
    
    _lb = lb.d;
    _ub = ub.d;
    
    return;
}

void CalcRedIntErrorMsg1(posit32 input, double roundingLb, double roundingUb,
                         double guessLb, double guessUb, double tempResult) {
    printf("Initial guess resulted in a value outside of rounding interval\n");
    printf("Diagnostics:");
    printf("Input x = %.100e\n", input.toDouble());
    printf("Rounding interval:\n");
    printf("lb      = %.100e\n", roundingLb);
    printf("ub      = %.100e\n", roundingUb);
    printf("Initial guess:\n");
    printf("lb      = %.100e\n", guessLb);
    printf("ub      = %.100e\n", guessUb);
    printf("output  = %.100e\n", tempResult);
    exit(0);
}

string GetNewFileName(string tfileName) {
    fileIndex++;
    return tfileName + "_temp" + std::to_string(fileIndex);
}

void SaveIntervalsToAFile(std::map<double, IntData> intervals,
                          string newFileName) {
    
    std::map<double, IntData>::iterator it;
    FILE* tf = fopen(newFileName.c_str(), "w");
    for (it = intervals.begin(); it != intervals.end(); it++) {
        fwrite(&it->first, sizeof(double), 1, tf);
        fwrite(&it->second.lb, sizeof(double), 1, tf);
        fwrite(&it->second.ub, sizeof(double), 1, tf);
    }
    fclose(tf);
}

void CopyData(double dest[3], double source[3]) {
    for (int i = 0; i < 3; i++) dest[i] = source[i];
}

bool ReadData(FILE* f, double dest[3]) {
    size_t s = fread(dest, sizeof(double), 3, f);
    if (s == 0) return false;
    if (s == 3) return true;
    printf("ReadData needs to read 3 * double data. Seems like we couldn't.\n");
    exit(0);
}
