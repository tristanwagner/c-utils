#ifndef __COMPLEX_H__
#define __COMPLEX_H__
#include "math.h"

typedef struct FCOMPLEX {float r,i;} fcomplex;

fcomplex Cadd(fcomplex a, fcomplex b);
fcomplex Csub(fcomplex a, fcomplex b);
fcomplex Cmul(fcomplex a, fcomplex b);
fcomplex Complex(float re, float im);
fcomplex Conjg(fcomplex z);
fcomplex Cdiv(fcomplex a, fcomplex b);
fcomplex Csqrt(fcomplex z);
fcomplex RCmul(float x, fcomplex a);

#endif
