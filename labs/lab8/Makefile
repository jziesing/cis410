all: stencil_serial stencil_openmp stencil_cilk

stencil_cilk: stencil_cilk.cpp
	icpc -std=c++11 -o stencil_cilk stencil_cilk.cpp -Wall -Wextra -lopencv_core -lopencv_highgui -lm -lcilkrts


stencil_serial: stencil_serial.cpp
	icpc -std=c++11 -o stencil_serial stencil_serial.cpp -Wall -Wextra -lopencv_core -lopencv_highgui -lm

stencil_openmp: stencil_mp.cpp
	icpc -std=c++11 -o stencil_mp stencil_mp.cpp -fopenmp -Wall -Wextra -lopencv_core -lopencv_highgui -lm 

clean:
	rm -f *.o stencil_serial stencil_mp stencil_cilk
	
.PHONY: clean
