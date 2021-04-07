objects = 	Log \
		Log2 \
		Log10 \
		Exp \
		Exp2 \
		Exp10 \
		Sinh \
		Cosh \
		Sinpi \
		Cospi

CC=g++

ADDTL +=

INCLUDES= -I$(SOFTPOSITPATH)/source/include -I$(SOPLEXPATH)/src
CPP_FLAGS += $(ADDTL) -O2 -fvisibility=hidden -fvisibility-inlines-hidden --std=c++17 -I../../helper/
LD_FLAGS= $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a $(SOPLEXPATH)/build/lib/libsoplex.a -lmpfr -lgmp  -lz -lm

all: $(objects)
	
%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@ $(INCLUDES)
	
$(objects): %: ../../helper/PolyGenSampling/PolyGenSampling.o %.o 
	$(CC) $^ $(LD_FLAGS) -o $@

clean:
	rm -rf *.o ../../helper/PolyGenSampling/*.o $(objects) *~ *.dSYM dump.lp
