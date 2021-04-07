#include "Helper.h"
#include "PolyFinder.hpp"
#include "IntervalRange.hpp"
#include <map>

#define PI_DOUBLE 3.1415926535897932384626433832795028841971693993751058209749445923078164062

using namespace std;

// What is the method used to generate polynomial?
// FULL: compute intervals for ALL inputs
// _sample: sample some inputs, create interval for it, and generate
// polynomial. If the polynomial is not accurate for some inputs, then add
// more inputs to the polynomial.
typedef enum _method_t { FULL, SAMPLE } method_t;
// How should we pick the initial samples?
// CHEBYSHEV_NODE: pick chebyshev nodes from sampleLowBound to
// sampleUpperBound.
typedef enum _initial_sample_t { CHEBYSHEV_NODE } initial_sample_t;

class MapData {
    public :
    double lb;
    double ub;
};

template <class T, class E>
class PolySynth {
    public :
    
    // Variables
    shared_ptr<IntervalRange> intervals;
    unique_ptr<PolyFinder> poly;
    method_t method;
    uint64_t sampleSize;
    double sampleLowBound;
    double sampleUpperBound;
    
    // Constructor
    PolySynth(method_t _m = FULL, uint64_t _ss = 0);
    void SetUpSamplingOption(double, double);
    
    // Functions called by users
    void CalcIntervals();
    std::map<double, unique_ptr<MapData>> CalcSomeIntervalsUsingMap(uint32_t, uint32_t);
    void PerformErrorAnalysis();
    bool TestAndAddSamplePoints();
    
    // Helper functions for computing polynomials
    void ResetPolynomials(void);
    void FindPolynomials(vector<int>);
    void FindPolynomialOnce(vector<int>);
    void FindPolynomialsUntil(vector<int>, int);
    void FindPolynomialsUntilBefore(vector<int>, double);
    
    private :
    void CalcFullIntervals(void);
    void CalcSampleIntervals(void);
    
    void CalcOneInterval(T);
    void GetChebyshevSample(void);
    void CorrectIntervalLimit(T, double&, double&, double);
    T ComputeFunction(T);
    void IntervalSanityCheck(T, T, double, double, double);
    void PrintErrorAnalysis(T, T, T);
};

template <class T, class E>
PolySynth<T, E>::PolySynth(method_t _m, uint64_t _ss) {
    intervals = std::shared_ptr<IntervalRange>(nullptr);
    poly = std::unique_ptr<PolyFinder>(nullptr);
    method = _m;
    sampleSize = _ss;
}

template <class T, class E>
void PolySynth<T, E>::SetUpSamplingOption(double _slb, double _sub) {
    sampleLowBound = _slb;
    sampleUpperBound = _sub;
}

// Functions called by users
template <class T, class E>
void PolySynth<T, E>::CalcIntervals() {
    if (method == method_t::FULL) CalcFullIntervals();
    else if (method == method_t::SAMPLE) CalcSampleIntervals();
}

template <class T, class E>
void PolySynth<T, E>::CalcSampleIntervals() {
    GetChebyshevSample();
}

template <class T, class E>
void PolySynth<T, E>::CalcFullIntervals() {
    if (!intervals) intervals = std::make_shared<IntervalRange>();
    T x = 0.0;
    uint32_t upperLimit;
    
    if constexpr (std::is_same_v<T, bfloat16>) upperLimit = 0xFF82;
    else if constexpr (std::is_same_v<T, posit16>) upperLimit = 0x10000;
    else if constexpr (std::is_same_v<T, float>) upperLimit = 0xFF800002;
    
    for (uint32_t i = 0x0; i < upperLimit; i++) {
        Helper<T>::HexToValue(x, i);
        CalcOneInterval(x);
    }
}

