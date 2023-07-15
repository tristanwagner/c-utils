#include "utils.h"

// produces a random number between 0 and 32767
uint32 util_rand(uint32 seed) {
  seed = seed * 1103515245 + 1337;
  return (uint32)(seed / 65536) % 32768;
}

uint32 rand_max(uint32 seed, uint32 max) {
  return util_rand(seed) % (max + 1);
}

void bubble_sort(int s, int* a) {
  int x,y,t;
   for (x=0; x < s-1; x++) {
      for (y=0; y < s-x-1; y++) {
          if (a[y] > a[y+1]) {
              t=a[y];
              a[y]=a[y+1];
              a[y+1]=t;
          }
      }
   }
}

// allocate mem and set to 0
void* c_alloc(DWORD size) {
  BYTE* res = (BYTE*) malloc(size);
  memset(res, 0, size);
  return res;
}

// just an example on how to open a file
void example_fopen(){
  FILE* f;
  if ((f = fopen("filepath", "rb"))){
      DEBUG_PRINT("fileSize: %d\n", f_size(f));
  }
}

// return file size
int f_size(FILE* f) {
  int res, original = ftell(f);
  fseek(f, 0, SEEK_END);
  res = ftell(f);
  fseek(f, original, SEEK_SET);
  return res;
}

// count character occurences in string
DWORD str_ch_oc(char* str, char ch) {
  if (!str) return 0;
  DWORD c = 0;
  while (*str)
    if (*str++ == ch)
      c++;
  return c;
}

// count character occurences in string
DWORD str_len(char* str) {
  if (!str) return 0;
  DWORD c = 0;
  while (*str++)
    c++;
  return c;
}

char* itoa(int value) {
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

// return bit value at index of field
int bit(int index, BYTE* field)
{
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
DWORD extract_bits_from_bytes(BYTE* src, DWORD pos, DWORD bits) {
  DWORD i, res = 0;
  for (i = 0; i < bits; i++)
    if (bit(pos + i, src))
     bit_set(i, (BYTE*) &res);
  return res;
}

// vectors
#define V_END 1
#define FREE_ARG char*

uint8* cvector(long nl, long nh){
  uint8* v;
  v = (uint8*) malloc((size_t) ((nh - nl + 1 + V_END)* sizeof(uint8)));
  if (!v) DEBUG_PRINT("failed allocation using cvector(%lg, %lg)\n", nl, nh);
  return v;
};

void free_cvector(uint8* a, long nl) {
  free((FREE_ARG) a+nl-V_END);
};

int* ivector(long nl, long nh){
  int* v;
  v = (int*) malloc((size_t) ((nh - nl + 1 + V_END)* sizeof(int)));
  if (!v) DEBUG_PRINT("failed allocation using ivector(%lg, %lg)\n", nl, nh);
  return v;
};

void free_ivector(int* a, long nl) {
  free((FREE_ARG) a+nl-V_END);
};

long* lvector(long nl, long nh){
  long* v;
  v = (long*) malloc((size_t) ((nh - nl + 1 + V_END)* sizeof(long)));
  if (!v) DEBUG_PRINT("failed allocation using lvector(%lg, %lg)\n", nl, nh);
  return v;
};

void free_lvector(long* a, long nl) {
  free((FREE_ARG) a+nl-V_END);
};

real32* vector(long nl, long nh) {
  real32* v;
  v = (real32*) malloc((size_t) ((nh - nl + 1 + V_END)* sizeof(real32)));
  if (!v) DEBUG_PRINT("failed allocation using vector(%lg, %lg)\n", nl, nh);
  return v;
};

void free_vector(real32* a, long nl) {
  free((FREE_ARG) a+nl-V_END);
};

real64* dvector(long nl, long nh) {
  real64* v;
  v = (real64*) malloc((size_t) ((nh - nl + 1 + V_END)* sizeof(real64)));
  if (!v) DEBUG_PRINT("failed allocation using dvector(%lg, %lg)\n", nl, nh);
  return v;
};

void free_dvector(real64* a, long nl) {
  free((FREE_ARG) a+nl-V_END);
};

// matrix

real32** matrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  real32** m;

  m = (real32**) malloc((size_t) ((nrow + V_END) * sizeof(real32*)));
  if (!m) DEBUG_PRINT("failed allocation using matrix(%lg, %lg, %lg, %lg) on row level\n", nrl, nrh, ncl, nch);
  m += V_END;
  m -= nrl;
  m[nrl] = (real32*) malloc((size_t) ((nrow * ncol + V_END) * sizeof(real32)));
  if (!m[nrl]) DEBUG_PRINT("failed allocation using matrix(%lg, %lg, %lg, %lg) on col level\n", nrl, nrh, ncl, nch);
  m[nrl] += V_END;
  m[nrl] -= ncl;

  for (i = nrl + 1;i <= nrh;i++) m[i] = m[i-1] + ncol;

  return m;
}

void free_matrix(real32** a, long nrl, long ncl) {
  free((FREE_ARG) (a[nrl] + ncl - V_END));
  free((FREE_ARG) (a + nrl - V_END));
};

