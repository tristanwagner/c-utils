#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdlib.h>
#include <string.h>

#define ARRAY_INITIAL_CAPACITY 2

#define array(T) array_init(sizeof(T), ARRAY_INITIAL_CAPACITY)
#define array_get_header(a) ((array_header*)(a) - 1)
#define array_length(a) (array_get_header(a)->length)
#define array_capacity(a) (array_get_header(a)->capacity)

#define array_push(a, v) ( \
    (a) = array_ensure_capacity(a, 1, sizeof(v)), \
    (a)[array_get_header(a)->length] = (v), \
    &(a)[array_get_header(a)->length++])

#define array_remove(a, i) do { \
  array_header* h = array_get_header(a); \
  if (i == h->length - 1) { \
    h->length--; \
  } else if (h->length > 1) { \
    void *ptr = a + i; \
    void *next = a + i + 1; \
    h->length--; \
    memmove(ptr, next, (h->length - i) * sizeof(*a));\
  } \
} while(0);

#define array_pop(a) (array_get_header(a)->length--)

typedef struct {
  size_t length;
  size_t capacity;
} array_header;

void* array_init(size_t item_size, size_t capacity);
void* array_ensure_capacity(void* arr, size_t item_count, size_t item_size);

#endif
