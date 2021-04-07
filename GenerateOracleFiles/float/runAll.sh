#!/bin/bash
mkdir -p ${ORACLEPATH}

./Log ${ORACLEPATH}/LogOracle
./Log2 ${ORACLEPATH}/Log2Oracle
./Log10 ${ORACLEPATH}/Log10Oracle
./Exp ${ORACLEPATH}/ExpOracle
./Exp2 ${ORACLEPATH}/Exp2Oracle
./Exp10 ${ORACLEPATH}/Exp10Oracle
./Sinh ${ORACLEPATH}/SinhOracle
./Cosh ${ORACLEPATH}/CoshOracle
./Sinpi ${ORACLEPATH}/SinpiOracle
./Cospi ${ORACLEPATH}/CospiOracle

