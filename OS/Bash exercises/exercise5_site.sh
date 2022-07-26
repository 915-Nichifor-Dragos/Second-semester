#!/bin/bash

# Write a bash script that keeps reading strings from the keyboard until the name of a readable regular file is given.

X=""
while true; do
	read -p "Enter a string: " X
	if [ -f $X ];then
		echo "$X is a file"
		break
	else
		echo "$X is not a file, continuing to read..."
	fi
done

