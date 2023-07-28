#include "ustring.h"

// count character occurences in string
size_t str_ch_oc(const char *str, char ch) {
  if (!str)
    return 0;
  size_t c = 0;
  while (*str)
    if (*str++ == ch)
      c++;
  return c;
}

size_t str_len(const char *str) {
  if (!str)
    return 0;
  size_t c = 0;
  while (*str++)
    c++;
  return c;
}

void str_split(str_split_result *result, char *src, char token) {
  result->size = 0;

  if (!src) {
    return;
  }

  // TODO: support more than 256 matches ?
  int matches[256];
  int i = 0;
  char *srcpy = src;

  while (*src) {
    if (*src == token) {
      matches[result->size] = i;
      result->size++;
    }
    i++;
    src++;
  }

  if (result->size == 0) {
    return;
  }

  char **ptr =
      (char **)realloc(result->substrings, (result->size + 1) * sizeof(char *));
  if (ptr != NULL) {
    result->substrings = ptr;

    for (int x = 0; x < result->size; x++) {
      int previous = x <= 0 ? 0 : matches[x - 1];
      int size = matches[x] - previous;
      int offset = previous == 0 ? previous : previous + 1;
      result->substrings[x] =
          realloc(result->substrings[x], (size) * sizeof(char));
      memcpy(result->substrings[x], &srcpy[offset], size);
      result->substrings[x][size - (previous == 0 ? 0 : 1)] = '\0';
    }

    // close
    result->substrings[result->size] = NULL;
  } else {
    die("Failed to allocate memory in str_split()");
  }

  return;
}

void free_str_split_result(str_split_result *result) {
  if (result->substrings != NULL) {
    free(result->substrings);
  }
}

char *itoa(int value) {
  static char buffer[256];
  int i = 0;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return buffer;
  }

  if (value < 0) {
    buffer[i++] = '-';
    value = -value;
  }

  while (value != 0) {
    int digit = value % 10;
    buffer[i++] = '0' + digit;
    value /= 10;
  }

  buffer[i] = '\0';

  int start = buffer[0] == '-' ? 1 : 0;
  int end = i - 1;

  while (start < end) {
    char tmp = buffer[start];
    buffer[start] = buffer[end];
    buffer[end] = tmp;
    start++;
    end--;
  }

  return buffer;
}

// TODO: support negative numbers
int atoi(const char *s) {
  int n = 0;
  while (1) {
    char c = *s++;
    if (!c)
      break;
    n = 10 * n + (c - '0');
  }
  return n;
}

int c_is_separator(int c) {
  return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != NULL;
}

char *str_to_hex(const char *src, size_t len) {
  if (len == 0 || src == NULL) {
    return NULL;
  }

  int out_len = len * 5;

  char *buffer = malloc(out_len + 1);
  if (buffer == NULL) {
    return NULL;
  }

  int i, c = 0;
  for (i = 0; i < len; i++) {
    c += snprintf(&buffer[c], 6, "0x%02X ", (unsigned char)src[i]);
  }
  // terminate string and strip last space
  buffer[c - 1] = '\0';
  return buffer;
}
