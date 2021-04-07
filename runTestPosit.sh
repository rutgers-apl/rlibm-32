#!/bin/bash

echo -e "Building rlibm math library"
make -s clean
make -s

cd testing/posit32/glibc_double_O3_flags/
./runAll.sh

cd ../glibc_rlibm_O3_flags/
./runAll.sh

cd ../intel_double_O3_noftz_strict/
./runAll.sh

cd ../intel_rlibm_O3_noftz_strict/
./runAll.sh

cd ../crlibm_O3_flags/
./runAll.sh
