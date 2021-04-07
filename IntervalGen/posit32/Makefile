objects = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh


CC=g++

INCLUDES= -I$(SOFTPOSITPATH)/source/include  -I../../helper/

CPP_FLAGS= -O2 -std=c++17

LD_FLAGS= $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a -lmpfr -lz -lm

all: $(objects)

$(objects): %: %.cpp
	$(CC) $(CPP_FLAGS) $(INCLUDES) $^ $(LD_FLAGS) -o $@

clean:
	rm -rf *.o $(objects) *~ *.dSYM MergeTwoFiles