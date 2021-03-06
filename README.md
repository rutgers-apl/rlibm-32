# RLIBM-32

RLIBM-32 is both a library that provides correctly rounded result for all inputs and a collection of tools used to generate the correct polynomials. 
See the PLDI 2021 paper and its accompanying extended technical report at https://arxiv.org/pdf/2104.04043.pdf. 
It extends our RLIBM work to work with 32-bit types. If you want to know more about RLIBM, see the POPL 2021 paper at https://www.cs.rutgers.edu/~santosh.nagarakatte/papers/rlibm-popl-2021.pdf

More details on the RLIBM project is available on the RLIBM project page at https://people.cs.rutgers.edu/~sn349/rlibm/

Currently, RLIBM-32 supports a number of elementary functions for float and posit32 representations. 

### List of float functions supported by RLIBM-32
1. log(x), log2(x), log10(x)
2. exp(x), exp2(x), exp10(x)
3. sinh(x), cosh(x)
4. sinpi(x), cospi(x)

### List of posit32 functions supported by RLIBM-32
1. log(x), log2(x), log10(x)
2. exp(x), exp2(x), exp10(x)
3. sinh(x), cosh(x)


# Getting started with RLIBM-32:
There are various pre-requisites for using RLIBM-32 math library, testing it, or generating polynomials.
We describe the pre-requisites in each section. Alternatively, we have set up a docker image that contains the pre requisites and environment variables set up already. 

### Using Docker Image
1. Install docker if not already installed by following the installation documentation in this link: https://docs.docker.com/install/

2. Download the docker image

```
docker pull jpl169/rlibm-32
```
* The docker image is roughly ~6GB in size

3. Run the docker image
	
```
sudo docker run -it jpl169/rlibm-32
```

### Manual Installation
In each section (using math library, testing, generating polynomial) we list the pre-requisites and how to set up.


# How to build and use RLIBM-32 math library

