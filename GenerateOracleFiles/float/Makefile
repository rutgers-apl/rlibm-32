CC = gcc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Cospi Sinpi

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -static -I../../include -frounding-math -fsignaling-nans -O3 -std=c11 $^ ../../lib/floatMathLib.a -lm -o $@

clean:
	rm -rf $(obj) *.dSYM
