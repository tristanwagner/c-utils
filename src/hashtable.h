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
} ht;

ht* ht_new();
ht* ht_new_sized(int base_size);
static ht_item* ht_new_item(const char* k, const char* v);
static void ht_del_item(ht_item* i);
static void ht_del_table(ht* t);

void ht_insert(ht* t, const char* key, const char* value);
char* ht_get(ht* t, const char* key);
void ht_delete(ht* t, const char* key);

static void ht_resize(ht *t, const int base_size);
static void ht_resize_up(ht *t);
static void ht_resize_down(ht *t);

#endif
