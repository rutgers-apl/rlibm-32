CC = gcc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Cosh Sinh

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.c
	$(CC) -static -frounding-math -fsignaling-nans -O3 -std=c11 $^ -lm -o $@

clean:
	rm -rf $(obj) *.dSYM
