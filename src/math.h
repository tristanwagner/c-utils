#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"
#include "debug.h"
/* #define DEBUG_MEMORY */
/* #include "dbg_mem.h" */

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef EPSILON
#define EPSILON 0.000001f
#endif

#define DEG2RAD(deg) ((deg) * (PI/180.0f))
#define RAD2DEG(rad) ((rad) * (180.0f/PI))

#define BYTE_MAX  0xFF
#define CHAR_MIN  (-0x80)
#define CHAR_MAX  0x7F
#define LBYTE(x) ((unsigned char) ((x) & BYTE_MAX))
#define HBYTE(x) ((unsigned char) ((x) >> 8 & BYTE_MAX))

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

#define CLAMP(V, MIN, MAX) ((V) > (MAX) ? (MAX) : (V) < (MIN) ? (MIN) : (V))

uint32 util_rand(uint32 seed);
uint32 rand_max(uint32 seed, uint32 max);

#ifdef CUSTOM_RAND
#define rand(s) util_rand(s)
#endif

int factorial(int n);
void bubble_sort(int, int []);

real32 SQRTF(real32 number);
real32 FABS(real32 number);

// vectors
// h high
// l low
uint8* cvector(long nl, long nh);
void free_cvector(uint8* a, long nl);
int* ivector(long nl, long nh);
void free_ivector(int* a, long nl);
long* lvector(long nl, long nh);
void free_lvector(long* a, long nl);
real32* vector(long nl, long nh);
void free_vector(real32* a, long nl);
real64* dvector(long nl, long nh);
void free_dvector(real64* a, long nl);

// matrix
// r row
// c column
real32** matrix(long nrl, long nrh, long ncl, long nch);
void free_matrix(real32** a, long nrl, long ncl);
real64** dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(real64** a, long nrl, long ncl);
int** imatrix(long nrl, long nrh, long ncl, long nch);
void free_imatrix(int** a, long nrl, long ncl);
real32** sub_matrix(real32** a, long oldnrl, long oldnrh, long oldncl,
  long oldnch, long newnrl, long newnrh, long newncl, long newnch);
real32** convert_matrix(real32* a, long nrl, long nrh, long ncl, long nch);

// tensor
// d depth
real32*** f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_f3tensor(real32*** a, long nrl, long ncl, long ndl);

#endif
