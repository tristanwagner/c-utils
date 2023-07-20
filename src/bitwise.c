#include "bitwise.h"

// return bit value at index of field
int bit(int index, char *field) {
  // get field to the byte containing the bit we are looking for
  // we shift index 3 bits to the right to get the offset for the
  // byte we want
  field += index >> 3;

  // index of the bit in the field from 0 to 7
  index &= 7;
  return (*field & (1 << index)) ? 1 : 0;
}

// set bit to 1 if it is 0
int bit_set(int index, char *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  char mask = (1 << index);
  res = *field & mask;
  *field |= mask;
  return (res) ? 1 : 0;
}

// set bit to 0 if it is 1
int bit_clear(int index, char *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  char mask = ~(1 << index);
  res = *field & mask;
  *field &= mask;
  return (res) ? 1 : 0;
}

int bit_toggle(int index, char *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  char mask = 1 << index;
  res = *field & mask;
  *field ^= mask;
  return (res) ? 1 : 0;
}

int bytes_compare(char *b0, char *b1, size_t len) {
  return 0 == memcmp(b0, b1, len);
}

// extract bits from bytes
size_t extract_bits_from_bytes(char *src, size_t pos, size_t bits) {
  size_t i, res = 0;
  for (i = 0; i < bits; i++)
    if (bit(pos + i, src))
      bit_set(i, (char *)&res);
  return res;
}
