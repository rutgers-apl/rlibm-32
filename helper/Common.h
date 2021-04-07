#pragma once
#include "mpfr.h"

using namespace std;

typedef union {
    float f;
    unsigned x;
} floatX;

typedef union {
    double d;
    unsigned long long int x;
} doubleX;

struct IntData {
    double lb;
    double ub;
};
