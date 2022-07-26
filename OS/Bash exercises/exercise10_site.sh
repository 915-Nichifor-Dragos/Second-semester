#!/bin/bash

# Write a bash script that sorts all files given as command line arguments descending by size.(first check if an argument is a file)

for F in $@; do
	if [ -f $F ]; then
		du -b $F 
	fi
done | sort -n -r

