CC = gcc

funcNames = Log Log2 Log10 Sinh Cosh Exp Exp2 Exp10

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -O2 -std=c11  -I../../../helper/ -I../../../include/  $^ -lm -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
