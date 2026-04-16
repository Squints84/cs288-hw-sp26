#!/bin/bash

if [ $# -eq 0 ]; then
	echo "$0 num1 num2 ..."
	exit 1
fi

nums=("$@")

echo "Original array: ${nums[*]}"

nums_length=${#nums[@]}


for ((i = 0; i < nums_length; i++));do
       	key=${nums[i]}
	j=$((i - 1))

	while ((j>=0 && ${nums[j]} > key)); do
		nums[j+1]=${nums[j]}
		((j--))
	done

	nums[j+1]=$key
done

echo "Sorted array: ${nums[*]}"
