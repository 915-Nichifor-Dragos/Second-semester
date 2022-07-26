#!/bin/bash

# Write a script that extracts from all the C source files given as command line arguments the included libraries and saves them in a file.(use the file command to check if a file is a C source file)


for F in $@; do
	if [ -f $F ]; then
		if echo $F | grep -E ".c$"; then
			lib=$(grep -E -o "#include[ ]*<[a-z0-9.]+>" $F)
			echo "$lib"
			echo $lib > output.txt
		else
			echo "Not a c file"
		fi
	fi
done


