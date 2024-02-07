#ifndef _BITWISE_H_
#define _BITWISE_H_

#include <string.h>

#define STRUCT_OFFSET(TYPE, ELEMENT) ((size_t)(&(((TYPE*)(0))->ELEMENT)))
#define BITVALUE(V, I) (((V) >> (I) ) & 0x1)

int bit(int index, char* field);
int bit_set(int index, char* field);
int bit_clear(int index, char* field);
int bit_toggle(int index, char* field);
int bytes_compare(char *b0, char* b1, size_t len);
size_t extract_bits_from_bytes(char* src, size_t pos, size_t bits);

#endif
