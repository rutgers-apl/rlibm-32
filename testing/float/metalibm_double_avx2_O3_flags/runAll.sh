#!/bin/bash
echo -e "CRLIBM DOUBLE: O3 -frounding-math -fsignaling-nans"
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

echo -e "Sinh"
taskset -c 12 ./Sinh ${ORACLEPATH}/SinhOracle

echo -e "Cosh"
taskset -c 12 ./Cosh ${ORACLEPATH}/CoshOracle

echo -e "Sinpi"
taskset -c 12 ./Sinpi ${ORACLEPATH}/SinpiOracle

echo -e "Cospi"
taskset -c 12 ./Cospi ${ORACLEPATH}/CospiOracle

make -s clean
