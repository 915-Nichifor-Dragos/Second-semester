#!/bin/bash

# Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use option -L to test if a path is a symbolic link, and option -e to test if it exists (will return false if the target to which the link points does not exist)

if [ $# -lt 1 ]; then
	echo "No parameters"
	exit 1
fi

if [ ! -d $1 ]; then
       echo "Not a directory"
       exit 1
fi

for F in $(find $1 -type l); do
	if [ -e $F ]; then
		echo "The link exists"
	else
		echo "The link does not exist"
	fi
done


