CC = g++
CFLAGS  = -g -Wall -std=c++11

default: OptimizationAlgorithms

OptimizationAlgorithms:	Main.o Algorithm.o HandWrittenNumbers.o FacialImageSet.o
		$(CC) $(CFLAGS) -o OptimizationAlgorithms Main.o Algorithm.o HandWrittenNumbers.o FacialImageSet.o

main:	Main.cpp Algorithm.h
		$(CC) $(CFLAGS) -c Main.cpp

algorithm:	Algorithm.cpp Algorithm.h HandWrittenNumbers.h FacialImageSet.h
			$(CC) $(CFLAGS) -c Algorithm.cpp

handwrittennumbers:	HandWrittenNumbers.cpp HandWrittenNumbers.h DataInput.h
					$(CC) $(CFLAGS) -c HandWrittenNumbers.cpp

facialimageset:	FacialImageSet.cpp FacialImageSet.h DataInput.h
				$(CC) $(CFLAGS) -c FacialImageSet.cpp

datainput:	DataInput.h 
			$(CC) $(CFLAGS) -c DataInput.h

clean:	$(RM) count *.o *~
