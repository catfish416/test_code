CURDIR=$(shell pwd)
LD_LIBRARY_PATH=/usr/local/lib/
#USER_DIR = .

SRC=$(CURDIR)/src/money.cpp    \
    $(CURDIR)/test/money_test.cpp    \
    $(CURDIR)/test/money_test_main.cpp    \
    
CXX=g++
CC=gcc
CXXFLAGS=-I src/ -I test/ -I /usr/local/include/cppunit/
libflag = -L /usr/local/lib
#LDFLAGS=-lcppunit -ldl
LDFLAGS=-lcppunit -lrt -lcurses -ldl
TESTFLAG = -ftest-coverage -fprofile-arcs

FILES = $(foreach d, $(CURDIR), $(wildcard $(d)/src/*.cpp))
FILES += $(foreach d, $(CURDIR), $(wildcard $(d)/test/*.cpp))
#OBJS = $(patsubst %.cpp, %.o, $(FILES))


all: run_test
#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) ${TESTFLAG} -c $< -o $@

#run_test: $(SRC)
#	$(CXX) -o $@ $(SRC) $(CXXFLAGS) $(LDFLAGS) ${libflag} -pg ${TESTFLAG}
run_test: $(OBJS)
	$(CXX) -o $@ $(FILES) $(CXXFLAGS) $(LDFLAGS) ${libflag} -pg ${TESTFLAG}

clean:
	rm -f *.o src/*.o test/*.o *.gcno *.gcda *.out *.gcov *.info run_test
	rm -rf result
