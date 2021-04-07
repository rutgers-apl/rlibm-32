#!/bin/bash
echo -e "GLIBC DOUBLE: O3 -frounding-math -fsignaling-nans"
make -s clean
make -s

echo -e "Log"
taskset -c 12 ./Log ${ORACLEPATH}/LogOracle

echo -e "Log2"
taskset -c 12 ./Log2 ${ORACLEPATH}/Log2Oracle

echo -e "Log10"
taskset -c 12 ./Log10 ${ORACLEPATH}/Log10Oracle

echo -e "Exp"
taskset -c 12 ./Exp ${ORACLEPATH}/ExpOracle

echo -e "Exp2"
taskset -c 12 ./Exp2 ${ORACLEPATH}/Exp2Oracle

echo -e "Exp10"
taskset -c 12 ./Exp10 ${ORACLEPATH}/Exp10Oracle

echo -e "Sinh"
taskset -c 12 ./Sinh ${ORACLEPATH}/SinhOracle

echo -e "Cosh"
taskset -c 12 ./Cosh ${ORACLEPATH}/CoshOracle

make -s clean
