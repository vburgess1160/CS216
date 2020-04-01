# Name: Victoria Burgess
# File: makefile
# Project: Project 3
# Purpose: Compiles source files for target CS216PA3
EXEC = CS216PA3
OBJECTS = Graph.o WordLadder.o CS216PA3.o
HEADERS = Graph.h WordLadder.h
	#(listing all of ur obj files here, separated by space)
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -i *.o
	rm -i `find ./ -type f -executable`
