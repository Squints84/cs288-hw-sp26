#!/bin/bash

if [ $# -eq 0 ]; then
    read -r -p "Enter filename: " filename
else
    filename=$1
fi

if [ ! -f "$filename" ]; then
    echo "Error: File '$filename' not found." >&2
    exit 1
fi

declare -a date_entries

while IFS= read -r line || [[ -n "$line" ]]; do
    matches=$(echo "$line" | grep -oE '[0-9]{2}[/.-][0-9]{2}[/.-][0-9]{4}')

    while IFS= read -r date; do
        [ -z "$date" ] && continue

        if [[ "$date" == *"/"* ]]; then
            month=$(echo "$date" | cut -d'/' -f1)
            day=$(echo "$date" | cut -d'/' -f2)
            year=$(echo "$date" | cut -d'/' -f3)
        elif [[ "$date" == *"-"* ]]; then
            month=$(echo "$date" | cut -d'-' -f1)
            day=$(echo "$date" | cut -d'-' -f2)
            year=$(echo "$date" | cut -d'-' -f3)
        elif [[ "$date" == *"."* ]]; then
            temp=$(echo "$date" | sed 's/\./ /g')
            month=$(echo "$temp" | cut -d' ' -f1)
            day=$(echo "$temp" | cut -d' ' -f2)
            year=$(echo "$temp" | cut -d' ' -f3)
        fi

        sort_key="${year}${month}${day}"

        date_entries+=("${sort_key}|${date}")

    done <<< "$matches"
done < "$filename"

if [ ${#date_entries[@]} -eq 0 ]; then
    echo "No dates found in the file."
    exit 0
fi

printf '%s\n' "${date_entries[@]}" | sort | cut -d'|' -f2
