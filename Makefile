CXX = g++

CXXFLAGS = -std=c++17 -Wall -Werror 

all: main test

clean:
	rm src/Graph.o main test

main: src/Graph.o src/Main.cpp
	$(CXX) $(CXXFLAGS) src/Main.cpp src/Graph.o -o main

test: src/Graph.o src/Tests.cpp
	$(CXX) $(CXXFLAGS) src/Tests.cpp src/Graph.o -o test

src/Graph.o: src/Graph.cpp 
	$(CXX) $(CXXFLAGS) -c src/Graph.cpp -o src/Graph.o