template <class T, class E>
std::map<double, unique_ptr<MapData>>
PolySynth<T, E>::CalcSomeIntervalsUsingMap(uint32_t lower, uint32_t upper) {
    printf("Hello!\n");
    std::map<double, unique_ptr<MapData>> intervalMap;
    T x = 0.0;
    
    for (uint32_t i = lower; i <= upper; i++) {
        Helper<T>::HexToValue(x, i);
        T res;
        double lb, ub, intPart;
        if (E::ComputeSpecialCase(x, res)) {
            if (i % 100 == 0) {
                printf("i = %u\r", i);
                fflush(stdout);
            }
            continue;
        }
        double reducedX = E::RangeReduction(x, intPart);
        T by = E::MpfrCalculateFunction(x);
        Helper<T>::CalculateInterval(by, lb, ub);
        CorrectIntervalLimit(by, lb, ub, intPart);
        IntervalSanityCheck(x, by, lb, ub, intPart);
        
        
        // Find reducedX;
        std::map<double, unique_ptr<MapData>>::iterator it;
        it = intervalMap.find(reducedX);
        if (it != intervalMap.end()) {
            // We found it
            MapData& temp = *intervalMap[reducedX];
            if (lb > temp.lb) temp.lb = lb;
            if (ub < temp.ub) temp.ub = ub;
        } else {
            // There is nothing with it
            unique_ptr<MapData> temp = make_unique<MapData>();
            temp->lb = lb;
            temp->ub = ub;
            intervalMap[reducedX] = std::move(temp);
        }
        
        if (i % 100 == 0) {
            printf("i = %u\r", i);
            fflush(stdout);
        }
    }
    printf("\n");
    printf("Size of the map: %lu\n", intervalMap.size());
    return intervalMap;
}

template <class T, class E>
void PolySynth<T, E>::CalcOneInterval(T x) {
    T res;
    double lb, ub, intPart;
    if (E::ComputeSpecialCase(x, res)) return;
    double reducedX = E::RangeReduction(x, intPart);
    T by = E::MpfrCalculateFunction(x);
    Helper<T>::CalculateInterval(by, lb, ub);
    CorrectIntervalLimit(by, lb, ub, intPart);
    IntervalSanityCheck(x, by, lb, ub, intPart);
    intervals->AddInterval(reducedX, lb, ub);
}

template <class T, class E>
void PolySynth<T, E>::GetChebyshevSample() {
    if (!intervals) {
        printf("Recreating?\n");
        intervals = std::make_shared<IntervalRange>();
    }
    T x;
    double term1 = (sampleUpperBound + sampleLowBound) * 0.5;
    double term2 = (sampleUpperBound - sampleLowBound) * 0.5;
    
    for (int i = sampleSize; i > 0; i--) {
        double inside = (i - 0.5) / sampleSize * PI_DOUBLE;
        double dx = term1 + term2 * cos(inside);
        x = dx;
        T y;
        if (!E::ComputeSpecialCase(x, y)) CalcOneInterval(x);
    }
    printf("Done\n");
}

// Correctly identify interval limit of by in double precision.
template <class T, class E>
void PolySynth<T, E>::CorrectIntervalLimit(T by, double& lb, double& ub,
                                     double modifier) {
    bool flip = E::FlipLbAndUb(modifier);
    lb = E::ReverseRangePropagation(lb, modifier);
    ub = E::ReverseRangePropagation(ub, modifier);
    
    // Check if lb rounds correctly to by. Otherwise, reduce range.
    T testlb = E::RangePropagation(lb, modifier);
    while (by != testlb) {
        doubleX lbX;
        lbX.d = lb;
        if ((lbX.d >= 0) ^ flip) lbX.x = lbX.x + 1;
        else lbX.x = lbX.x - 1;
        lb = lbX.d;
        testlb = E::RangePropagation(lb, modifier);
    }
    
    // Check if ub rounds correctly to by. Otherwise, reduce range.
    T testub = E::RangePropagation(ub, modifier);
    while (by != testub) {
        doubleX ubX;
        ubX.d = ub;
        if ((ubX.d >= 0) ^ flip) ubX.x = ubX.x - 1;
        else ubX.x = ubX.x + 1;
        ub = ubX.d;
        testub = E::RangePropagation(ub, modifier);
    }
    
    {
        // Now check if we can go larger!
        doubleX lbX, ubX;
        unsigned long long counter = 0;
        unsigned long long step = 1073741824;
        while (true) {
            lbX.d = lb;
            ubX.d = ub;
            if (lbX.x < 0x8000000000000000) lbX.x -= step;
            else lbX.x += step;
            if (ubX.x < 0x8000000000000000) ubX.x += step;
            else ubX.x -= step;
            
            T blb = E::RangePropagation(lbX.d, modifier);
            T bub = E::RangePropagation(ubX.d, modifier);
            if (by == blb && by != 0.0) {
                lb = lbX.d;
            } else if (by == bub && by != 0.0) {
                ub = ubX.d;
            } else if (step <= 1) {
                break;
            }
            else {
                step /= 2;
            }
            /*
            printf("lb  = %.100e\n", lbX.d);
            printf("ub  = %.100e\n", ubX.d);
            printf("blb = %.100e\n", blb);
            printf("by  = %.100e\n", by);
            printf("bub = %.100e\n", bub);
             */
            counter += step;
            //printf("We can go larger! (%llu)\r", counter);
        }
        //printf("\n");
    }
    
    if (E::FlipLbAndUb(modifier)) {
        swap(lb, ub);
    }
}

