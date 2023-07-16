#include "math.h"

// produces a random number between 0 and 32767
uint32 util_rand(uint32 seed) {
  seed = seed * 1103515245 + 1337;
  return (uint32)(seed / 65536) % 32768;
}

uint32 rand_max(uint32 seed, uint32 max) { return util_rand(seed) % (max + 1); }

void bubble_sort(int s, int *a) {
  int x, y, t;
  for (x = 0; x < s - 1; x++) {
    for (y = 0; y < s - x - 1; y++) {
      if (a[y] > a[y + 1]) {
        t = a[y];
        a[y] = a[y + 1];
        a[y + 1] = t;
      }
    }
  }
}

// vectors
#define V_END 1
#define FREE_ARG char *

uint8 *cvector(long nl, long nh) {
  uint8 *v;
  v = (uint8 *)malloc((size_t)((nh - nl + 1 + V_END) * sizeof(uint8)));
  if (!v)
    DEBUG_PRINT("failed allocation using cvector(%ld, %ld)\n", nl, nh);
  return v;
};

void free_cvector(uint8 *a, long nl) { free((FREE_ARG)a + nl - V_END); };

int *ivector(long nl, long nh) {
  int *v;
  v = (int *)malloc((size_t)((nh - nl + 1 + V_END) * sizeof(int)));
  if (!v)
    DEBUG_PRINT("failed allocation using ivector(%ld, %ld)\n", nl, nh);
  return v;
};

void free_ivector(int *a, long nl) { free((FREE_ARG)a + nl - V_END); };

long *lvector(long nl, long nh) {
  long *v;
  v = (long *)malloc((size_t)((nh - nl + 1 + V_END) * sizeof(long)));
  if (!v)
    DEBUG_PRINT("failed allocation using lvector(%ld, %ld)\n", nl, nh);
  return v;
};

void free_lvector(long *a, long nl) { free((FREE_ARG)a + nl - V_END); };

real32 *vector(long nl, long nh) {
  real32 *v;
  v = (real32 *)malloc((size_t)((nh - nl + 1 + V_END) * sizeof(real32)));
  if (!v)
    DEBUG_PRINT("failed allocation using vector(%ld, %ld)\n", nl, nh);
  return v;
};

void free_vector(real32 *a, long nl) { free((FREE_ARG)a + nl - V_END); };

real64 *dvector(long nl, long nh) {
  real64 *v;
  v = (real64 *)malloc((size_t)((nh - nl + 1 + V_END) * sizeof(real64)));
  if (!v)
    DEBUG_PRINT("failed allocation using dvector(%ld, %ld)\n", nl, nh);
  return v;
};

void free_dvector(real64 *a, long nl) { free((FREE_ARG)a + nl - V_END); };

// matrix

real32 **matrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  real32 **m;

  m = (real32 **)malloc((size_t)((nrow + V_END) * sizeof(real32 *)));
  if (!m)
    DEBUG_PRINT(
        "failed allocation using matrix(%ld, %ld, %ld, %ld) on row level\n",
        nrl, nrh, ncl, nch);
  m += V_END;
  m -= nrl;

  m[nrl] = (real32 *)malloc((size_t)((nrow * ncol + V_END) * sizeof(real32)));
  if (!m[nrl])
    DEBUG_PRINT(
        "failed allocation using matrix(%ld, %ld, %ld, %ld) on col level\n",
        nrl, nrh, ncl, nch);
  m[nrl] += V_END;
  m[nrl] -= ncl;

  for (i = nrl + 1; i <= nrh; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}

void free_matrix(real32 **a, long nrl, long ncl) {
  free((FREE_ARG)(a[nrl] + ncl - V_END));
  free((FREE_ARG)(a + nrl - V_END));
};