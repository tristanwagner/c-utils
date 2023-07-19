#ifndef _BITWISE_H_
#define _BITWISE_H_

#include <stddef.h>

int bit(int index, char* field);
int bit_set(int index, char* field);
int bit_clear(int index, char* field);
int bit_toggle(int index, char* field);
size_t extract_bits_from_bytes(char* src, size_t pos, size_t bits);

#endif
