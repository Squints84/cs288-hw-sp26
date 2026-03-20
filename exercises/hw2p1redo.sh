#!/bin/bash

if [ $# -eq 0 ] then
	echo "$0 num1 num2 ..."
	exit 1
fi

nums=("$@")

echo "Original array: ${nums[*]}"

nums_length=${#nums[@]}


for 