template <class T, class E>
T PolySynth<T, E>::ComputeFunction(T x) {
    double intPart, y;
    double reduced = E::RangeReduction(x, intPart);
    y = poly->PolyEval(reduced);
    return E::RangePropagation(y, intPart);
}

template <class T, class E>
bool PolySynth<T, E>::TestAndAddSamplePoints() {
    std::vector<double> wrongRedInputs;
    wrongRedInputs.resize(5);
    uint64_t wrongCount = 0, count = 0, upperLimit;
    double lb, ub, intPart;
    T x, y, my;
    
    if constexpr (std::is_same_v<T, bfloat16>) upperLimit = 0x10000;
    else if constexpr (std::is_same_v<T, posit16>) upperLimit = 0x10000;
    else if constexpr (std::is_same_v<T, float>) upperLimit = 0x100000000;
    
    count = 0;
    for (; count < upperLimit; count++) {
        Helper<T>::HexToValue(x, count);
        if (E::ComputeSpecialCase(x, y)) goto TestAndAddSamplePoints_message;
        y = ComputeFunction(x);
        my = E::MpfrCalculateFunction(x);
        if (my != my && y != y) goto TestAndAddSamplePoints_message;
        
        if (my != y) {
            if (wrongCount < 5) {
                wrongRedInputs[wrongCount] = E::RangeReduction(x, intPart);
            }
            wrongCount++;
            CalcOneInterval(x);
        }
        
        TestAndAddSamplePoints_message:
        if (count % 100000 == 0) {
            printf("Adding %lld/%lld values to the sample pool. (%lu)\r", wrongCount, count, intervals->intervals.size());
            fflush(stdout);
        }
    }
    
    printf("Adding %lld/%lld values to the sample pool\n", wrongCount, count);
    printf("Total size of sample intervals: %lu\n",
           intervals->intervals.size());
    
    uint64_t printCount = wrongCount > 5 ? 5 : wrongCount;
    printf("List of first 5 reduced inputs that created wrong result:\n");
    for (int i = 0; i < printCount; i++) {
        printf("redX = %.100e\n", wrongRedInputs[i]);
        
        unique_ptr<Interval> info = make_unique<Interval>();
        info->xtrans = wrongRedInputs[i];
        
        auto comparer = [&](const unique_ptr<Interval>& left,
                            const unique_ptr<Interval>& right) {
            return left->xtrans < right->xtrans;
        };
        auto insertPos = lower_bound(intervals->intervals.begin(),
                                     intervals->intervals.end(),
                                     info, comparer);
        printf("lb   = %.100e\n", (*insertPos)->lb);
        printf("ub   = %.100e\n", (*insertPos)->ub);
        printf("\n");
    }
    
    return wrongCount != 0;
}

template <class T, class E>
void PolySynth<T, E>::ResetPolynomials() {
    if (!poly) poly = make_unique<PolyFinder>(intervals);
    poly->ResetPiecewise();
}

