#if (defined __ANDROID__)
#define PLATFORM_ANDROID
#elif defined(__APPLE__) || defined(__MACH__)
#define PLATFORM_OSX
#elif (defined linux || defined _linux || defined __linux__)
#define PLATFORM_UNIX
#elif defined(_WIN64) || defined(_WIN32)
#define __USE_MINGW_ANSI_STDIO  1
// Necessary windows defines before including windows.h, because it's retarded.
#define OEMRESOURCE
#include <windows.h>
#define PLATFORM_WIN
#elif (defined __EMSCRIPTEN__)
#define PLATFORM_WEB
#endif
