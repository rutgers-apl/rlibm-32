CC=g++

INCLUDES= -I$(SOFTPOSITPATH)/source/include -I$(SOPLEXPATH)/src
CPP_FLAGS= -fvisibility=hidden -fvisibility-inlines-hidden --std=c++17 -I../helper/

all: PolyFinder.o IntervalRange.o

%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@ $(INCLUDES)
	
clean:
	rm -rf *.o *.lp *~ *.dSYM
