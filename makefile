CXX=g++
CFLAGS=-I -std=c++14 -pedantic -Wall --std=c++14
OBJ = main.o

# The default command does everything, it clears the terminal, compiles the app, and runs it. Just type make!
server: $(OBJ)
	$(CXX) -o main $(OBJ)
	chmod 755 main
	./main

# Run the application. This assumes it is already compiled.
run:
	./main

# Clear out all those ramdon *.o files littering the source directory!
clean:
	rm -f *.o main
