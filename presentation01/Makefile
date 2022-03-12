# The variable CC specifies which compiler will be used.
# (because different unix systems may use different compilers)
CC=gcc

# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
#   -std=c99: Using newer C99 version of C programming language
# 	-g allows for Valgrind to be used, to measure debugging information and memory leaks
# 	-O 
CFLAGS=-c -Wall -std=c99 -g -O1

# All of the .h header files to use as dependencies
HEADERS=demo.h demo_functions.h

# All of the object files to produce as intermediary work
OBJECTS=demo.o demo_functions.o

# The final program to build
EXECUTABLE=demo_program

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
