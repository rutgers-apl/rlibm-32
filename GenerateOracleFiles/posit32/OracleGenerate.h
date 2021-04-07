#include "stdio.h"
#include "posit32_math.h"
#include "softposit.h"
#include "stdlib.h"

void RunTest(char* FileName) {
  
  unsigned long count = 0;
  
  FILE* f = fopen(FileName, "w");
  
  for (count = 0x0; count < 0x100000000; count++) {
    posit32_t x = castP32(count);
    posit32_t res = __ELEM__(x);
    unsigned bitrep = res.v;

    fwrite(&bitrep, sizeof(unsigned), 1, f);
  }

  fclose(f);
}
