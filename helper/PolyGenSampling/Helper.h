#pragma once
#include "softposit_cpp.h"
#include "bfloat16.hpp"

using namespace std;

template <class T>
class Helper {
    public :
    static inline double ConvertToDouble(T x);
    static inline uint32_t GetHexRep(T x);
    static inline void HexToValue(T& v, uint32_t h);
    static void CalculateInterval(T, double&, double&);
    
    private :
    static double convertPositToDouble(uint64_t, uint64_t, uint64_t);
};

// Static functions for rounding and identifying intervals:
template <>
void Helper<bfloat16>::CalculateInterval(bfloat16 by, double& _lb, double& _ub) {
    // If by == 0, then the interval is between -minbfloat/2 to minbfloat/2
    if ((float)by == 0) {
        floatint fi;
        fi.x = 0x1;
        fi.x <<= 15;
        _ub = (double)fi.f;
        _lb = (double)-fi.f;
        return;
    }
    
    // Otherwise, add another bit at the end and add 1 / remove 1
    floatint fi, lbfi, ubfi;
    fi.x = by.val;
    
    // We need to detect whether tie values will round towards or round away from by
    bool roundAway = false;
    if ((fi.x & 0x1) == 0x1) roundAway = true;
    
    fi.x <<= 16;
    // If value is positive then _lb -> -0x8000, _ub -> +0x8000
    // If value is negative then _lb -> +0x8000, _ub -> -0x8000
    if (fi.f > 0) {
        lbfi.x = fi.x - 0x8000;
        ubfi.x = fi.x + 0x8000;
        
        doubleint lbdx, ubdx;
        lbdx.d = (double)lbfi.f;
        ubdx.d = (double)ubfi.f;

        
        // If the value rounds away from by, then reduce the range
        if (roundAway) {
            lbdx.x++;
            ubdx.x--;
        }
        
        _lb = lbdx.d;
        _ub = ubdx.d;
        return;
    }
    
    lbfi.x = fi.x + 0x8000;
    ubfi.x = fi.x - 0x8000;
    
    doubleint lbdx, ubdx;
    lbdx.d = (double)lbfi.f;
    ubdx.d = (double)ubfi.f;
    
    // If the value rounds away from by, then reduce the range
    if (roundAway) {
        lbdx.x--;
        ubdx.x++;
    }
    
    _lb = lbdx.d;
    _ub = ubdx.d;
    return;
}

template <>
void Helper<posit16>::CalculateInterval(posit16 py, double& _lb, double& _ub) {
    // Only 0 rounds to 0.
    if (py == 0) {
        _lb = 0.0;
        _ub = 0.0;
        return;
    }
    
    uint32_t hex = py.value;
    hex <<= 1;
    doubleint lb, ub;
    
    bool roundAway = false;
    if ((py.value & 0x1) == 0x1) roundAway = true;
    
    if (py > 0) {
        lb.d = convertPositToDouble(hex - 1, 17, 1);
        ub.d = convertPositToDouble(hex + 1, 17, 1);
        
        if (roundAway) {
            lb.x++;
            ub.x--;
        }
        
        if (py.value == 0x1) {
            // If py is positive minpos, then lower bound is > 0
            lb.x = 0x0000000000000001;
        } else if (py.value == 0x7FFF) {
            // If py is positive maxpos, then upper bound is < infinity
            ub.x = 0x7FEFFFFFFFFFFFFF;
        }
    } else {
        lb.d = convertPositToDouble(hex - 1, 17, 1);
        ub.d = convertPositToDouble(hex + 1, 17, 1);
        
        if (roundAway) {
            lb.x--;
            ub.x++;
        }
        
        if (py.value == 0xFFFF) {
            // If py is negative minpos, then upper bound is < 0
            ub.x = 0x8000000000000001;
        } else if (py.value == 0x7FFF) {
            // If py is positive maxpos, then lower bound is > infinity
            lb.x = 0xFFEFFFFFFFFFFFFF;
        }
    }
    
    _lb = lb.d;
    _ub = ub.d;
    
    return;
}

template <>
void Helper<posit32>::CalculateInterval(posit32 py, double& _lb, double& _ub) {
    // Only 0 rounds to 0.
    if (py == 0) {
        _lb = 0.0;
        _ub = 0.0;
        return;
    }
    
    uint64_t hex = py.value;
    hex <<= 1lu;
    doubleint lb, ub;
    
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

// This function only works for posit of up to n = 64
// And only if the posit value is exactly representable by double.
template <class T>
double Helper<T>::convertPositToDouble(uint64_t ps, uint64_t nbit, uint64_t es) {
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

template <>
void Helper<float>::CalculateInterval(float x, double& lb, double& ub) {
    floatint xi;
    doubleint di;
    xi.f = x;
    double dx = x;
    // Take care of special cases:
    if (x == 0.0) {
        xi.x = 0x80000001;
        double lower = xi.f;
        lb = lower / 2;
        xi.x = 0x00000001;
        double upper = xi.f;
        ub = upper / 2;
        return;
    }
    
    if (x < 0.0) {
        if (xi.x == 0xFF7FFFFF) {
            double lower = -pow(2.0, 128.0);
            lb = (dx + lower) / 2;
        } else {
            xi.x++;
            double lower = xi.f;
            lb = (dx + lower) / 2;
            xi.x--;
        }
        
        xi.x--;
        double upper = xi.f;
        ub = (dx + upper) / 2;

        // Inclusive or exclusive?
        xi.f = x;
        if ((xi.x & 0x1) != 0) {
            di.d = lb;
            di.x--;
            lb = di.d;
            di.d = ub;
            di.x++;
            ub = di.d;
        }
        return;
    }
    
    // Otherwise x > 0.0
    xi.x--;
    double lower = xi.f;
    lb = (dx + lower) / 2;
    xi.x++;
    
    if (xi.x == 0x7F7FFFFF) {
        double upper = pow(2.0, 128.0);
        ub = (dx + upper) / 2;
    } else {
        xi.x++;
        double upper = xi.f;
        ub = (dx + upper) / 2;
    }
    
    // inclusive or exclusive?
    xi.f = x;
    if ((xi.x & 0x1) != 0) {
        di.d = lb;
        di.x++;
        lb = di.d;
        di.d = ub;
        di.x--;
        ub = di.d;
    }
}

template <>
inline double Helper<bfloat16>::ConvertToDouble(bfloat16 x) {
    return (double)x;
}

template <>
inline double Helper<posit16>::ConvertToDouble(posit16 x) {
    return x.toDouble();
}

template <>
inline double Helper<float>::ConvertToDouble(float x) {
    return x;
}

template <>
inline uint32_t Helper<bfloat16>::GetHexRep(bfloat16 x) {
    return x.val;
}

template <>
inline uint32_t Helper<posit16>::GetHexRep(posit16 x) {
    return x.value;
}

template <>
inline uint32_t Helper<float>::GetHexRep(float x) {
    return *((unsigned int *)&x);
}

template <>
inline void Helper<bfloat16>::HexToValue(bfloat16& v, uint32_t h) {
    v.val = h;
}

template <>
inline void Helper<posit16>::HexToValue(posit16& v, uint32_t h) {
    v.value = h;
}

template <>
inline void Helper<float>::HexToValue(float& v, uint32_t h) {
        floatint fi;
        fi.x = h;
        v = fi.f;
}
