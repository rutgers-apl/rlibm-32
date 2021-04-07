CC = gcc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -static \
	-I../../../include \
	-I$(SOFTPOSITPATH)/source/include \
	-frounding-math -fsignaling-nans \
        -O3 -std=c11 $^ \
	../../../lib/posit32MathLib.a \
	$(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a \
	-lm \
        -o $@

clean:
	rm -rf $(obj) *.dSYM
