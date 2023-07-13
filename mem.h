#ifndef _MEM_H_
#define _MEM_H_
extern void* dbg_malloc(size_t size, char* file, int line);
extern void* dbg_realloc(void* ptr, size_t size, char* file, int line);
extern void dbg_free(void* ptr, char* file, int line);
#endif
