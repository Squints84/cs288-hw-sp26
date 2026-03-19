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

tmp=$(mktemp)

current_year=2025

while IFS= read -r line || [[ -n "$line" ]]; do
    [ -z "$line" ] && continue

    name=$(echo "$line" | cut -d',' -f1 | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    dob=$(echo "$line" | cut -d',' -f2 | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    city=$(echo "$line" | cut -d',' -f3 | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    if [[ ! "$city" =~ [[:space:]] ]]; then
        continue
    fi

    birth_year=$(echo "$dob" | grep -oE '^[0-9]{4}')
    [ -z "$birth_year" ] && continue

    age=$((current_year - birth_year))
    echo "${age}|${name}" >> "$tmp"
done < "$filename"

sort -t'|' -k1 -rn "$tmp" | while IFS='|' read -r age name; do
    echo "$name, $age"
done

rm -f "$tmp"
