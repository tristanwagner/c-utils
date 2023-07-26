#ifndef _CLIPBOARD_H_
#define _CLIPBOARD_H_
#include "platform.h"

#if defined(PLATFORM_WIN)
#include <windows.h>
#elif defined(PLATFORM_UNIX)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#elif defined(PLATFORM_OSX)
// objective c bridging
#else
#error "Unsupported platform: This clipboard implementation supports Windows, macOS, and Linux only."
#endif

void clipboard_write(const char *text);
char *clipboard_read();
#endif
