#ifndef _U_STRING_H_
#define _U_STRING_H_

#include <string.h>
#include "uerror.h"
/* #define DEBUG_MEMORY */
/* #include "dbg_mem.h" */

typedef struct {
  char **substrings;
  size_t size;
} str_split_result;

size_t str_ch_oc(const char* str, char ch);
size_t str_len(const char* str);
void str_split(str_split_result* result, char *src, char token);
void free_str_split_result(str_split_result *result);
char* itoa(int value);
int atoi(const char* s);
int c_is_separator(int c);
char *str_to_hex(const char *src, size_t len);
// another implementation without std
// seems 2x faster
char *bin_to_hex(const char *src, size_t len);
// TODO: research more * implement
// to lowercased
// to uppercased
// is numeric
// substring
// ends with
// starts with
// concat
// join

#endif
