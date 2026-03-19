#!/bin/bash

read -p "Enter the path to a text file: " filepath

if [ ! -e "$filepath" ]; then
	echo "Error: That file does not exist."
	exit 1
fi

if [ ! -f "$filepath" ]; then
	echo "Error: The path is not a regular file."
	exit 1
fi

results=$(sort "$filepath" | uniq -c | sort -k1,1nr -k2,2)

echo "$results" | while read count word; do
	echo "Frequency of the word $word: $count"
done

unique_count=$(echo "$results" | wc -l)
echo "Total number of unique words analyzed: $unique_count"

