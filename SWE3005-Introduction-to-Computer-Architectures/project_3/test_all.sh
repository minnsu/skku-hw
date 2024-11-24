#!/bin/bash

for file in $(cat apl_list.txt)
do
    removeELF=${file%.elf}
    ./test_each.sh $removeELF
done