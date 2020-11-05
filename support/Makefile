CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wextra -Wall -Werror -pedantic -Wno-sign-compare -Wno-unused-result
NAME = benchmark
DIR = ../solution

all: rb_tree.o pair.o
	$(CXX) $(CXXFLAGS) rb_tree.o pair.o benchmark.cpp -o $(NAME)
rb_tree.o: $(DIR)/rb_tree.cpp $(DIR)/rb_tree.hpp $(DIR)/pair.hpp
	$(CXX) $(CXXFLAGS) -c $(DIR)/rb_tree.cpp
pair.o: $(DIR)/pair.hpp
	$(CXX) $(CXXFLAGS) -c $(DIR)/pair.cpp
clean:
	rm -f *.o $(NAME)