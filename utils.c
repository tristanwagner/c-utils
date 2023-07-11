#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "utils.h"

// produces a random number between 0 and 32767
uint32 util_rand(uint32 seed) {
  seed = seed * 1103515245 + 1337;
  return (uint32)(seed / 65536) % 32768;
}

uint32 randmax(uint32 seed, uint32 max) {
  return util_rand(seed) % (max + 1);
}

void bubbleSort(int s, int *a) {
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

// just an example on how to open a file
void exampleFopen(){
  FILE* f;
  if ((f = fopen("filepath", "rb"))){
      DEBUG_PRINT("fileSize: %d\n", fSize(f));
  }
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
  if (!str) return 0;
  DWORD c = 0;
  while (*str)
    if (*str++ == ch)
      c++;
  return c;
}

// count character occurences in string
DWORD strLen(char* str) {
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
int bitSet(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = (1 << index);
  res = *field & mask;
  *field |= mask;
  return (res) ? 1 : 0;
}

// set bit to 0 if it is 1
int bitClear(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = ~(1 << index);
  res = *field & mask;
  *field &= mask;
  return (res) ? 1 : 0;
}

int bitToggle(int index, BYTE *field) {
  int res;
  field += (index >> 3);
  index &= 7;
  BYTE mask = 1 << index;
  res = *field & mask;
  *field ^= mask;
  return (res) ? 1 : 0;
}

// extract bits from bytes
DWORD extractBitsFromBytes(BYTE* src, DWORD pos, DWORD bits) {
  DWORD i, res = 0;
  for (i = 0; i < bits; i++)
    if (bit(pos + i, src))
     bitSet(i, (BYTE*) &res);
  return res;
}

// Queue (linked list)

void QInit(void *head) {
  // Init the first element, head is only a placeholder that hold the queue,
  // to get the first element you will need to do head.next
  ((CQueue *)head)->next=(CQueue *)head;
  ((CQueue *)head)->last=(CQueue *)head;
}

void QInsert(void *entry, void *pred) {
  CQueue *succ;
  succ=((CQueue *)pred)->next;
  ((CQueue *)entry)->last=(CQueue *)pred;
  ((CQueue *)entry)->next=succ;
  succ->last=(CQueue *)entry;
  ((CQueue *)pred)->next=(CQueue *)entry;
}

// insert at end
void QPush(void *entry, void *q) {
  QInsert(entry,((CQueue *) q)->last);
}

// insert at start
void QUnshift(void *entry, void *q) {
  QInsert(entry, q);
}

//remove queue entry from queue
void QRemove(void *entry) {
  ((CQueue *)entry)->last->next=((CQueue *)entry)->next;
  ((CQueue *)entry)->next->last=((CQueue *)entry)->last;
}

//Free entries in queue, not head.
void QWipe(void *head) {
  CQueue *tmpq=((CQueue *)head)->next,*tmpq1;
  while (tmpq!=head) {
    tmpq1=((CQueue *)tmpq)->next;
    QRemove(tmpq);
    Free(tmpq);
    tmpq=tmpq1;
  }
}

int QCount(void *head)
{
  //Count of nodes in queue, not head.
  CQueue *tmpq=((CQueue *)head)->next;
  int res=0;
  while (tmpq!=head) {
    res++;
    tmpq=((CQueue *)tmpq)->next;
  }
  return res;
}

// for each element in queue, call callback function
// passing pointer of current element
void QForEach(void *head, QCallback cb) {
  CQueue *ptr = ((CQueue *)head)->next;
  while (ptr != head)
  {
    cb(ptr);
    ptr = ptr->next;
  }
}

typedef struct Test Test;

typedef struct Test {
    Test *next, *last;
    int value;
} Test;

void print(void *ptr){
    Test *item = (Test *) ptr;
    DEBUG_PRINT("value: %d | next: %d | last: %d\n", item->value, item->next->value, item->last->value);
}

void add(void *ptr){
    Test *item = (Test *) ptr;
    item->value += 1;
}

int main(){
    BYTE s[50];
    snprintf(s, sizeof s, "LHELLLLLLLLLLLO");
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", strChOc(s, 'L'));
    DEBUG_PRINT("%d\n", bit(80, s));
    bitSet(80, &s);
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", bit(80, s));
    bitClear(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    bitToggle(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", extractBitsFromBytes("AAA", 4, 4));
    DEBUG_PRINT("strlen %s: %d\n", s, strLen(s));
    DEBUG_PRINT("strlen %s: %d\n", "hello", strLen("hello"));
    int a = 3499995;
    char* t = itoa(a);
    DEBUG_PRINT("strlen %s: %d\n", t, strLen(t));

    int b = -3499995;
    char* tt = itoa(b);
    DEBUG_PRINT("strlen %s: %d\n", tt, strLen(tt));
    Test list;
    QInit(&list);

    DEBUG_PRINT("%d\n", list.value);

    for (size_t i = 0; i < 10; i++)
    {
        Test *tmp = (Test *) malloc(sizeof(Test));
        tmp->value = i;
        QPush(tmp, &list);
    }

    Test *addHead = (Test *) malloc(sizeof(Test));
    addHead->value = 10;
    QUnshift(addHead, &list);

    Test *ptr;
    ptr = list.next;

    QForEach(&list, print);

    QForEach(&list, add);

    QForEach(&list, print);

    DEBUG_PRINT("List item count: %d\n", QCount(&list));

    QWipe(&list);

    DEBUG_PRINT("List item count: %d\n", QCount(&list));

    Test *add = (Test *) malloc(sizeof(Test));
    add->value = 1;

    QInsert(add, list.last);

    DEBUG_PRINT("List item count: %d\n", QCount(&list));

    QForEach(&list, print);

}
