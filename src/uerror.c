#include "uerror.h"

void die(const char *s) {
  perror(s);
  exit(1);
}
