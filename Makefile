CC = ${LOCAL}/usr/bin/gcc

floatFNames = log log2 log10 exp exp2 exp10 sinh cosh sinpi cospi log2_8 log10_8 

floatSrcDir = source/float
floatObjDir = obj/float
libDir = lib

floatSrc = $(patsubst %, $(floatSrcDir)/%.c, $(floatFNames))
floatObj = $(patsubst %, $(floatObjDir)/%.o, $(floatFNames))

all: $(libDir)/floatMathLib.a

$(floatObjDir)/%.o: $(floatSrcDir)/%.c
	@mkdir -p $(floatObjDir)
	$(CC) -static -std=c11 -O3 -c $^ -Iinclude/ -o $@

$(libDir)/floatMathLib.a: $(floatObj)
	@mkdir -p $(libDir)
	ar rc $@ $^

floatmlib: $(libDir)/floatMathLib.a

clean:
	rm -rf obj lib *.dSYM
