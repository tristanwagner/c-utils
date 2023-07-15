#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "benchmark.h"
#include "debug.h"
#include "queue.h"

// TODO:
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
#include "mem.h"

#define malloc(s) dbg_malloc(s, __FILE__, __LINE__)
#define realloc(ptr, s) dbg_realloc(ptr, s, __FILE__, __LINE__)
#define free(ptr) dbg_free(ptr, __FILE__, __LINE__)
#endif
#define BYTE_MAX  0xFF
#define CHAR_MIN  (-0x80)
#define CHAR_MAX  0x7F

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

#if defined(_WIN32)
typedef unsigned int uint;
#elif defined(unix)
#elif defined(__APPLE__)
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

extern uint32 util_rand(uint32 seed);

#ifdef CUSTOM_RAND
#define rand(s) util_rand(s)
#endif

// maths
static real32 sqra;
#define SQR(a) ((sqra=(a)) == 0.0 ? 0.0 : sqra*sqra)
static real32 maxa, maxb;
#define FMAX(a, b) (maxa=(a), maxb=(b), (maxa) > (maxb) ?\
      (maxa) : (maxb))
static real32 mina, minb;
#define FMIN(a, b) (mina=(a), minb=(b), (mina) < (minb) ?\
      (mina) : (minb))
static real64 dsqra;
#define DSQR(a) ((dsqra=(a)) == 0.0 ? 0.0 : dsqra*dsqra)
static real64 dmaxa, dmaxb;
#define DMAX(a, b) (dmaxa=(a), dmaxb=(b), (dmaxa) > (dmaxb) ?\
      (dmaxa) : (dmaxb))
static real64 dmina, dminb;
#define DMIN(a, b) (dmina=(a), dminb=(b), (dmina) < (dminb) ?\
      (dmina) : (dminb))
static long lmaxa, lmaxb;
#define LMAX(a, b) (lmaxa=(a), lmaxb=(b), (lmaxa) > (lmaxb) ?\
      (lmaxa) : (lmaxb))
static long lmina, lminb;
#define LMIN(a, b) (lmina=(a), lminb=(b), (lmina) < (lminb) ?\
      (lmina) : (lminb))
static int imaxa, imaxb;
#define IMAX(a, b) (imaxa=(a), imaxb=(b), (imaxa) > (imaxb) ?\
      (imaxa) : (imaxb))
static int imina, iminb;
#define IMIN(a, b) (imina=(a), iminb=(b), (imina) < (iminb) ?\
      (imina) : (iminb))

extern void uerror(char message[]);
extern uint32 rand_max(uint32 seed, uint32 max);
extern void bubble_sort(int, int []);
extern void* c_alloc(DWORD size);
extern int f_size(FILE* f);
extern DWORD str_ch_oc(char* str, char ch);
extern DWORD str_len(char* str);
extern char* itoa(int value);
extern int bit(int index, BYTE* field);
extern int bit_set(int index, BYTE* field);
extern int bit_clear(int index, BYTE* field);
extern int bit_toggle(int index, BYTE* field);
extern DWORD extract_bits_from_bytes(BYTE* src, DWORD pos, DWORD bits);

// vectors
// h high
// l low
extern uint8* cvector(long nl, long nh);
extern void free_cvector(uint8* a, long nl);
extern int* ivector(long nl, long nh);
extern void free_ivector(int* a, long nl);
extern long* lvector(long nl, long nh);
extern void free_lvector(long* a, long nl);
extern real32* vector(long nl, long nh);
extern void free_vector(real32* a, long nl);
extern real64* dvector(long nl, long nh);
extern void free_dvector(real64* a, long nl);

// matrix
// r row
// c column
extern real32** matrix(long nrl, long nrh, long ncl, long nch);
extern void free_matrix(real32** a, long nrl, long ncl);

#endif
