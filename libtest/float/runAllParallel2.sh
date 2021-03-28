#!/bin/bash

parallelism=2

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

mkdir -p Result
mkdir -p Result/glibcO2
mkdir -p Result/glibcO3
mkdir -p Result/rlibm

#2. Run function generation program in parallel
echo -e "\033[1m* Generating polynomial. This will take a long time\033[0m"
echo -e "\033[1m\tRunning generation script in parallel\033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\tEstimated time: 15 minutes\033[0m"
cat ParallelCommand2.txt | parallel -j $parallelism

