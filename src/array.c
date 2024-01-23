#include "array.h"
#include "debug.h"

void *array_init(size_t item_size, size_t capacity) {
  void *ptr = 0;
  size_t size = item_size * capacity + sizeof(array_header);
  array_header *h = malloc(size);

  if (h) {
    h->length = 0;
    h->capacity = capacity;
    ptr = h + 1;
  }

  return ptr;
}

void *array_ensure_capacity(void *arr, size_t item_count, size_t item_size) {
  array_header *h = array_get_header(arr);
  size_t desired_capacity = h->length + item_count;

  if (h->capacity < desired_capacity) {
    size_t new_capacity = h->capacity * 2;
    while (new_capacity < desired_capacity) {
      new_capacity *= 2;
    }

    size_t new_size = item_size * new_capacity + sizeof(array_header);
    array_header *new_h = malloc(new_size);

    if (new_h) {
      size_t old_size = h->length * item_size + sizeof(*h);
      memcpy(new_h, h, old_size);
      free(h);
      new_h->capacity = new_capacity;
      h = new_h;
    } else {
      h = 0;
    }
  }

  return h + 1;
}
