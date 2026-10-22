CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror 
GTEST_PREFIX = $(shell brew --prefix googletest)
GTEST_CXXFLAGS = -I$(GTEST_PREFIX)/include
GTEST_LDFLAGS = -L$(GTEST_PREFIX)/lib -lgtest -lgtest_main -pthread

all: main test

clean:
	rm src/Graph.o main test

main: src/Graph.o src/Main.cpp
	$(CXX) $(CXXFLAGS) src/Main.cpp src/Graph.o -o main

test: src/Graph.o src/Tests.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) src/Tests.cpp src/Graph.o $(GTEST_LDFLAGS) -o test

src/Graph.o: src/Graph.cpp 
	$(CXX) $(CXXFLAGS) -c src/Graph.cpp -o src/Graph.o
