#!/bin/bash

# 7. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

if [ $# -lt 2 ]; then
	echo "Not enough arguments"
	exit 1
fi

if [ $(($#%2)) -eq 1 ]; then
	echo "The number of arguments must be even"
	exit 1
fi

while [ $# -gt 1 ]; do
	file=$1
	word=$2

	if [ ! -f $file ]; then
		echo "Not a file"
	else
		count=$(grep -E -o "\<$word\>" $file | wc -l)
		if [ $count -ge 3 ]; then
			echo "Word $word appeared $count times in the file $file"
		else
			echo "No"
		fi
	fi
	
	shift 2
done

