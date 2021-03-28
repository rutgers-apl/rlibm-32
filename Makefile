CC = gcc
CXX = g++

bf16FNames = log log2 log10 sinpi cospi sqrt cbrt exp exp2 exp10
p16FNames = cospi log log2 log10 sinpi sqrt exp exp2 exp10
floatFNames = log log2 log10 exp exp2 exp10 sinh cosh sinpi cospi log2_8 log10_8 
p32FNames = log2 log log10 exp2 exp exp10 sinh cosh_1212 cosh_1412

bf16SrcDir = source/bfloat16
bf16ObjDir = obj/bfloat16
p16SrcDir = source/posit16
p16ObjDir = obj/posit16
floatSrcDir = source/float
floatObjDir = obj/float
p32SrcDir = source/posit32
p32ObjDir = obj/posit32
libDir = lib

bf16Src = $(patsubst %, $(bf16SrcDir)/%.cpp, $(bf16FNames))
bf16Obj = $(patsubst %, $(bf16ObjDir)/%.o, $(bf16FNames))
p16Src = $(patsubst %, $(p16SrcDir)/%.c, $(p16FNames))
p16Obj = $(patsubst %, $(p16ObjDir)/%.o, $(p16FNames))
floatSrc = $(patsubst %, $(floatSrcDir)/%.c, $(floatFNames))
floatObj = $(patsubst %, $(floatObjDir)/%.o, $(floatFNames))
p32Src = $(patsubst %, $(p32SrcDir)/%.c, $(p32FNames))
p32Obj = $(patsubst %, $(p32ObjDir)/%.o, $(p32FNames))

all: $(libDir)/bfloat16MathLib.a $(libDir)/posit16MathLib.a $(libDir)/floatMathLib.a $(libDir)/posit32MathLib.a

$(bf16ObjDir)/%.o: $(bf16SrcDir)/%.cpp
	@mkdir -p $(bf16ObjDir)
	$(CXX) -std=c++11 -O3 -c $^ -Iinclude/ -o $@

$(libDir)/bfloat16MathLib.a: $(bf16Obj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(p16ObjDir)/%.o: $(p16SrcDir)/%.c
	@mkdir -p $(p16ObjDir)
	$(CC) -std=c11 -O3 -c $^ -Iinclude/ -I$(SOFTPOSITPATH)/source/include -o $@

$(libDir)/posit16MathLib.a: $(p16Obj)
	@mkdir -p $(libDir) 
	ar rc  $@ $^ $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a 

$(floatObjDir)/%.o: $(floatSrcDir)/%.c
	@mkdir -p $(floatObjDir)
	$(CC) -std=c11 -O3 -c $^ -Iinclude/ -o $@

$(libDir)/floatMathLib.a: $(floatObj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(p32ObjDir)/%.o: $(p32SrcDir)/%.c
	@mkdir -p $(p32ObjDir)
	$(CC) -std=c11 -O3 -c $^ -Iinclude/ -I$(SOFTPOSITPATH)/source/include -o $@

$(libDir)/posit32MathLib.a: $(p32Obj)
	@mkdir -p $(libDir) 
	ar rc  $@ $^ $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a 

bfloat16mlib: $(libDir)/bfloat16MathLib.a

posit16mlib: $(libDir)/posit16MathLib.a

floatmlib: $(libDir)/floatMathLib.a

posit32mlib: $(libDir)/posit32MathLib.a

clean:
	rm -rf obj lib *.dSYM
