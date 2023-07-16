#include "math.h"
#include "types.h"

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

// magic
real32 SQRTF(real32 number) {
  int i;
  real32 x, y;
  x = number * 0.5;
  y = number;
  i = *(int *)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *)&i;
  y = y * (1.5 - (x * y * y));
  y = y * (1.5 - (x * y * y));
  return number * y;
}

real32 FABS(real32 number) {
  if (number < 0) {
    return -number;
  }
  return number;
}

// vectors
#define V_END 1
#define FREE_ARG char *

/* allocate a char vector with subscript range v[nl..nh] */
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

/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
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

real64 **dmatrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  real64 **m;

  m = (real64 **)malloc((size_t)((nrow + V_END) * sizeof(real64 *)));
  if (!m)
    DEBUG_PRINT(
        "failed allocation using dmatrix(%ld, %ld, %ld, %ld) on row level\n",
        nrl, nrh, ncl, nch);
  m += V_END;
  m -= nrl;

  m[nrl] = (real64 *)malloc((size_t)((nrow * ncol + V_END) * sizeof(real64)));
  if (!m[nrl])
    DEBUG_PRINT(
        "failed allocation using dmatrix(%ld, %ld, %ld, %ld) on col level\n",
        nrl, nrh, ncl, nch);
  m[nrl] += V_END;
  m[nrl] -= ncl;

  for (i = nrl + 1; i <= nrh; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}

void free_dmatrix(real64 **a, long nrl, long ncl) {
  free((FREE_ARG)(a[nrl] + ncl - V_END));
  free((FREE_ARG)(a + nrl - V_END));
}

int **imatrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  int **m;

  m = (int **)malloc((size_t)((nrow + V_END) * sizeof(int *)));
  if (!m)
    DEBUG_PRINT(
        "failed allocation using imatrix(%ld, %ld, %ld, %ld) on row level\n",
        nrl, nrh, ncl, nch);
  m += V_END;
  m -= nrl;

  m[nrl] = (int *)malloc((size_t)((nrow * ncol + V_END) * sizeof(int)));
  if (!m[nrl])
    DEBUG_PRINT(
        "failed allocation using imatrix(%ld, %ld, %ld, %ld) on col level\n",
        nrl, nrh, ncl, nch);
  m[nrl] += V_END;
  m[nrl] -= ncl;

  for (i = nrl + 1; i <= nrh; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}

void free_imatrix(int **a, long nrl, long ncl) {
  free((FREE_ARG)(a[nrl] + ncl - V_END));
  free((FREE_ARG)(a + nrl - V_END));
}

real32 **sub_matrix(real32 **a, long oldrl, long oldrh, long oldcl, long oldch,
                    long newrl, long newrh, long newcl, long newch) {
  /* point a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
  long i, j, nrow = oldrh - oldrl + 1, ncol = oldcl - newcl;
  real32 **m;

  m = (real32 **)malloc((size_t)((nrow + V_END) * sizeof(real32 *)));
  if (!m)
    DEBUG_PRINT("failed allocation using sub_matrix()\n");
  m += V_END;
  m -= newrl;

  for (i = oldrl, j = newrl; i <= oldrh; i++, j++)
    m[j] = a[i] + ncol;

  return m;
}

real32 **convert_matrix(real32 *a, long nrl, long nrh, long ncl, long nch) {
  /* allocate a float matrix m[nrl..nrh][ncl..nch] that points to the matrix
  declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1 and
  ncol=nch-ncl+1. The routine should be called with the address
  &a[0][0] as the first argument. */
  long i, j, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  real32 **m;

  m = (real32 **)malloc((size_t)((nrow + V_END) * sizeof(real32 *)));
  if (!m)
    DEBUG_PRINT("failed allocation using convert_matrix(%ld, %ld, %ld, %ld) on "
                "row level\n",
                nrl, nrh, ncl, nch);
  m += V_END;
  m -= nrl;

  m[nrl] = a - ncl;
  for (i = 1, j = nrl + 1; i < nrow; i++, j++)
    m[j] = m[j - 1] + ncol;

  return m;
}

real32 ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh) {
  long i, j, nrow = nrh - nrl + 1, ncol = nch - ncl + 1, ndep = ndh - ndl + 1;
  real32 ***t;

  t = (real32 ***)malloc((size_t)((nrow + V_END) * sizeof(real32 **)));
  if (!t)
    DEBUG_PRINT("failed allocation using f3tensor(%ld, %ld, %ld, %ld, %ld, "
                "%ld) on row level\n",
                nrl, nrh, ncl, nch, ndl, ndh);
  t += V_END;
  t -= nrl;

  t[nrl] =
      (real32 **)malloc((size_t)((nrow * ncol + V_END) * sizeof(real32 *)));
  if (!t[nrl])
    DEBUG_PRINT("failed allocation using f3tensor(%ld, %ld, %ld, %ld, %ld, "
                "%ld) on col level\n",
                nrl, nrh, ncl, nch, ndl, ndh);
  t[nrl] += V_END;
  t[nrl] -= ncl;

  t[nrl][ncl] =
      (real32 *)malloc((size_t)((nrow * ncol * ndep + V_END) * sizeof(real32)));
  if (!t[nrl])
    DEBUG_PRINT("failed allocation using f3tensor(%ld, %ld, %ld, %ld, %ld, "
                "%ld) on depth level\n",
                nrl, nrh, ncl, nch, ndl, ndh);
  t[nrl][ncl] += V_END;
  t[nrl][ncl] -= ndl;

  for (j = ncl + 1; j <= nch; j++)
    t[nrl][j] = t[nrl][j - 1] + ndep;

  for (i = nrl + 1; i <= nrh; i++) {
    t[i] = t[i - 1] + ncol;
    t[i][ncl] = t[i - 1][ncl] + ncol * ndep;
    for (j = ncl + 1; j <= nch; j++)
      t[i][j] = t[i][j - 1] + ndep;
  }

  return t;
}

void free_f3tensor(real32 ***a, long nrl, long ncl, long ndl) {
  free((FREE_ARG)(a[nrl][ncl] + ndl - V_END));
  free((FREE_ARG)(a[nrl] + ncl - V_END));
  free((FREE_ARG)(a + nrl - V_END));
}
