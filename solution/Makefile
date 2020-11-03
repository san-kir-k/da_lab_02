CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
NAME = solution

all: rb_tree.o pair.o
	$(CXX) $(CXXFLAGS) rb_tree.o pair.o main.cpp -o $(NAME)
rb_tree.o: rb_tree.cpp rb_tree.hpp pair.hpp
	$(CXX) $(CXXFLAGS) -c rb_tree.cpp
pair.o: pair.hpp
	$(CXX) $(CXXFLAGS) -c pair.cpp
clean:
	rm -f *.o $(NAME)