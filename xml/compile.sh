#!/bin/sh

echo compiling...

g++ a.cpp -I/usr/local/include/libxml2 -L/usr/local/lib -lxml2 -o a
g++ b.cpp -I/usr/local/include/libxml2 -L/usr/local/lib -lxml2 -o b

echo run a...
./a
cat List.xml

echo run b...
./b

exit 0
