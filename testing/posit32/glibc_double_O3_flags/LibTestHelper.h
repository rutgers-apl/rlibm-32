#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <x86intrin.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "softposit.h"

void RunTest(char* FileName) {

  struct stat s;
  unsigned long count = 0;
  unsigned long wrongResult = 0;
  unsigned long totalTime = 0;
  unsigned int t1, t2, dummy;
  
  posit32_t x, res;

  int fd = open(FileName, O_RDONLY);

  // Get Size of oracle file
  int status = fstat(fd, &s);
  size_t file_size = s.st_size;

  // MMap oracle file
  unsigned* oracle = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (oracle == MAP_FAILED) {
    printf("mmap %s failed: %s\n", FileName, strerror(errno));
    exit(0);
  }
  
  for (count = 0x0; count < 0x100000000; count++) {
    x = castP32(count);
    
    // Make sure t2 > t1.
    do {
      t1 = __rdtscp(&dummy);
      double dx = convertP32ToDouble(x);
      double dres = __ELEM__(dx);
      res = convertDoubleToP32(dres);
      t2 = __rdtscp(&dummy);
    } while(t2 <= t1);
      
    totalTime += (t2 - t1);

    posit32_t oracleResult = castP32(oracle[count]);

    // Now check if the two values are exactly the same
    if (!p32_eq(res, oracleResult)) wrongResult++;
  }

  // Un-mmap oracle file
  munmap(oracle, file_size);
  close(fd);
  printf("Aggregate cycles:          %lu\n", totalTime);
  printf("glibc double wrong result: %lu\n", wrongResult);
}
