#include "mem.h"

// TODO: more advanced memory debugging

void *dbg_malloc(size_t size, char *file, int line) {
  fprintf(stderr, "[%s:%d] <malloc> allocated %zu bytes\n", file, line, size);
  void *ptr = malloc(size);
  return ptr;
}

void *dbg_calloc(size_t count, size_t size, char *file, int line) {
  fprintf(stderr, "[%s:%d] <calloc> allocated %zu bytes\n", file, line,
          count * size);
  void *ptr = calloc(count, size);
  return ptr;
}

void *dbg_realloc(void *ptr, size_t size, char *file, int line) {
  fprintf(stderr, "[%s:%d] <realloc> allocated %zu bytes\n", file, line, size);
  return realloc(ptr, size);
}

void dbg_free(void *ptr, char *file, int line) {
  fprintf(stderr, "[%s:%d] <free>\n", file, line);
  free(ptr);
  return;
}

// allocate mem and set to 0
// why does stdlib calloc takes 2 args wtf
void *c_alloc(size_t size) {
  char *res = (char *)malloc(size);
  memset(res, 0, size);
  return res;
}
