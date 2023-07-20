#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdlib.h>

#define ZeroStruct(a) memset(&(a), 0, sizeof(a))

#include "uerror.h"
#include "debug.h"
#include "dbg_mem.h"
#include "types.h"
#include "buffer.h"
#include "term.h"
#include "benchmark.h"
#include "queue.h"
#include "task.h"
#include "bitwise.h"
#include "math.h"
#include "complex.h"
#include "ustring.h"

int f_size(FILE* f);

#endif
