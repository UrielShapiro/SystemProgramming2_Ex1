# Last digits of ID: 9745
# Mail: uriel1999@gmail.com



CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

SOURCES=Graph.cpp Algorithms.cpp
Algorithms = Algorithms
Graph = Graph
OBJECTS=Graph.o Algorithms.o

all: demo test

debug:
	$(CXX) $(CXXFLAGS) --compile Algorithms.cpp -o Algorithms.o -DDEBUG
	make test
	-./test			# ignore code 1 that test returns

run: demo
	./$^

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo -lgcov

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lgcov

TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c -o $@ $^

$(Algorithms).o: $(Algorithms).cpp $(Algorithms).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<

$(Graph).o: $(Graph).cpp $(Graph).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<

gcov: 
	make all
	-./test
	-gcov $(Algorithms).cpp
	-gcov $(Graph).cpp
	-cat $(Algorithms).cpp.gcov
	make clean

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
	-make clean

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o *.gcov *.gcda *.gcno demo test

.PHONY: all run demo test clean gcov valgrind
