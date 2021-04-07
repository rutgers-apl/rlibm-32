CC = gcc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -static \
        -L${LOCAL}/usr/lib64 \
        -L${LOCAL}/lib64 \
        -I${LOCAL}/include \
        -I${LOCAL}/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include \
        -I$(SOFTPOSITPATH)/source/include \
	-I../../include \
        -Wl,-rpath=${LOCAL}/usr/lib64:${LOCAL}/lib64 \
        -Wl,--dynamic-linker=${LOCAL}/lib64/ld-linux-x86-64.so.2 \
        -Wl,--dynamic-linker=${LOCAL}/lib64/ld-2.33.so \
        -frounding-math -fsignaling-nans \
        -O3 -std=c11 $^ \
	../../lib/posit32MathLib.a \
        $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a \
        ${LOCAL}/usr/lib64/libm-2.33.a \
        -o $@

clean:
	rm -rf $(obj) *.dSYM
