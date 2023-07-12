/* utils.h */
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define TRUE		1
#define FALSE		0
#define BYTE_MAX 	0xFF
#define CHAR_MIN 	(-0x80)
#define CHAR_MAX	0x7F

#ifndef NULL
#ifdef __cplusplus
#define NULL    0 /* Defines NULL in C++*/
#else
#define NULL    ((void *)0) /* Defines NULL in C*/
#endif
#endif

#if !defined(TRUE)
#define TRUE 1 /* Defines TRUE */
#endif
#if !defined(FALSE)
#define FALSE 0 /* Defines FALSE*/
#endif
#if defined _WIN32
typedef unsigned int uint;
#else
#include <sys/types.h>
#endif
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef float real32;
typedef double real64;
typedef unsigned char boolean;
typedef signed long long int64;
typedef unsigned long long uint64;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BOOL;
typedef unsigned char boolean;

// float with 64bits or 32bits precision
#ifdef F_DOUBLE_PRECISION
typedef double freal;
#else
typedef float freal;
#endif

#define DEBUG_PRINT(...) \
    do { \
        fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)

extern uint32 util_rand(uint32 seed);

#ifdef CUSTOM_RAND
#define rand(s) util_rand(s)
#endif

#ifdef DEBUG_MEMORY
extern void* dbg_malloc(size_t size, char* file, int line);
extern void* dbg_realloc(void* ptr, size_t size, char* file, int line);
extern void dbg_free(void* ptr, char* file, int line);

#define malloc(s) dbg_malloc(s, __FILE__, __LINE__)
#define realloc(ptr, s) dbg_realloc(ptr, s, __FILE__, __LINE__)
#define free(ptr) dbg_free(ptr, __FILE__, __LINE__)
#endif

extern uint32 randmax(uint32 seed, uint32 max);
extern void bubble_sort(int, int []);
extern void* cAlloc(DWORD size);
extern int fSize(FILE* f);
extern void Free(void* ptr);
extern DWORD strChOc(char* str, char ch);
extern DWORD strLen(char* str);
extern char* itoa(int value);
extern int bit(int index, BYTE* field);
extern int bitSet(int index, BYTE *field);
extern int bitClear(int index, BYTE *field);
extern int bitToggle(int index, BYTE *field);
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

#endif
