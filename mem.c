#include <stdlib.h>
#include <stdio.h>

void* dbg_malloc(size_t size, char* file, int line) {
  fprintf(stderr, "[%s:%d] <malloc> allocated %d bytes\n", file, line, size); \
  void* ptr =  malloc(size);
  return ptr;
}

void* dbg_realloc(void* ptr, size_t size, char* file, int line) {
  fprintf(stderr, "[%s:%d] <realloc> allocated %d bytes\n", file, line, size); \
  return realloc(ptr, size);
}

void dbg_free(void* ptr, char* file, int line) {
  fprintf(stderr, "[%s:%d] <free>\n", file, line); \
  return free(ptr);
}
