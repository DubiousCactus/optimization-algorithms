CC = g++
CFLAGS  = -g -Wall

default: main

main:	Algorithm.o DataInput.o
		$(CC) $(CFLAGS) -o OptimizationAlgorithms Algorithm.o DataInput.o

algorithm:	Algorithm.cpp Algorithm.h DataInput.h
			$(CC) $(CFLAGS) -c Algorithm.cpp

datainput:	DataInput.cpp DataInput.h
			$(CC) $(CFLAGS) -c DataInput.cpp

clean:	$(RM) count *.o *~
