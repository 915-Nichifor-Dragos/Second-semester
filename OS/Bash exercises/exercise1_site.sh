#!/bin/bash

# Write a bash script that counts all the C files from a given directory and all of its subdirectories.

if [ $# -lt 1 ]; then
	echo "No directory given"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "The argument is not a directory"
	exit 1
fi

find $1 -type f | grep -E -c ".c$"

