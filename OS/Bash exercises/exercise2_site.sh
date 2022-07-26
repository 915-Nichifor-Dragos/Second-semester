#!/bin/bash

# 1a. Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument, excluding lines that are              empty or contain only spaces. 

if [ $# -lt 1 ]; then
	echo "Not enough arguments"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Not a directory"
	exit 1;
fi

total=0

for F in $(ls $1 | grep -E ".c$"); do
	if [ -f "$1/$F" ]; then
		nr_lines=$(grep -E -c -v "^[ \t]*$" "$1/$F")
		echo "$F: $nr_lines"
		total=$((total+nr_lines))
	fi
done

echo "Total number of lines: $total"


