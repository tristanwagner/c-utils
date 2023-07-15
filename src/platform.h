#if defined(__APPLE__) || defined(__MACH__)
#define PLATFORM "osx"
#elif defined(unix)
#define PLATFORM "unix"
#elif defined(_WIN64) || defined(_WIN32)
#define PLATFORM "win"
#endif
