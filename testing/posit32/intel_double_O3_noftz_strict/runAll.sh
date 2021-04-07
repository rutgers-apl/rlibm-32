#!/bin/bash
echo -e "INTEL DOUBLE: O3 -no-ftz -fp-model strict"
make -s clean
make -s

echo -e "Log"
taskset -c 12 ./Log ${ORACLEPOSITPATH}/LogOracle

echo -e "Log2"
taskset -c 12 ./Log2 ${ORACLEPOSITPATH}/Log2Oracle

echo -e "Log10"
taskset -c 12 ./Log10 ${ORACLEPOSITPATH}/Log10Oracle

echo -e "Exp"
taskset -c 12 ./Exp ${ORACLEPOSITPATH}/ExpOracle

echo -e "Exp2"
taskset -c 12 ./Exp2 ${ORACLEPOSITPATH}/Exp2Oracle

echo -e "Exp10"
taskset -c 12 ./Exp10 ${ORACLEPOSITPATH}/Exp10Oracle

echo -e "Sinh"
taskset -c 12 ./Sinh ${ORACLEPOSITPATH}/SinhOracle

echo -e "Cosh"
taskset -c 12 ./Cosh ${ORACLEPOSITPATH}/CoshOracle

make -s clean
