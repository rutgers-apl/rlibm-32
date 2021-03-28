CC = $(ICCPATH)/compiler/2021.1.1/linux/bin/intel64/icc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Sinpi2 Cospi

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -std=c11 -O3 -I../../../helper/ -I../../../include/  $^  $(ICCPATH)/compiler/2021.1.1/linux/compiler/lib/intel64/libimf.a -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
