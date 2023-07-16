#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "types.h"
#include "benchmark.h"
#include "debug.h"
#include "queue.h"
#include "task.h"
#include "math.h"

// TODO:
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
#include "mem.h"

#define malloc(s) dbg_malloc(s, __FILE__, __LINE__)
#define realloc(ptr, s) dbg_realloc(ptr, s, __FILE__, __LINE__)
#define free(ptr) dbg_free(ptr, __FILE__, __LINE__)
#endif

void uerror(char message[]);
void* c_alloc(DWORD size);
int f_size(FILE* f);
DWORD str_ch_oc(char* str, char ch);
DWORD str_len(char* str);
char* itoa(int value);
int atoi(const char* s);
int bit(int index, BYTE* field);
int bit_set(int index, BYTE* field);
int bit_clear(int index, BYTE* field);
int bit_toggle(int index, BYTE* field);
DWORD extract_bits_from_bytes(const BYTE* src, DWORD pos, DWORD bits);

#endif
