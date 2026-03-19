#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 num1 num2 num3 ..."
	echo "Example: $0 5 -1 10 2"
	exit 1
fi


arguments=("$@")

echo "Original array: ${arguments[@]}"

len=${#arguments[@]}

for ((i = 1; i < len; i++)); do
	key=${arguments[i]}
	j=$((i - 1))

	while ((j >= 0)) && ((arguments[j] > key)); do
		arguments[$((j + 1))]=${arguments[j]}
		j=$((j - 1))
	done

	arguments[$((j + 1))]=$key
done

echo "Sorted array: ${arguments[*]}"
