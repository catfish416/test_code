#   This makefile is used for gtest and lcov
#   So gtest and lcov should be installed and configured correctly first.
#   Author: WangShijie

CURDIR=$(shell pwd)
LD_LIBRARY_PATH=/usr/local/lib/

INC_DIR   = $(CURDIR)/inc
SRC_PATH  = $(CURDIR)/src
TEST_PATH = $(CURDIR)/test


CXX = g++
CC  = gcc
CXXFLAGS = -I $(INC_DIR) -I /usr/local/include/gtest/
libflag  = -L /usr/local/lib
LDFLAGS  = -lgtest -lgtest_main -lpthread -std=c++11
TESTFLAG = -ftest-coverage -fprofile-arcs

SRC = $(foreach d, $(SRC_PATH), $(wildcard $(d)/*.cpp))
SRC += $(foreach d, $(TEST_PATH), $(wildcard $(d)/*.cpp))



all: run_test
run_test:
	$(CXX) -o $@ $(SRC) $(CXXFLAGS) $(LDFLAGS) -pg ${TESTFLAG}

clean:
	rm -f *.o src/*.o test/*.o *.gcno *.gcda *.out *.gcov *.info run_test
	rm -rf result
