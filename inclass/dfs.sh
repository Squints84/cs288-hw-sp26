#!/bin/bash


# recursive method


function traverse(){
	if [ ! -d "$1"]; then # if not a directory then return
		return
	fi
	if [ $(ls "$l" | wc -l) -eq 0]; then # ls to get details abt directory then piping into word count with -l option to count lines and checking if it's equal to 0 to check if directory is empty and we can ignore it
		return
	fi
	entries=("$1"/*)
	for i in "${entries[@]}"
	do
		traverse "$i"
	done


