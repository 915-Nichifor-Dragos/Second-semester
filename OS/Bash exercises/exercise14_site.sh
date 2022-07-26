#!/bin/bash

# 12. Write a bash script that receives a folder name as argument. Find recursively in the folder the number of times each file name is repeated.

if [ $# -lt 1 ]; then
	echo "Not enough arguments"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Not a directory"
	exit 1
fi

find "$1" -type f | awk -F/ '{print $NF}' | sort | uniq -c

