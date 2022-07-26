#!/bin/bash

# Write a script that monitors the state of a given folder and prints a message when something changed.

if [ $# -lt 1 ]; then
	echo "Not enough arguments"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "$1 is not a directory"
	exit 1
fi

S=""
ok=0
while true; do
	Z=""
	for F in $1; do
		if [ -f $F ]; then
			H=`ls -l $F | sha1sum`
			C=`cat $F | sha1sum`
		elif [ -d $F ]; then
			H=`ls -ld $F | sha1sum`
			C=`ls -l $F | sha1sum`
		fi
		Z="$Z $H $C"	
	done
	if [ $ok -eq 1 ];then
		if [ "$S" != "$Z" ]; then
			echo "some change ocurred"
			exit 0
		fi
	fi
	S="$Z"
	ok=1
	echo "$Z"
	sleep 7	

done


