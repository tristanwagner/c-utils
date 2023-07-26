#include "clipboard.h"

#if defined(PLATFORM_WIN) || defined(PLATFORM_UNIX)
// TODO: support windows & linux
char *clipboard_read() { return NULL; }
void clipboard_write(const char *text) {}
#elif defined(PLATFORM_OSX)
// objective c bridging
#else
#error                                                                         \
    "Unsupported platform: This clipboard implementation supports Windows, macOS, and Linux only."
#endif
