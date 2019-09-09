#!/bin/bash
file_name=$1
echo "$file_name"

#ls -l|grep "$file_name"
find . -name "*.cpp"
r=$?

if [ $r == 1 ]; then
	echo "不存在此文件"
	#exit 1
elif [ $r == 0 ]; then
	echo "存在此文件"
	#exit 0
fi
