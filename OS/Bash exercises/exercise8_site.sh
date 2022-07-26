#!/bin/bash

# Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.(Hint: test command to check if regular file; file command to check if text file)

while true; do
	read -p "Enter the filename or stop: " file
	if [ $file == "stop" ]; then
		echo "Done"
		exit 0
	fi

	if [ -f $file ]; then
		if file $file | grep -E -q "text"; then
			echo "File $file - Words on the 1st line: $(head -1 $file | wc -w)"
		fi
	fi
done

