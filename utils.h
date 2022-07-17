/* utils.h */
#define TRUE		1
#define FALSE		0
#define BYTE_MAX 	0xFF
#define CHAR_MIN 	(-0x80)
#define CHAR_MAX	0x7F

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BOOL;

extern int rand();
extern int randmax(int max);
extern void bubble_sort(int, int []);
extern void* cAlloc(DWORD size);
extern int fSize(FILE* f);
extern void Free(void* ptr);
extern DWORD strChOc(char* str, char ch);
extern DWORD strLen(char* str);
extern char* itoa(int value);
extern int bit(int index, BYTE* field);
extern int bitSet(int index, BYTE *field);
extern DWORD extractBitsFromBytes(BYTE* src, DWORD pos, DWORD bits);

typedef struct CQueue CQueue;
typedef struct CQueue
{
    CQueue *next;
    CQueue *last;
} CQueue;
typedef void (*QCallback)(void *);

extern void QInit(void *head);
extern void QInsert(void *entry, void *pred);
extern void QPush(void *entry, void *q);
extern void QUnshift(void *entry, void *q);
extern void QRemove(void *entry);
extern void QWipe(void *head);
extern int QCount(void *head);
extern void QForEach(void *head, QCallback cb);