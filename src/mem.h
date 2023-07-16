#ifndef _MEM_H_
#define _MEM_H_
#include <stdlib.h>
#include <stdio.h>

void* dbg_malloc(size_t size, char* file, int line);
void* dbg_realloc(void* ptr, size_t size, char* file, int line);
void dbg_free(void* ptr, char* file, int line);

#endif
