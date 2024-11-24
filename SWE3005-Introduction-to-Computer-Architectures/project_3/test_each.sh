#!/bin/bash

Min=100
MinCase=""

for set in 1 2 4 8 16 32 64 128 256
do
    ways=$((256/$set))
    Output=$(./build/spike --dc=$set:$ways:64 ~swe3005/2023s/proj3/pk ~swe3005/2023s/proj3/bench/$1.elf | grep "D$ Miss Rate")
    MissRate=${Output:14}
    OnlyPctage=${MissRate%\%}
    isNewMin=$(echo "$Min > $OnlyPctage" | bc)
    if [ ${isNewMin} -eq 1 ]; then
        Min=$OnlyPctage
        MinCase=$(echo $1 "--dc=$set:$ways:64" $MissRate)
    fi
    echo $1 "--dc=$set:$ways:64" $MissRate
done

echo "Minimum test case"
echo $MinCase