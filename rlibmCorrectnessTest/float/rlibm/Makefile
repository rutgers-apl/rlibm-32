CC = gcc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Sinpi Cospi

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -O3 -std=c11 -I../../../helper/ -I../../../include/  $^ ../../../lib/floatMathLib.a -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
