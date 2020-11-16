# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps			: MaxPlanarSubset_opt.o main_opt.o 
			$(CC) $(OPTFLAGS) MaxPlanarSubset_opt.o main_opt.o  -o bin/mps
main_opt.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@
MaxPlanarSubset_opt.o	: src/MaxPlanarSubset.cpp src/MaxPlanarSubset.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg		: MaxPlanarSubset_dbg.o main_dbg.o 
			$(CC) $(DBGFLAGS) MaxPlanarSubset_dbg.o main_dbg.o -o bin/mps_dbg
main_dbg.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@
MaxPlanarSubset_dbg.o	: src/MaxPlanarSubset.cpp src/MaxPlanarSubset.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o bin/*

