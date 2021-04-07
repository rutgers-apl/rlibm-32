#!/bin/bash

echo -e "Building rlibm math library"
make -s clean
make -s

echo -e "Building Metalibm library"
cd external/metalibm/
make -s clean
make -s
cd ../..

cd testing/float/glibc_float_O3_flags/
./runAll.sh

cd ../glibc_double_O3_flags/
./runAll.sh

cd ../glibc_rlibm_O3_flags/
./runAll.sh

cd ../intel_float_O3_noftz_strict/
./runAll.sh

cd ../intel_double_O3_noftz_strict/
./runAll.sh

cd ../intel_rlibm_O3_noftz_strict/
./runAll.sh

cd ../crlibm_O3_flags/
./runAll.sh

cd ../metalibm_float_avx2_O3_flags/
./runAll.sh

cd ../metalibm_double_avx2_O3_flags/
./runAll.sh
