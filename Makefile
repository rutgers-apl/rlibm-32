CC = gcc

floatFNames = log log2 log10 exp exp2 exp10 sinh cosh sinpi cospi log2_8 log10_8 

p32FNames = log2 log log10 exp2 exp exp10 sinh cosh_1212 cosh_1412

floatSrcDir = source/float
floatObjDir = obj/float
p32SrcDir = source/posit32
p32ObjDir = obj/posit32
libDir = lib

floatSrc = $(patsubst %, $(floatSrcDir)/%.c, $(floatFNames))
floatObj = $(patsubst %, $(floatObjDir)/%.o, $(floatFNames))
p32Src = $(patsubst %, $(p32SrcDir)/%.c, $(p32FNames))
p32Obj = $(patsubst %, $(p32ObjDir)/%.o, $(p32FNames))

all: $(libDir)/floatMathLib.a $(libDir)/posit32MathLib.a

$(floatObjDir)/%.o: $(floatSrcDir)/%.c
	@mkdir -p $(floatObjDir)
	$(CC) -std=c11 -O3 -c $^ -Iinclude/ -o $@

$(libDir)/floatMathLib.a: $(floatObj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(p32ObjDir)/%.o: $(p32SrcDir)/%.c
	@mkdir -p $(p32ObjDir)
	$(CC) \
	-L${HOME}/bin/usr/lib64 \
	-L${HOME}/bin/lib64 \
	-I${HOME}/bin/include \
	-I${HOME}/bin/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include \
	-std=c11 -O3 -c $^ -Iinclude/ -I$(SOFTPOSITPATH)/source/include -o $@

$(libDir)/posit32MathLib.a: $(p32Obj)
	@mkdir -p $(libDir) 
	ar rc  $@ $^ $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a

floatmlib: $(libDir)/floatMathLib.a

posit32mlib: $(libDir)/posit32MathLib.a

clean:
	rm -rf obj lib *.dSYM
