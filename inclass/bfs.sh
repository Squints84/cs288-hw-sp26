#!/bin/bash

#set up as a queue
# first in,first out
#
#

queue[0]=$1
while ["${#queue[@]}" -ne 0]; do
	echo "${queue[0]}"
	if [ -d "${queue[0]}" ] && [ $(ls "${queue[0]}" | wc -l) -ne 0]; then
		entries=("${queue[0]}"/*)

		# merge two arrays
		queue=("${queue[@]}" "${entries[@]}")
	fi
	#remove the first element (element 0)
	queue=("${queue[@]}:1")
done

