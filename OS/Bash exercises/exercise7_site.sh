#!/bin/bash

# Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder given as a parameter.(use test to check if the folder exists and if a given file is a regular file)

if [ $# -lt 1 ]; then
	echo "Please enter a parameter"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "The parameter must be a directory"
	exit 1
fi

total=0
for F in $(ls $1); do
	if [ -f $1/$F ]; then
		dim=$(du -b $1/$F | awk '{print $1}')
		total=$((dim+total))
		echo "$1/$F - $dim"
	fi
done

echo "Total - $total"


