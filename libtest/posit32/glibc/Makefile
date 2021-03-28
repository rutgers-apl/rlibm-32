objects = log2 log log10 exp2 exp exp10 sinh cosh cosh14

all: $(objects)

$(objects): %: %.cpp
	g++ -O2 -std=c++11 $^ -lm -lmpfr -lgmp ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a  -I$(SOFTPOSITPATH)/source/include -I../../../include/ -o $@


clean:
	rm -rf $(objects) *.dSYM
