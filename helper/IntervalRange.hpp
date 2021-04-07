#pragma once
#include <vector>

using namespace std;

// Class containing the interval information of range reduced input and its computation interval.
class Interval {
    public :
    double xtrans;
    double lb;
    double ub;
    double origLb;
    double origUb;
};

union doubleX {
    double d;
    unsigned long long int x;
};

union floatX {
    float f;
    unsigned int x;
};

class IntervalRange {
    public :
        vector<unique_ptr<Interval>> intervals;

        // Helpful functions
        void AddInterval(double, double, double);
        void AssertSanity();
        void PrintIntervals();
};
