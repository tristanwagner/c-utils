#include <stdio.h>
#include "utils.h"

int rand_seed=10;

// produces a random number between 0 and 32767
int rand()
{
    rand_seed = rand_seed * 1103515245 + 1337;
    return (unsigned int)(rand_seed / 65536) % 32768;
}

int randmax(int max) {
    return rand() % (max + 1);
}

void bubbleSort(int s, int *a)
{
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
void* cAlloc(DWORD size) {
  BYTE* res = (BYTE*) malloc(size);
  memset(res, 0, size);
  return res;
}

// return file size
int fSize(FILE* f) {
    int res, original = ftell(f);
    fseek(f, 0, SEEK_END);
    res = ftell(f);
    fseek(f, original, SEEK_SET);
    return res;
}

void Free(void* ptr) {
    if (ptr) free(ptr);
}

// count character occurences in string
DWORD strChOc(char* str, char ch) {
    DWORD c = 0;
    if (!str) return 0;
    while (*str)
        if (*str++ == ch)
            c++;
    return c;
}

// return bit value at index of field
int bit(int index, BYTE* field)
{
  // get field to the byte containing the bit we are looking for
  field += index >> 3;
  // index cannot be more than 7 ?
  index &= 7;
  return (*field & (1 << index)) ? 1 : 0;
}

// switch bit to 1 if it is 0
int bitSwitch(int index, BYTE *field) {
  int res;
  field += index >> 3;
  index &= 7;
  res = *field & (1 << index);
  *field |= (1 << index);
  return (res) ? 1 : 0;
}

// extract bits from bytes
DWORD extractBitsFromBytes(BYTE* src, DWORD pos, DWORD bits) {
    DWORD i, res = 0;
    for (i = 0; i < bits; i++)
        if (bit(pos + i, src))
            bitSwitch(i, (BYTE*) &res);
    return res;
}

int main(){
    char* s = "HELLLLLLLLLLLO";
    printf("%s\n", s);
    printf("%d\n", strChOc(s, 'L'));
    printf("%d\n", bit(80, s));
    bitSwitch(80, s);
    printf("%d\n", bit(80, s));
    bitSwitch(80, s);
    printf("%d\n", bit(80, s));
    printf("%s\n", s);
    printf("%d\n", extractBitsFromBytes("AAA", 4, 4));
}