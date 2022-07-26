#!/bin/bash

# Write a bash script that receives any number of command line arguments and prints on the screen, for each argument, if it is a file, a directory, a number or something else.

if [ $# -lt 1 ];then
	echo "No arguments given"
	exit 1
fi

for A in $@; do
	if [ -f $A ];then
		echo "$A is a file"
	elif [ -d $A ]; then
		echo "$A is a directory"
	elif echo $A | grep -E -q "^[0-9]*$";then
		echo "$A is a number"
	else
		echo "I dont know what $A is"
	fi
done

