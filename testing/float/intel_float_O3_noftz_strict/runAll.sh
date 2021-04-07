#!/bin/bash
echo -e "INTEL FLOAT: O3 -no-ftz -fp-model strict"
make -s clean
make -s

echo -e "Log"
taskset -c 12 ./Log ${ORACLEPATH}/LogOracle
taskset -c 12 ./Log ${ORACLEPATH}/LogOracle
taskset -c 12 ./Log ${ORACLEPATH}/LogOracle

echo -e "Log2"
taskset -c 12 ./Log2 ${ORACLEPATH}/Log2Oracle
taskset -c 12 ./Log2 ${ORACLEPATH}/Log2Oracle
taskset -c 12 ./Log2 ${ORACLEPATH}/Log2Oracle

echo -e "Log10"
taskset -c 12 ./Log10 ${ORACLEPATH}/Log10Oracle
taskset -c 12 ./Log10 ${ORACLEPATH}/Log10Oracle
taskset -c 12 ./Log10 ${ORACLEPATH}/Log10Oracle

echo -e "Exp"
taskset -c 12 ./Exp ${ORACLEPATH}/ExpOracle
taskset -c 12 ./Exp ${ORACLEPATH}/ExpOracle
taskset -c 12 ./Exp ${ORACLEPATH}/ExpOracle

echo -e "Exp2"
taskset -c 12 ./Exp2 ${ORACLEPATH}/Exp2Oracle
taskset -c 12 ./Exp2 ${ORACLEPATH}/Exp2Oracle
taskset -c 12 ./Exp2 ${ORACLEPATH}/Exp2Oracle

echo -e "Exp10"
taskset -c 12 ./Exp10 ${ORACLEPATH}/Exp10Oracle
taskset -c 12 ./Exp10 ${ORACLEPATH}/Exp10Oracle
taskset -c 12 ./Exp10 ${ORACLEPATH}/Exp10Oracle

echo -e "Sinh"
taskset -c 12 ./Sinh ${ORACLEPATH}/SinhOracle
taskset -c 12 ./Sinh ${ORACLEPATH}/SinhOracle
taskset -c 12 ./Sinh ${ORACLEPATH}/SinhOracle

echo -e "Cosh"
taskset -c 12 ./Cosh ${ORACLEPATH}/CoshOracle
taskset -c 12 ./Cosh ${ORACLEPATH}/CoshOracle
taskset -c 12 ./Cosh ${ORACLEPATH}/CoshOracle

echo -e "Sinpi"
taskset -c 12 ./Sinpi ${ORACLEPATH}/SinpiOracle
taskset -c 12 ./Sinpi ${ORACLEPATH}/SinpiOracle
taskset -c 12 ./Sinpi ${ORACLEPATH}/SinpiOracle

echo -e "Cospi"
taskset -c 12 ./Cospi ${ORACLEPATH}/CospiOracle
taskset -c 12 ./Cospi ${ORACLEPATH}/CospiOracle
taskset -c 12 ./Cospi ${ORACLEPATH}/CospiOracle

make -s clean
