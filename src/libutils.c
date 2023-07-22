#include "libutils.h"
#include <stdio.h>

// return file size
int f_size(FILE *f) {
  int res, original = ftell(f);
  fseek(f, 0, SEEK_END);
  res = ftell(f);
  fseek(f, original, SEEK_SET);
  return res;
}

int f_exist(char *filename) {
  FILE *f = fopen(filename, "rb");
  if (f) {
    fclose(f);
    return TRUE;
  }
  return FALSE;
}
