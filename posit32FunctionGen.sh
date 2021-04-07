#!/bin/bash

parallelism=3

while getopts j: flag
do
    case "${flag}" in
        j) parArg=${OPTARG};;
    esac
done

if [ "$parArg" -eq "$parArg" ] 2>/dev/null
then
   parallelism=$parArg
fi

#1. Build the function generation program
echo -e "\033[1m* Compiling function generation code\033[0m"
cd functiongen/posit32
make --silent clean
make --silent ADDTL=-w
echo -e "\033[1m\tCompilation finished\033[0m"

#2. Run function generation program in parallel
echo -e "\033[1m* Generating polynomial. This will take a long time\033[0m"
echo -e "\033[1m\tRunning generation script in parallel\033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\tEstimated time: 3 hours\033[0m"
cat FuncGenCommands.txt | parallel -j $parallelism

echo -e "\033[1m\tPolynomial generation complete\033[0m"

echo -e "\033[1m\tFile transfer complete\033[0m"

#5. Finally, make clean
echo -e "\033[1m* Cleaning up\033[0m"
make --silent clean
rm *.log
cd ../..
echo -e "\033[1m\tCleanup complete\033[0m"
