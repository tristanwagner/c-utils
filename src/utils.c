#include "utils.h"

// just an example on how to open a file
void example_fopen() {
  FILE *f;
  if ((f = fopen("filepath", "rb"))) {
    DEBUG_PRINT("fileSize: %d\n", f_size(f));
  }
}

// return file size
int f_size(FILE *f) {
  int res, original = ftell(f);
  fseek(f, 0, SEEK_END);
  res = ftell(f);
  fseek(f, original, SEEK_SET);
  return res;
}
