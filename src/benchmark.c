#include "benchmark.h"
#include "debug.h"

// TODO: test unix & windows
#if defined(__MACH__)
// will only work for macOS 10.0+
// TODO:  what about older macs
// apple deprecate stuff rly quick anyway
uint64_t getCurrentTime() { return mach_absolute_time(); }

double convertToNanoseconds(uint64_t t) {
  static mach_timebase_info_data_t timebase;
  if (timebase.denom == 0) {
    mach_timebase_info(&timebase);
  }
  return (double)t * (double)timebase.numer / (double)timebase.denom;
}
#endif

#if defined(_WIN32)
static LARGE_INTEGER frequency, start, end;
#else
static uint64_t start, end;
#endif

static double elapsed;

void benchmark(function_entry f) {
#if defined(__MACH__)
  start = getCurrentTime();
#elif defined(unix)
  start = clock();
#elif defined(__WIN32)
  LARGE_INTEGER frequency, start, end;
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);
#endif
  f.ptr();
#if defined(__MACH__)
  end = getCurrentTime();
  elapsed = convertToNanoseconds(end - start);
  DEBUG_PRINT("Elapsed time calling function \"%s\": %.2f ns\n", f.name,
              elapsed);
#elif defined(unix)
  end = clock();
  elapsed = (double)(end - start);
  DEBUG_PRINT("Elapsed time calling function \"%s\": %.2f ms\n", f.name,
              elapsed);
#elif defined(__WIN32)
  QueryPerformanceCounter(&end);
  elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  DEBUG_PRINT("Elapsed time calling function \"%s\": %.2f s\n", f.name,
              elapsed);
#endif
}
