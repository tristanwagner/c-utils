#ifndef _TYPES_H_
#define _TYPES_H_

#include <stddef.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0 /* Defines NULL in C++*/
#define false   0
#define true    1
typedef bool               b8;
#else
#define NULL    ((void *)0) /* Defines NULL in C*/
#ifndef __bool_true_false_are_defined
typedef _Bool              bool;
#endif
typedef bool               b8;
#endif
#endif

#if !defined(TRUE)
#define TRUE 1 /* Defines TRUE */
#endif
#if !defined(FALSE)
#define FALSE 0 /* Defines FALSE*/
#endif

typedef signed char        int8;
typedef unsigned char      uint8;
typedef signed short       int16;
typedef unsigned short     uint16;
typedef signed int         int32;
typedef unsigned int       uint32;
typedef float              real32;
typedef double             real64;
typedef signed long long   int64;
typedef unsigned long long uint64;

typedef int8               int8_t;
typedef uint8              uint8_t;
typedef int16              int16_t;
typedef uint16             uint16_t;
typedef int32              int32_t;
typedef uint32             uint32_t;
typedef int64              int64_t;
typedef uint64             uint64_t;

typedef uint8_t            u8;
typedef int8_t             s8;
typedef uint16_t           u16;
typedef int16_t            s16;
typedef uint32_t           u32;
typedef int32_t            s32;
typedef s32                b32;
typedef uint64_t           u64;
typedef int64_t            s64;
typedef float              f32;
typedef double             f64;
typedef const char*        const_str;

typedef int32_t            bool32_t;
typedef float              float32_t;
typedef double             float64_t;

typedef bool32_t           bool32;

typedef unsigned char      BYTE;
typedef unsigned short     WORD;
typedef unsigned int       DWORD;
typedef unsigned char      boolean;

typedef size_t             usize;

#define uint16_max         UINT16_MAX
#define uint32_max         UINT32_MAX
#define int32_max          INT32_MAX
#define float_max          FLT_MAX
#define float_min          FLT_MIN

// float with 64bits or 32bits precision
#define F_DOUBLE_PRECISION
#ifdef F_DOUBLE_PRECISION
typedef double freal;
#else
typedef float freal;
#endif

#endif
