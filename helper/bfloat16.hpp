#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpfr.h>

union floatint{
  float f;
  unsigned int x;
};

union doubleint{
    double d;
    unsigned long long int x;
};

// In bfloat16, we assume the RNE rounding mode:
// Round to nearest tie goes to even. We have to do correct rounding
// for every cast from float/double to bfloat16.
inline unsigned short RoundFloatToBFloat16(float v) {
  floatint temp;
  temp.f = v;
  
  // There is one exception we much check: If it's NaN, make sure
  // it stays at NaN. The only case is when x111 1111 1111 1111:
  // There should not be any rounding up.
  if (((temp.x >> 16) & 0x7FFF) == 0x7FFF) {
    return temp.x >> 16;
  }
  
  // Calculate last bit, bit+1, and S bit:
  unsigned short lb = (temp.x >> 16) & 0x1;
  unsigned short bp1 = (temp.x >> 15) & 0x1;
  unsigned short sb = ((temp.x & 0x7FFF) == 0) ? 0 : 1;
  
  // Apply rounding rule
  unsigned short round = (lb & bp1) | (bp1 & sb);
  return (temp.x >> 16) + round;
}

// In bfloat16, we assume the RNE rounding mode:
// Round to nearest tie goes to even. We have to do correct rounding
// for every cast from float/double to bfloat16.
inline unsigned short RoundDoubleToBFloat16(double v) {
    doubleint temp;
    temp.d = v;
    // Take care of Infinity
    if (temp.x >= 0x47EFF00000000000 && temp.x <= 0x7FF0000000000000) {
        return 0x7F80;
    }
    if (temp.x >= 0xC7EFF00000000000 && temp.x <= 0xFFF0000000000000) {
        return 0xFF80;
    }
    
    // Take care of NaN
    if ((temp.x & 0x7FF0000000000000) == 0x7FF0000000000000) {
        return temp.x >> 48;
    }
    
    long long int exp = (temp.x >> 52) & 0x7FF;
    exp -= 1023;
    bool lb, bp1, sb;
    unsigned long long int mask = 0x1;
    unsigned short mantissa;
    unsigned short expbits;
    unsigned short signedBit = ((temp.x >> 48) & 0x8000);

    
    if (exp <= -135) {
        return (temp.x >> 48) & 0x8000;
    }
    
    if (exp == -134) {
        lb = false;
        bp1 = true;
        sb = (temp.x & ((mask << 52) - 1)) != 0;
        mantissa = 0;
        expbits = 0;
    }
    
    else if (exp == -133) {
        lb = true;
        bp1 = ((temp.x >> 51) & 0x1) == 0x1;
        sb = (temp.x & ((mask << 51) - 1)) != 0;
        mantissa = 1;
        expbits = 0;
    }
    
    else if (-132 <= exp && exp <= -127) {
        unsigned long long int shift1 = (unsigned long long int)(-exp) - 81;
        unsigned long long int shift2 = (unsigned long long int)(-exp) - 82;
        lb = ((temp.x >> shift1) & 0x1) == 0x1;
        bp1 = ((temp.x >> shift2) & 0x1) == 0x1;
        sb = (temp.x & ((mask << shift2) - 1)) != 0;
        mantissa = ((temp.x & 0x000FFFFFFFFFFFFF) | 0x0010000000000000) >> shift1;
        expbits = 0;
    }
    
    else if (exp >= -126) {
        lb = ((temp.x >> 45) & 0x1) == 0x1;
        bp1 = ((temp.x >> 44) & 0x1) == 0x1;
        sb = (temp.x & ((mask << 44) - 1)) != 0;
        mantissa = (temp.x >> 45) & 0x7F;
        expbits = (exp + 127) << 7;
    }

    // Put everything together:
    unsigned short intermediateRes = signedBit | mantissa | expbits;
    
    // Perform rounding
    if ((lb && bp1) || (bp1 && sb)) {
        intermediateRes++;
    }
    
    return intermediateRes;
}




class bfloat16 {
public :
    unsigned short val;
    bfloat16() {
        val = 0;
    }
    bfloat16(float v) {
        val = RoundFloatToBFloat16(v);
    }
  
    bfloat16(double v) {
        val = RoundDoubleToBFloat16(v);
    }
  
    bfloat16(unsigned short v) {
        val = v;
    }
  
    explicit operator float() const {
        floatint temp;
        temp.x = val;
        temp.x <<= 16;
        return temp.f;
    }

    explicit operator double() const {
        floatint temp;
        temp.x = val;
        temp.x <<= 16;
        return (double)temp.f;
    }
  
    const bool operator==(const bfloat16& other) {
        return (float)(*this) == (float)other;
    }
        
    const bool operator<(const bfloat16& other) {
        return (float)(*this) < (float)other;
    }
        
    const bool operator!=(const bfloat16& other) {
        return !(*this == other);
    }
    const bool operator<=(const bfloat16& other) {
        return (*this == other) || (*this < other);
    }
    const bool operator>(const bfloat16& other) {
        return !(*this < other) && (*this != other);
    }
    const bool operator>=(const bfloat16& other) {
        return !(*this < other);
    }
        
    const bool operator==(const float& other) {
        return (float)(*this) == other;
    }
        
    const bool operator<(const float& other) {
        return (float)(*this) < other;
    }
        
    const bool operator!=(const float& other) {
        return !(*this == other);
    }
    const bool operator<=(const float& other) {
        return (*this == other) || (*this < other);
    }
    const bool operator>(const float& other) {
        return !(*this < other) && (*this != other);
    }
    const bool operator>=(const float& other) {
        return !(*this < other);
    }

};
