#ifndef _TERM_H_
#define _TERM_H_

#define ESC '\x1b'
#define CSI '['

#include "uerror.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void term_reset_options();
void term_enable_raw_mode();
void term_init();
int term_get_window_size(int *rows, int *cols);
int term_get_cursor_position(int *rows, int *cols);
int term_enable_mouse_reporting();
int term_disable_mouse_reporting();
void term_clean();
#endif
