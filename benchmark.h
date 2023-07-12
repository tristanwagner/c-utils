// will only work for mac m1+
// TODO: support linux/win
#include <mach/mach_time.h>

typedef void (*function_ptr)();

typedef struct {
  char* name;
  function_ptr ptr;
} function_entry;

extern uint64_t getCurrentTime() {
  return mach_absolute_time();
}

extern double convertToNanoseconds(uint64_t t) {
  static mach_timebase_info_data_t timebase;
  if (timebase.denom == 0) {
    mach_timebase_info(&timebase);
  }
  return (double)t * (double)timebase.numer / (double)timebase.denom;
}
extern void benchmark(function_entry f) {
  uint64_t start, end;
  double elapsed;
  start = getCurrentTime();
  f.ptr();
  end = getCurrentTime();
  elapsed = convertToNanoseconds(end - start);
  printf("Elapsed time calling function \"%s\": %.2f ns", f.name, elapsed);
}
