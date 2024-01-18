#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "prime.h"

#define HT_INITIAL_BASE_SIZE 50

typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  int base_size;
  int size;
  int count;
  ht_item** items;
} ht_table;

ht_table* ht_new();
ht_table* ht_new_sized(int base_size);
static ht_item* ht_new_item(const char* k, const char* v);
static void ht_del_item(ht_item* i);
static void ht_del_table(ht_table* t);

void ht_insert(ht_table* ht, const char* key, const char* value);
char* ht_get(ht_table* ht, const char* key);
void ht_delete(ht_table* h, const char* key);

static void ht_resize(ht_table *ht, const int base_size);
static void ht_resize_up(ht_table *ht);
static void ht_resize_down(ht_table *ht);

#endif
