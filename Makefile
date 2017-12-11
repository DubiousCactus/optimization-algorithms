CC = g++
CFLAGS  = -g -Wall -std=c++11 -O3 -march=native -ffast-math -funroll-loops -ggdb3 -pthread -lm -lpthread

default: OptimizationAlgorithms

OptimizationAlgorithms:	Main.o Algorithm.o MNISTData.o ORLData.o
		$(CC) $(CFLAGS) -o OptimizationAlgorithms Main.o Algorithm.o MNISTData.o ORLData.o

main:	Main.cpp Algorithm.h
		$(CC) $(CFLAGS) -c Main.cpp

algorithm:	Algorithm.cpp Algorithm.h MNISTData.h ORLData.h
			$(CC) $(CFLAGS) -c Algorithm.cpp

mnistdata:	MNISTData.cpp MNISTData.h DataInput.h
					$(CC) $(CFLAGS) -c MNISTData.cpp

orldata:	ORLData.cpp ORLData.h DataInput.h
				$(CC) $(CFLAGS) -c ORLData.cpp

datainput:	DataInput.h
			$(CC) $(CFLAGS) -c DataInput.h

clean:	
	$(RM) count *.o *~
