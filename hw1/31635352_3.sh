#!/bin/bash

read -p "Enter a directory path: " dir_path

if [ ! -d "$dir_path" ]; then
	echo "Error: The directory does not exist."
	exit 1
fi

cd "$dir_path"

echo "Analyzing directory: $dir_path"
echo " "

ls_output=$(ls -l | tail -n +2)
total_size=0
num_items=0

echo "All items in the directory with their sizes:"

while read line; do
	size=$(echo "$line" | tr -s ' ' | cut -d ' ' -f5)
	name=$(echo "$line" | tr -s ' ' | cut -d ' ' -f9)

	echo " - $name: $size bytes"
	total_size=$((total_size + size))
	num_items=$((num_items + 1))
done <<< "$ls_output"

average=$((total_size / num_items))
echo ""
echo "Average size: $average bytes"
echo ""

echo "Items larger than average ($average bytes):"
large_count=0

while read line; do
	size=$(echo "$line" | tr -s ' ' | cut -d' ' -f5)
    	name=$(echo "$line" | tr -s ' ' | cut -d' ' -f9)
    	if [ $size -gt $average ]; then
        	large_count=$((large_count + 1))
        	echo "$large_count. $name - $size bytes"
    	fi
done <<< "$ls_output"

echo ""
echo "Total items above average: $large_count out of $num_items"
