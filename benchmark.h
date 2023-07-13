#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

typedef void (*function_ptr)();
typedef struct {
  char* name;
  function_ptr ptr;
} function_entry;

#if defined(__MACH__)
extern uint64_t getCurrentTime();
extern double convertToNanoseconds(uint64_t t);
#endif

extern void benchmark(function_entry f);
#endif
