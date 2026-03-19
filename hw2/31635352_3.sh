#!/bin/bash

if [ $# -eq 0 ]; then
	echo "No argument was provided. The program will now exit."
	exit 1
elif [ $# -gt 1 ]; then
	echo "More than one argument was provided. The program will now exit."
	exit 1
else
	directory="$1"
fi

if [ ! -d "$directory" ]; then
	echo "The directory entered is not valid. The program will now exit."
	exit 1
fi

file_names=()
path_names=()
files_processed=0
duplicate_files=0
files_deleted=0

traverse() {
	local current="$1"

	for item in $(ls "$current"); do
		local full_path="$current/$item"
		if [ -d "$full_path" ]; then
			traverse "$full_path"
		elif [ -f "$full_path" ]; then
			local filename=$(basename "$full_path")

			local is_dupe=0
			local og_path=""


			for ((i=0; i<${#file_names[@]}; i++)); do
				if [[ "${file_names[$i]}" == "$filename" ]]; then
			 		is_dupe=1
					((duplicate_files++))
					og_path="${path_names[$i]}"
					break
				fi
			done

			if [[ $is_dupe -eq 1 ]]; then
				echo "Duplicate found"
				echo "Original: $og_path"
				echo "Duplicate: $full_path"
				while true; do
					echo "Do you want to remove $full_path? (yes/no):" 
					read user_input
					good_user=$(echo $user_input | tr '[:upper:]' '[:lower:]')

					if [[ "$good_user" == "yes" || "$good_user" ==  "y" ]]; then
						rm "$full_path"
						echo "File removed."
						((files_deleted++))
						break
					elif [[ "$good_user" == "no" || "$good_user" == "n" ]]; then
						echo "File kept."
						break
					else
						echo "Invalid input. Please enter yes or no."
						fi
				done
			fi
			((files_processed++))
			file_names+=( "$filename" )
			path_names+=( "$full_path" )
		fi
	done
}

traverse "$directory"
echo "Traversal complete."
echo "Files processed: $files_processed"
echo "Duplicate files found: $duplicate_files"
echo "Files deleted: $files_deleted"