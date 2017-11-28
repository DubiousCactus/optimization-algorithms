CC = g++
CFLAGS  = -g -Wall -std=c++11

default: main

main:	Main.o 
		$(CC) $(CFLAGS) -o OptimizationAlgorithms Main.o

algorithm:	Algorithm.cpp Algorithm.h HandWrittenNumbers.h FacialPictures.h
			$(CC) $(CFLAGS) -c Algorithm.cpp

handwrittennumbers:	HandWrittenNumbers.cpp HandWrittenNumbers.h DataInput.h
					$(CC) $(CFLAGS) -c HandWrittenNumbers.cpp

facialpictures:	FacialPictures.cpp FacialPictures.h DataInput.h
				$(CC) $(CFLAGS) -c FacialPictures.cpp

datainput:	DataInput.h Matrix.h
			$(CC) $(CFLAGS) -c DataInput.h

clean:	$(RM) count *.o *~
