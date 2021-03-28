# rlibm-32

rlibm-32 is a math library that provides correctly rounded result for all inputs. Currently, rlibm-32 supports a number of elementary functions for float and posit32 representations. 

## Installation
To compile the math library, please follow the instructions below.
This compilation instruction conrates separate math library for each of the available representations.

### Prerequisite
If you want to compile the math library for posit32, you have to install SoftPosit. Please follow the instructions from the [SoftPosit GitLab](https://gitlab.com/cerlane/SoftPosit).

### Installation step
1. Clone the rlibm-32 repository
```
git clone https://github.com/rutgers-apl/rlibm-32.git
```

2. Create an environment variable SOFTPOSITPATH that points to the directory of SoftPosit:
```
export SOFTPOSITPATH=<path-to-softposit-directory>
```
  
3. Build the math library
  1. If you want to build all the math libraries, simply use make rule
  ```
  cd rlibm-32
  make
  ```

  2. If you want to build math libraries for each representation separately, you can use these make rule
  ```
  cd rlibm-32
  make floatmlib
  make posit32mlib
  ```
4. (Optional) Test that the math library does produce the correct value. This step requires MPFR installed.
  1. To run the correctness bench suite for all math libraries, run
  ```
  ./runLibTest.sh
  ```
  2. The correctness bench suite for math library is located in the libtest folder.
  ```
  cd libtest/float
  make
  ./runAll.sh
  ```

## USAGE
The math library will be located in the lib directory.
  * floatMathLib.a : math library for float
  * posit32MathLib.a : math library for posit32.

The header files for each library is located in the include directory:
  * float_math.h : header for float math library
  * posit32_math.h : header for posit32 math library

You can use our library in the code similar to how standard math library is used, except our function names start with "rlibm_":
```
test.cpp: 
#include "float_math.h"
int main() {
  float result = rlibm_cospi(1.5f);
  return 0;
}
```

To build the program, include the math library in the compilation command:
```
g++ test.cpp ../../lib/floatMathLib.a -lm -o test
```
Currently, rlibm uses some functions from the default math library for range reduction, such as to decompose a floating point value into the integral part and fractional part.
