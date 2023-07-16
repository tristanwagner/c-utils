#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define DEBUG_MEMORY
#include "dbg_mem.h"
#include "types.h"
#include "benchmark.h"
#include "debug.h"
#include "queue.h"
#include "task.h"
#include "math.h"

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
