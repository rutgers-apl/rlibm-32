objects = log2 log log10 exp2 exp exp10 sinh cosh

all: $(objects)

$(objects): %: %.c
	gcc -O3 -std=c11 $^ -I$(SOFTPOSITPATH)/source/include -I../../../include/  ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a -lm -lmpfr -lgmp -o $@


clean:
	rm -rf $(objects) *.dSYM
