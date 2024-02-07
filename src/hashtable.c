#include "hashtable.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;

static ht_item *ht_new_item(const char *k, const char *v) {
  ht_item *i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);

  return i;
};

ht *ht_new_sized(int base_size) {
  ht *t = malloc(sizeof(ht));
  t->base_size = base_size;
  t->size = next_prime(t->base_size);
  t->count = 0;
  t->items = calloc(t->size, sizeof(ht_item));
  return t;
};

ht *ht_new() { return ht_new_sized(HT_INITIAL_BASE_SIZE); };

static void ht_del_item(ht_item *i) {
  free(i->key);
  free(i->value);
  free(i);
};

static void ht_del_table(ht *t) {
  for (int i = 0; i < t->size; i++) {
    ht_item *item = t->items[i];
    if (item != NULL) {
      ht_del_item(item);
    }
  }

  free(t->items);
  free(t);
};

static int ht_hash(const char *s, const int a, const int max) {
  long hash = 0;
  const int slen = strlen(s);

  for (int i = 0; i < slen; i++) {
    hash = (long)pow(a, slen - (i + 1)) * s[i];
    hash = hash % max;
  }

  return (int)hash;
};

static int ht_get_hash(const char *s, const int nb_buckets, const int attempt) {
  const int hash_a = ht_hash(s, HT_PRIME_1, nb_buckets);
  const int hash_b = ht_hash(s, HT_PRIME_2, nb_buckets);
  return (hash_a * (attempt * (hash_b + 1)) % nb_buckets);
};

void ht_insert(ht *t, const char *key, const char *value) {
  const int load = t->count * 100 / t->size;
  if (load > 70) {
    ht_resize_up(t);
  }
  ht_item *item = ht_new_item(key, value);
  int index = ht_get_hash(key, t->size, 0);
  ht_item *current_item = t->items[index];
  int i = 1;
  while (current_item != NULL) {

    if (current_item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        ht_del_item(current_item);
        t->items[index] = item;
        return;
      }
    }
    index = ht_get_hash(key, t->size, i);
    current_item = t->items[index];
    i++;
  }
  t->items[index] = item;
  t->count++;
};

char *ht_get(ht *t, const char *key) {
  int index = ht_get_hash(key, t->size, 0);
  ht_item *item = t->items[index];
  int i = 1;
  while (item != NULL) {
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        return item->value;
      }
    }
    index = ht_get_hash(key, t->size, i);
    item = t->items[index];
    i++;
  }
  return NULL;
};

void ht_delete(ht *t, const char *key) {
  const int load = t->count * 100 / t->size;
  if (load < 10) {
    ht_resize_down(t);
  }
  int index = ht_get_hash(key, t->size, 0);
  ht_item *item = t->items[index];
  int i = 1;
  while (item != NULL) {
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        ht_del_item(item);
        t->items[index] = &HT_DELETED_ITEM;
      }
    }
    index = ht_get_hash(key, t->size, i);
    item = t->items[index];
    i++;
  }
  t->count--;
};

static void ht_resize(ht *t, const int base_size) {
  if (base_size < HT_INITIAL_BASE_SIZE) {
    return;
  }

  ht *new_t = ht_new_sized(base_size);

  for (int i = 0; i < t->size; i++) {
    ht_item *item = t->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM) {
      ht_insert(new_t, item->key, item->value);
    }
  }

  t->base_size = new_t->base_size;
  t->count = new_t->count;

  const int tmp_size = t->size;
  t->size = new_t->size;
  new_t->size = tmp_size;

  ht_item **tmp_items = t->items;
  t->items = new_t->items;
  new_t->items = tmp_items;

  ht_del_table(new_t);
};

static void ht_resize_up(ht *t) {
  const int new_size = t->base_size * 2;
  ht_resize(t, new_size);
};
static void ht_resize_down(ht *t) {
  const int new_size = t->base_size / 2;
  ht_resize(t, new_size);
};
