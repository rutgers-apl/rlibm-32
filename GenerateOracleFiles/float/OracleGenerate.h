#include "stdio.h"
#include "float_math.h"
#include "stdlib.h"

void RunTest(char* FileName) {
  
  unsigned long count = 0;
  
  float x;
  floatX xbase;

  FILE* f = fopen(FileName, "w");
  
  for (count = 0x0; count < 0x100000000; count++) {
    xbase.x = count;
    x = xbase.f;
    
    float res = __ELEM__(x);

    fwrite(&res, sizeof(float), 1, f);
  }

  fclose(f);
}
