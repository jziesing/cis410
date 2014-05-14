default: all

all: badIndex

badIndex: badIndex.c
	icc -g -o badIndex badIndex.c -fopenmp

clean:
	rm tbb badIndex *.o 2>/dev/null
