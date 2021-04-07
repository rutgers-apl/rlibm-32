CC = $(ICCPATH)/compiler/2021.1.1/linux/bin/intel64/icc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -O3 -static -std=c11 -fp-model strict -no-ftz \
	-I$(SOFTPOSITPATH)/source/include \
	$^ \
	$(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a \
	$(ICCPATH)/compiler/2021.1.1/linux/compiler/lib/intel64/libimf.a \
	-no-ftz -o $@

clean:
	rm -rf $(obj) *.dSYM
