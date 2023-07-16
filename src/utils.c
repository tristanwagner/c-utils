#include "utils.h"

// allocate mem and set to 0
void *c_alloc(DWORD size) {
  BYTE *res = (BYTE *)malloc(size);
  memset(res, 0, size);
  return res;
}

// just an example on how to open a file
void example_fopen() {
  FILE *f;
  if ((f = fopen("filepath", "rb"))) {
    DEBUG_PRINT("fileSize: %d\n", f_size(f));
  }
}

// return file size
int f_size(FILE *f) {
  int res, original = ftell(f);
  fseek(f, 0, SEEK_END);
  res = ftell(f);
  fseek(f, original, SEEK_SET);
  return res;
}

// count character occurences in string
DWORD str_ch_oc(char *str, char ch) {
  if (!str)
    return 0;
  DWORD c = 0;
  while (*str)
    if (*str++ == ch)
      c++;
  return c;
}

// count character occurences in string
DWORD str_len(char *str) {
  if (!str)
    return 0;
  DWORD c = 0;
  while (*str++)
    c++;
  return c;
}

char *itoa(int value) {
  static char buffer[256];
  int i = 0;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return buffer;
  }

  if (value < 0) {
    buffer[i++] = '-';
    value = -value;
  }

  while (value != 0) {
    int digit = value % 10;
    buffer[i++] = '0' + digit;
    value /= 10;
  }

  buffer[i] = '\0';

  int start = buffer[0] == '-' ? 1 : 0;
  int end = i - 1;

  while (start < end) {
    char tmp = buffer[start];
    buffer[start] = buffer[end];
    buffer[end] = tmp;
    start++;
    end--;
  }

  return buffer;
}

// TODO: support negative numbers
int atoi(const char *s) {
  int n = 0;
  while (1) {
    char c = *s++;
    if (!c)
      break;
    n = 10 * n + (c - '0');
  }
  return n;
}

// return bit value at index of field
int bit(int index, BYTE *field) {
  // get field to the byte containing the bit we are looking for
  // we shift index 3 bits to the right to get the offset for the
  // byte we want
  field += index >> 3;

  // index of the bit in the field from 0 to 7
  index &= 7;
  return (*field & (1 << index)) ? 1 : 0;
}

// set bit to 1 if it is 0
int bit_set(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = (1 << index);
  res = *field & mask;
  *field |= mask;
  return (res) ? 1 : 0;
}

// set bit to 0 if it is 1
int bit_clear(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = ~(1 << index);
  res = *field & mask;
  *field &= mask;
  return (res) ? 1 : 0;
}

int bit_toggle(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = 1 << index;
  res = *field & mask;
  *field ^= mask;
  return (res) ? 1 : 0;
}

// extract bits from bytes
DWORD extract_bits_from_bytes(const BYTE *src, DWORD pos, DWORD bits) {
  DWORD i, res = 0;
  for (i = 0; i < bits; i++)
    if (bit(pos + i, src))
      bit_set(i, (BYTE *)&res);
  return res;
}
