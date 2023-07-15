#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdlib.h>
#include <stdio.h>

#define DEBUG_PRINT(...) \
    do { \
        fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)
#endif
