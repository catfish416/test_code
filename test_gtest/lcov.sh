#!/bin/bash

# set chrome path
export PATH=$PATH:/opt/google/chrome

./run_test
dir="./src/*.cpp"
#dir=$1$dir
for f in $dir
do
if [ -f $f ]
then
echo $f
echo ${f##*/}  ##该方式是从左开始最大化匹配到字符"/"，然后截掉左边内容（包括字符"/"）,返回余下右侧部分。
gcov ${f##*/}
fi
done

# 转化为.info
lcov -d . -t 'hello test' -o 'hello_test.info' -b . -c
# 生成html
genhtml -o result hello_test.info
# 浏览器打开html
chrome ./result/index.html
