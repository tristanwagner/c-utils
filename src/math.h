#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"
#include "debug.h"

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef EPSILON
#define EPSILON 0.000001f
#endif

#ifndef DEG2RAD
#define DEG2RAD (PI/180.0f)
#endif

#ifndef RAD2DEG
#define RAD2DEG (180.0f/PI)
#endif

#ifndef BYTE_MAX
#define BYTE_MAX  0xFF
#endif

#ifndef CHAR_MIN
#define CHAR_MIN  (-0x80)
#endif

#ifndef CHAR_MAX
#define CHAR_MAX  0x7F
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


extern uint32 util_rand(uint32 seed);
uint32 rand_max(uint32 seed, uint32 max);

#ifdef CUSTOM_RAND
#define rand(s) util_rand(s)
#endif

void bubble_sort(int, int []);

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
void free_dmatrix(real64** a, long nrl, long nrh, long ncl, long nch);
int** imatrix(long nrl, long nrh, long ncl, long nch);
void free_imatrix(int** a, long nrl, long nrh, long ncl, long nch);
real32** sub_matrix(real32** a, long oldnrl, long oldnrh, long oldncl,
  long oldnch, long newnrl, long newnrh, long newncl, long newnch);
real32** convert_matrix(real32* a, long nrl, long nrh, long ncl, long nch);

// tensor
// d depth ?
real32*** f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_f3tensor(real32*** a, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);

#endif
