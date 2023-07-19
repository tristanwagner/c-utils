#ifdef DEBUG_MEMORY
#ifndef _DBG_MEM_H_
#define _DBG_MEM_H_
#include "mem.h"

#define malloc(s) dbg_malloc(s, __FILE__, __LINE__)
#define calloc(c, s) dbg_malloc(c, s, __FILE__, __LINE__)
#define realloc(ptr, s) dbg_realloc(ptr, s, __FILE__, __LINE__)
#define free(ptr) dbg_free(ptr, __FILE__, __LINE__)
#endif
#endif