### Prerequisite
If you want to compile the math library for posit32, you have to install SoftPosit. Please follow the instructions from the [SoftPosit GitLab](https://gitlab.com/cerlane/SoftPosit).

### Setup

1. Create an environment variable SOFTPOSITPATH that points to the directory of SoftPosit:
```
export SOFTPOSITPATH=<path-to-softposit-directory>
```
  
2. Build the math library
  1. If you want to build all the math libraries, simply use make rule from the root directory
  ```
  cd <path-to-rlibm-32>
  make
  ```

  2. If you want to build math libraries for each representation separately, you can use these make rule
  ```
  cd <path-to-rlibm-32>
  make floatmlib
  make posit32mlib
  ```
  
### USAGE
The math library will be located in the `lib` directory.
  * floatMathLib.a : math library for float
  * posit32MathLib.a : math library for posit32.

The header files for each library is located in the include directory:
  * `float_math.h` : header for float math library
  * `posit32_math.h` : header for posit32 math library

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
g++ test.cpp -I<path-to-rlibm-32>/include/ <path-to-rlibm-32>/lib/floatMathLib.a -lm -o test
```
Currently, RLIBM-32 uses some functions from the default math library for range reduction (i.e., to decompose a floating point value into the integral part and fractional part) so make sure to include `-lm` flag.

# Testing Correctness of RLIBM-32

### Prerequisite
To run the testing script to check for correctness of RLIBM-32, you need to have installed MPFR and SoftPosit. SoftPosit can be installed via the instructions from the [SoftPosit GitLab](https://gitlab.com/cerlane/SoftPosit).

### Setup

1. Create an environment variable SOFTPOSITPATH that points to the directory of SoftPosit:
```
export SOFTPOSITPATH=<path-to-softposit-directory>
```
  
2. Build the math library
```
cd <path-to-rlibm-32>
make
```

### Testing
1. To test the correctness of RLIBM-32's float functions, use the following command:
```
cd <path-to-rlibm-32>
make
cd rlibmCorrectnessTest/float/
./runAllParallel.sh -j <parallelism>
```
* Because the testing harness relies on MPFR math library to compute the correct result, the scripts can take hours to complete. In extreme case (sinpi(x)), it can take up to 24 hours to complete. Since there are a total of 10 float functions, we recommend parallelism of at least 4.

* Once the testing harness is complete, the results will be stored in `rlibmCorrectnessTest/float/Results/rlibm/` directory. 

2. To test the correctness of RLIBM-32's posit32 functions, use the following command:
```
cd <path-to-rlibm-32>
make
cd rlibmCorrectnessTest/posit32/
./runAllParallel.sh -j <parallelism>
```
* Because the testing harness relies on MPFR math library to compute the correct result, the scripts can take hours to complete. In extreme case (exp10(x)), it can take up to 12 hours to complete. Since there are a total of 8 posit32 functions, we recommend parallelism of at least 4.

* Once the testing harness is complete, the results will be stored in `rlibmCorrectnessTest/posit32/Results/rlibm/` directory. 


# Testing Performance of Various Math Libraries

### Prerequisite
To run the testing script to check for performance, we recommend to also install Intel compiler (icc) via [this site ](https://software.intel.com/content/www/us/en/develop/tools/oneapi/hpc-toolkit/download.html).

1. Select the appropriate operating system
2. Select "Web & Local" distribution option
3. Select Online installer
4. On the right hand side (gray background) if you scroll down, it will show the steps to install. 
  * If your OS is Linux base, then you might use the command:
```
wget https://registrationcenter-download.intel.com/akdlm/irc_nas/17427/l_HPCKit_p_2021.1.0.2684.sh
bash l_HPCKit_p_2021.1.0.2684.sh
```

5. Follow the instruction. The installer will guide you through installing intel compiler.
  a. Make sure to install "Intel?? oneAPI DPC++/C++ Compiler & Intel?? C++ Compiler Classic." You can choose to not install any other components
  b. Make sure to remember the Installation directory
  c. If it shows you any warning about requiring the "Base toolkit" you can choose to ignore it.
    * The installation will take roughly 5~10 minutes.

6. Once installation is complete, run script to set variables:
```
cd <path to intel oneAPI directory>
. setvars.sh
```

### Setup

1. Create an environment variable ICCPATH that points to the directory of intel/oneapi directory. If you did not change the installation path while installing Intel compiler, then the path to Intel oneAPI directory will most likely end with "intel/oneapi":
```
export ICCPATH=<path to Intel oneAPI directory>
```

2. Build the math library

cd <path-to-rlibm-32>

make

3. To run the testing harness, we must first generate files containing oracle results. To generate oracle files for 32-bit float functions, 
```
export ORACLEPATH=<path to directory where you want to store oracle files for float functions>
cd <path to rlibm-32 directory>
make
cd GenerateOracleFiles/float
make
./runAll.sh
```
  * This step creates a number of <function name>Oracle files inside `ORACLEPATH`. Each oracle file is 16GB(4 bytes * 2^32) and there are 10 functions which requires a total of 160GB. This step will take roughly 1 hour.

4. To generate oracle files for 32-bit posit functions, 
```
export ORACLEPOSITPATH=<path to directory where you want to store oracle files for posit32 functions>
cd <path to rlibm-32 directory>
make
cd GenerateOracleFiles/posit32
make
./runAll.sh
```
  * This step creates a number of <function name>Oracle files inside `ORACLEPOSITPATH`. Each oracle file is 16GB(4 bytes * 2^32) and there are 9 functions which requires a total of 128GB. This step will take roughly 1 hour.


### TESTING
* To run a comprehensive testing suite, which tests the performance and correctness of glibc, intel, CR-LIBM, MetaLibm, and RLIBM-32 for float functions, use the pre-assembled testing script:
```
cd <path to rlibm-32 directory>
./runTestFloat.sh
./runTestPosit.sh
```

* Each test will output two lines of result. 
  1. The first line reports the number of cycles required to compute the function for all 2^32 inputs. Thus, to compute the average, you can use the reported number and divide by 2^32. 
  2. The second number reports the number of inputs that produce wrong results.

* Individual testing configuration (glibc, intel, CR-LIBM, MetaLibm, *or* RLIBM-32) is stored in its own directory in `testing/float/` (for float functions) or `testing/posit32/` (for posit32 functions). For example, if you want to test the correctness and performance of RLIBM-32's float functions built with gcc, you can use the following commands:
```
cd <path to rlibm-32 directory>
cd testing/float/glibc_rlibm_O3_flags
./runAll.sh
```


# How to use RLIBM-32 Tool to Generate Polynomials

### Prerequisite
1. *SoftPosit:* Please follow the instructions from the [SoftPosit GitLab](https://gitlab.com/cerlane/SoftPosit).
2. *Soplex 4.0.1:* Please download soplex-4.0.1 from https://soplex.zib.de/index.php#download
* Make sure that you're downloading version 4.0.1
```
$ tar -xvf soplex-4.0.1.tar
$ cd soplex-4.0.1
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ../..
```
3. MPFR library, and zlib library (required from soplex). On Ubuntu systems, they can be installed with:
```
sudo apt-get install build-essential libgmp3-dev libmpfr-dev zlib1g zlib1g-dev
```

### Setup
Set environment variables to SoftPosit and Soplex:
```
$ export SOFTPOSITPATH=<path to SoftPosit directory>
$ export SOPLEXPATH=<path to soplex-4.0.1 directory>
```

### Generating Polynomials
There are two steps in generating polynomials: (1) Generating files containing reduced input and reduced intervals. (2) Based on the files, generate polynomials that produce results that satisfy the reduced input - interval constraints. Please note that the files containing reduced inputs and intervals are large. In extreme cases (i.e., exp10(x) for posit32), this file can be as large as ~80GB. Additionally, both the files and polynomials can take several hours (up to 24 hours for each function).

1. If you have more than 500GB of space, then you can use the existing script that automatically generates the files and polynomial. To produce the polynomials for float, use the following command:
```
cd <path to rlibm-32 directory>
./floatIntervalGen.sh
./floatFunctionGen.sh
```
The first script generates the files containing reduced inputs and intervals and puts it into the `intervals` directory. The second script generates correct polynomials for each function based on the generated files. The coefficients of the polynomials are saved into header files (`*.h`) in `functiongen/float` directory.

To produce the polynomials for posit32, use the following command:
```
cd <path to rlibm-32 directory>
./posit32FunctionGen.sh
./posit32IntervalGen.sh
```

The first script generates the files containing reduced inputs and intervals and puts it into the `intervals` directory. The second script generates correct polynomials for each function based on the generated files. The coefficients of the polynomials are saved into header files (`*.h`) in `functiongen/posit32` directory.

2. If you would like to generate polynomials for each function separately (to save space, etc) then follow the next instructions. We will use an example of generating the polynomials for ln(x) for float type. Other functions/types should be adjusted accordingly:
  a. Generate file containing reduced inputs/intervals information:
    ```
    cd <path to rlibm-32 directory>
    cd IntervalGen/float
    make
    ./Log10 FloatLog10Data
    ```
  b. Once the process finishes, use `FloatLog10Data` to generate the polynomial:
    ```
    cd <path to rlibm-32 directory>
    cd functiongen/float/
    make
    ./Log ../../IntervalGen/float/FloatLogData Log.log Log.h
    ```
   * The program requires three arguments. (1) The reduced inputs/intervals file, (2) A filename where the program writes logging information, and (3) A filename for the header file where the polynomial coefficients are stored.
   * Once the process finishes, `Log.h` can be found in `functiongen/float` and it will contain coefficients of the polynomials.






