CC = gcc

funcNames = Log Log2 Log10 Exp Cosh Sinh Cospi Sinpi

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -static \
	-I../../../external/include/crlibm/ \
	-I$(SOFTPOSITPATH)/source/include \
	-frounding-math -fsignaling-nans \
	-O3 -std=c11 $^ \
	$(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a \
	../../../external/lib/libcrlibm.a \
	-lm \
	-o $@

clean:
	rm -rf $(obj) *.dSYM
