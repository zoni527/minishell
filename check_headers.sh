#!/bin/bash

C_FILES=`find ./src -type f -name "*.c"`
for f in $C_FILES;
do
	BASENAME=$(basename ${f})
	HEADER_FILE_NAME=`awk 'NR == 4 {print $2}' $f`
	if [[ "$HEADER_FILE_NAME" != "$BASENAME" ]]; then
		echo "File $f has an incorrect header"
	fi
	awk 'NR == 6 {print $2 " " $3 " " $4}' $f
done
