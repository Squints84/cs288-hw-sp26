#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <directory>"
	exit 1
fi

directory=$1

if [ ! -d "$directory" ]; then
	echo "Error: $directory is not a valid directory."
	exit 1
fi

temp_file=$(mktemp)

traverse_directory() {
	local dir=$1
	for file in "$dir"/*; do
		if [ -d "$file" ]; then
			traverse_directory "$file"
		elif [ -f "$file" ] && [[ "$file" == *.txt ]]; then
			grep -oE '^[a-zA-Z][a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}' "$file" >> "$temp_file"
		fi
	done
}

traverse_directory "$directory"

sort -u "$temp_file" > unique_emails.txt

rm "$temp_file"

echo "EMAIL EXTRACTION COMPLETE"
echo "Unique email addresses have been saved to unique_emails.txt"
