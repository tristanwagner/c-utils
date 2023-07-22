#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdlib.h>

#define ZeroStruct(a) memset(&(a), 0, sizeof(a))
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

#include "uerror.h"
#include "debug.h"
#include "dbg_mem.h"
#include "types.h"
#include "buffer.h"
#include "term.h"
#include "queue.h"
#include "task.h"
#include "bitwise.h"
#include "math.h"
#include "complex.h"
#include "ustring.h"
#include "benchmark.h"

int f_size(FILE* f);

#endif
