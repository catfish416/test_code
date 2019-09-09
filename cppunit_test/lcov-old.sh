#!/bin/sh

./run_test
gcov money.cpp
lcov -d . -t 'hello test' -o 'hello_test.info' -b . -c
genhtml -o result hello_test.info
chrome ./result/index.html
