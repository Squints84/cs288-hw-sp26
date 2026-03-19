#!/bin/bash

if [ $# -eq 0 ]; then
	target_dir="."
elif [ $# -eq 1 ]; then
	target_dir="$1"
else
	echo "Too many arguments provided. This program only accepts 0 or 1 arguments. The program will now exit."
	exit 1
fi

if [ ! -d "$target_dir" ]; then
	echo "Error: The directory you entered: $target_dir does not exist."
	exit 1
fi

total_processed=0
total_removed=0

traverse() {
	local current="$1"

	echo "$current"

	for item in "$current"/*; do
		if [ -d "$item" ] && [ ! -L "$item" ]; then
			traverse "$item"
		elif [ -f "$item" ] && [ ! -L "$item" ]; then
			((total_processed++))
			
			if [ ! -s "$item" ]; then
				rm "$item"
				((total_removed++))
				echo "Removed: $item"
			fi
		fi
	done
}

traverse "$target_dir"

echo "-----------------------------"
echo "Summary:"
echo "Total number of files processed: $total_processed"
echo "Total number of zero-length files removed: $total_removed"