template <class T, class E>
void PolySynth<T, E>::PerformErrorAnalysis() {
    printf("STARTING ERROR ANALYSIS\n");
    uint64_t wrongCount = 0, count = 0, upperLimit;
    T x, y, my;
    
    if constexpr (std::is_same_v<T, bfloat16>) upperLimit = 0x10000;
    else if constexpr (std::is_same_v<T, posit16>) upperLimit = 0x10000;
    else if constexpr (std::is_same_v<T, float>) upperLimit = 0x100000000;
    
    for (; count < upperLimit; count++) {
        Helper<T>::HexToValue(x, count);
        if (E::ComputeSpecialCase(x, y)) continue;
        y = ComputeFunction(x);
        my = E::MpfrCalculateFunction(x);
        if (my != my && y != y) continue;
        if (my != y) {
            wrongCount++;
            PrintErrorAnalysis(x, my, y);
        }
        
        if ((count % 1000000) == 0) {
            printf("Found %lld/%lld values that did not calculate correctly\r",
                   wrongCount, count);
            fflush(stdout);
        }
    }
    
    printf("FOUND %lld/%lld VALUES THAT DID NOT CALCULATE CORRECTLY\n",
           wrongCount, count);
}

template <class T, class E>
void PolySynth<T, E>::PrintErrorAnalysis(T x, T my, T y) {
    printf("Input x = %.100e value is not right:\n", Helper<T>::ConvertToDouble(x));
    printf("\tinput           = %.100e (%x)\n",
           Helper<T>::ConvertToDouble(x), Helper<T>::GetHexRep(x));
    printf("\tcorrect result  = %.100e (%x)\n",
           Helper<T>::ConvertToDouble(my), Helper<T>::GetHexRep(my));
    printf("\tcomputed result = %.100e (%x)\n",
           Helper<T>::ConvertToDouble(y), Helper<T>::GetHexRep(y));
    printf("\n");
}

// Helper functions for computing polynomials
// For all the intervals, identify piecewise polynomial of degree pow.
template <class T, class E>
void PolySynth<T, E>::FindPolynomials(vector<int> pow) {
    if (!poly) poly = make_unique<PolyFinder>(intervals);
    poly->FindPolynomials(pow);
}

// From the beginning of the intervals, identify one polynomial of degree pow.
// If pow is not sufficient to identify a polynomial that satisfies all intervals,
// it will try to include as many intervals as possible.
template <class T, class E>
void PolySynth<T, E>::FindPolynomialOnce(vector<int> pow) {
    if (!poly) poly = make_unique<PolyFinder>(intervals);
    poly->FindPolynomialOnce(pow);
}

template <class T, class E>
void PolySynth<T, E>::FindPolynomialsUntil(vector<int> pow, int index) {
    if (!poly) poly = make_unique<PolyFinder>(intervals);
    poly->FindPolynomialsUntil(pow, index);
}

template <class T, class E>
void PolySynth<T, E>::FindPolynomialsUntilBefore(vector<int> pow, double val) {
    if (!poly) poly = make_unique<PolyFinder>(intervals);
    poly->FindPolynomialsUntilBefore(pow, val);
}

// Use this to quickly check whether the calculated interval makes sense even.
template <class T, class E>
void PolySynth<T, E>::IntervalSanityCheck(T x, T by, double lb,
                                    double ub, double modifier) {
    T blb = E::RangePropagation(lb, modifier);
    T bub = E::RangePropagation(ub, modifier);
    // lb should be < ub
    // rounded lb and ub should be equal to by.
    if (lb > ub || by != blb || by != bub) {
        printf("IntervalSanityCheck: something went wrong\n");
        printf("input      = %.30e (%x)\n",
               Helper<T>::ConvertToDouble(x),
               Helper<T>::GetHexRep(x));
        printf("correct y  = %.30e (%x)\n",
               Helper<T>::ConvertToDouble(by),
               Helper<T>::GetHexRep(by));
        printf("lb         = %.30e (%llx)\n", lb, *((uint64_t *)&lb));
        printf("ub         = %.30e (%llx)\n", ub, *((uint64_t *)&ub));
        printf("rounded lb = %.30e (%x)\n",
               Helper<T>::ConvertToDouble(blb),
               Helper<T>::GetHexRep(blb));
        printf("rounded ub = %.30e (%x)\n",
               Helper<T>::ConvertToDouble(bub),
               Helper<T>::GetHexRep(bub));
    }
}
