CC = g++
CFLAGS  = -g -Wall -std=c++11 -O3 -march=native -funroll-loops -mfpmath=sse -lm -lpthread -fopenmp

default: OptimizationAlgorithms

OptimizationAlgorithms:	Main.o Logic/Algorithm.o DataInput/MNISTData.o DataInput/ORLData.o
		$(CC) $(CFLAGS) -o OptimizationAlgorithms Main.o Logic/Algorithm.o DataInput/MNISTData.o DataInput/ORLData.o

main:	Main.cpp Logic/Algorithm.h
		$(CC) $(CFLAGS) -c Main.cpp

algorithm:	Logic/Algorithm.cpp Logic/Algorithm.h DataInput/MNISTData.h DataInput/ORLData.h
			$(CC) $(CFLAGS) -c Logic/Algorithm.cpp

mnistdata:	DataInput/MNISTData.cpp DataInput/MNISTData.h DataInput/DataInput.h
					$(CC) $(CFLAGS) -c DataInput/MNISTData.cpp

orldata:	DataInput/ORLData.cpp DataInput/ORLData.h DataInput/DataInput.h
				$(CC) $(CFLAGS) -c DataInput/ORLData.cpp

datainput:	DataInput/DataInput.h
			$(CC) $(CFLAGS) -c DataInput/DataInput.h

clean:	
	$(RM) -r count */*.o *~
