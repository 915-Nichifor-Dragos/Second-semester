#!/bin/bash

# Write a bash script that sorts the file given as command line arguments in ascending order according to their file size in bytes.

for F in $@; do
	if [ -f $F ];then
		du -b $F
	fi
done | sort -n




