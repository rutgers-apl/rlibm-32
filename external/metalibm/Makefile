CC = ${LOCAL}/usr/bin/gcc

genericFNames = cosh_float_generic cosh_double_generic exp2_double_generic exp2_float_generic exp_double_generic exp_float_generic log10_double_generic log10_float_generic log2_double_generic log2_float_generic log_double_generic log_float_generic 

x86FNames = cosh_float_x86 cosh_double_x86 exp2_double_x86 exp2_float_x86 exp_double_x86 exp_float_x86 log10_double_x86 log10_float_x86 log2_double_x86 log2_float_x86 log_double_x86 log_float_x86 

avx2FNames = cosh_float_avx2 cosh_double_avx2 exp2_double_avx2 exp2_float_avx2 exp_double_avx2 exp_float_avx2 log10_double_avx2 log10_float_avx2 log2_double_avx2 log2_float_avx2 log_double_avx2 log_float_avx2 


genericSrcDir = GeneratedFunctions/cr/generic
genericObjDir = obj/cr/generic
x86SrcDir = GeneratedFunctions/cr/x86
x86ObjDir = obj/cr/x86
avx2SrcDir = GeneratedFunctions/cr/avx2
avx2ObjDir = obj/cr/avx2
libDir = lib

genericSrc = $(patsubst %, $(genericSrcDir)/%.c, $(genericFNames))
genericObj = $(patsubst %, $(genericObjDir)/%.o, $(genericFNames))
x86Src = $(patsubst %, $(x86SrcDir)/%.c, $(x86FNames))
x86Obj = $(patsubst %, $(x86ObjDir)/%.o, $(x86FNames))
avx2Src = $(patsubst %, $(avx2SrcDir)/%.c, $(avx2FNames))
avx2Obj = $(patsubst %, $(avx2ObjDir)/%.o, $(avx2FNames))

all: $(libDir)/genericMath.a $(libDir)/x86Math.a $(libDir)/avx2Math.a

$(genericObjDir)/%.o: $(genericSrcDir)/%.c
	@mkdir -p $(genericObjDir)
	$(CC) -static \
        -L${LOCAL}/usr/lib64 \
        -L${LOCAL}/bin/lib64 \
        -I${LOCAL}/bin/include \
        -I${LOCAL}/bin/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include \
        -std=c11 -O3 -c $^ -Isupport_lib/ -o $@

$(libDir)/genericMath.a: $(genericObj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(x86ObjDir)/%.o: $(x86SrcDir)/%.c
	@mkdir -p $(x86ObjDir)
	$(CC) -static \
        -L${LOCAL}/usr/lib64 \
        -L${LOCAL}/bin/lib64 \
        -I${LOCAL}/bin/include \
        -I${LOCAL}/bin/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include \
        -std=c11 -O3 -c $^ -Isupport_lib/ -o $@

$(libDir)/x86Math.a: $(x86Obj)
	@mkdir -p $(libDir)
	ar rc $@ $^

$(avx2ObjDir)/%.o: $(avx2SrcDir)/%.c
	@mkdir -p $(avx2ObjDir)
	$(CC) -static \
        -L${LOCAL}/usr/lib64 \
        -L${LOCAL}/bin/lib64 \
        -I${LOCAL}/bin/include \
        -I${LOCAL}/bin/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include \
        -std=c11 -O3 -march=skylake -c $^ -Isupport_lib/ -o $@

$(libDir)/avx2Math.a: $(avx2Obj)
	@mkdir -p $(libDir)
	ar rc $@ $^

clean:
	rm -rf obj lib *.dSYM
