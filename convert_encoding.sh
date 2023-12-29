#!/bin/bash

files=$(find ./src/ ./include/ -type f)
result=$(enca -L zh_CN -x UTF-8 $files 2>&1)
if [ -z "$result" ]
then
	echo "Convert Successfully!"
else
	echo $result
	echo "Convert Failed!"
fi
