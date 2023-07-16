#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdlib.h>

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
typedef unsigned char BOOL;
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
typedef unsigned char boolean;

// float with 64bits or 32bits precision
#ifdef F_DOUBLE_PRECISION
typedef double freal;
#else
typedef float freal;
#endif

#endif
