#!/bin/bash
echo -e "CRLIBM DOUBLE: O3 -frounding-math -fsignaling-nans"
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

echo -e "Sinh"
taskset -c 12 ./Sinh ${ORACLEPOSITPATH}/SinhOracle

echo -e "Cosh"
taskset -c 12 ./Cosh ${ORACLEPOSITPATH}/CoshOracle

make -s clean
