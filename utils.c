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

// just an example on how to open a file
void exampleFopen(){
    FILE* f;
    if (f = fopen("filepath", "rb")){
        printf("fileSize: %d\n", fSize(f));
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
    char buffer[256];
    sprintf(buffer, "%d\0", value);
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
         bitSet(i, (BYTE*) &res);
    return res;
}

// Queue (linked list)

void QInit(void *head)
{// Init the first element, head is only a placeholder that hold the queue,
// to get the first element you will need to do head.next
    ((CQueue *)head)->next=(CQueue *)head;
    ((CQueue *)head)->last=(CQueue *)head;
}

void QInsert(void *entry, void *pred)
{
    CQueue *succ;
    succ=((CQueue *)pred)->next;
    ((CQueue *)entry)->last=(CQueue *)pred;
    ((CQueue *)entry)->next=succ;
    succ->last=(CQueue *)entry;
    ((CQueue *)pred)->next=(CQueue *)entry;
}

// insert at end
void QPush(void *entry, void *q)
{
    QInsert(entry,((CQueue *) q)->last);
}

// insert at start
void QUnshift(void *entry, void *q)
{
    QInsert(entry, q);
}

//remove queue entry from queue
void QRemove(void *entry)
{
    ((CQueue *)entry)->last->next=((CQueue *)entry)->next;
    ((CQueue *)entry)->next->last=((CQueue *)entry)->last;
    // should free here or let user do ?
}

void QWipe(void *head)
{//Free entries in queue, not head.
    CQueue *tmpq=((CQueue *)head)->next,*tmpq1;
    while (tmpq!=head) {
        tmpq1=((CQueue *)tmpq)->next;
        QRemove(tmpq);
        Free(tmpq);
        tmpq=tmpq1;
    }
}

int QCount(void *head)
{//Count of nodes in queue, not head.
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

/*
typedef struct Test Test;

typedef struct Test {
    Test *next, *last;
    int value;
} Test;

void print(void *ptr){
    Test *item = (Test *) ptr;
    printf("value: %d | next: %d | last: %d\n", item->value, item->next->value, item->last->value);
}

void add(void *ptr){
    Test *item = (Test *) ptr;
    item->value += 1;
}

int main(){
    char* s = "LHELLLLLLLLLLLO";
    printf("%s\n", s);
    printf("%d\n", strChOc(s, 'L'));
    printf("%d\n", bit(80, s));
    bitSet(80, s);
    printf("%d\n", bit(80, s));
    bitSet(80, s);
    printf("%d\n", bit(80, s));
    printf("%s\n", s);
    printf("%d\n", extractBitsFromBytes("AAA", 4, 4));
    printf("strlen %s: %d\n", s, strLen(s));
    printf("strlen %s: %d\n", "hello", strLen("hello"));
    int a = 3499995;
    char* t = itoa(a);
    printf("strlen %s: %d\n", t, strLen(t));

    Test list;
    QInit(&list);

    printf("%d\n", list.value);

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

    printf("List item count: %d\n", QCount(&list));
        
    QWipe(&list);

    printf("List item count: %d\n", QCount(&list));

    Test *add = (Test *) malloc(sizeof(Test));
    add->value = 1;

    QInsert(add, list.last);
    
    printf("List item count: %d\n", QCount(&list));

    QForEach(&list, print);

} */