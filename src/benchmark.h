#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

typedef void (*function_ptr)();
typedef struct {
  char* name;
  function_ptr ptr;
} function_entry;

#if defined(__MACH__)
#include <mach/mach_time.h>

uint64_t getCurrentTime();
double convertToNanoseconds(uint64_t t);
#elif defined(unix)
#include <time.h>
#elif defined(_WIN32)
#include <windows.h>
#else
  #error "Unknow os"
#endif

void benchmark(function_entry f);
#endif
