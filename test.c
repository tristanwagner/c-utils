#include "src/libutils.h"

// TODO: introduce unit tests instead of this mess

typedef struct Test {
  struct Test *next, *last;
  int value;
} Test;

void print(void *ptr) {
  Test *item = (Test *)ptr;
  DEBUG_PRINT("value: %d | next: %d | last: %d\n", item->value,
              item->next->value, item->last->value);
}

void add(void *ptr) {
  Test *item = (Test *)ptr;
  item->value += 1;
}

void testBenchmark() {
  Test list;
  QInit(&list);
  QForEach(&list, add);
}

void testingSub1() {
  TASK_INIT();
  printf("A");
  TASK_YIELD();
  printf("B");
  TASK_YIELD();
  printf("C");
  TASK_END();
}
void testingSub2() {
  TASK_INIT();
  printf("1");
  TASK_YIELD();
  printf("2");
  TASK_YIELD();
  printf("3");
  TASK_YIELD();
  printf("4");
  TASK_END();
}

void benchssplit() {
  int x;
  str_split_result sresult = {0};
  str_split(&sresult, "TEST\nTEST\n", '\n');
  for (x = 0; x < sresult.size; x++) {
    DEBUG_PRINT("splitest result[%d] = %s\n", x, sresult.substrings[x]);
  }
}

void testingSub3() {
  TASK_INIT();
  while (1) {
    printf("*");
    TASK_YIELD();
  }
  TASK_END();
}

void testingTasks() {
  testingSub1();
  testingSub2();
  testingSub3();
  printf("\n");
}

static char *tstr = "abcdefghijklmnopqrstuvwxyz ./,;";

void testStrToHex() {
  DEBUG_PRINT("str_to_hex %s => \n%s\n", tstr, str_to_hex(tstr, str_len(tstr)));
}
void testBinToHex() {
  DEBUG_PRINT("bin_to_hex %s => \n%s\n", tstr, bin_to_hex(tstr, str_len(tstr)));
}

int run() {
  int x;
  size_t i;
  char s[] = "LHELLLLLLLLLLLO";
  DEBUG_PRINT("%s\n", s);
  DEBUG_PRINT("%zu\n", str_ch_oc(s, 'L'));
  DEBUG_PRINT("%d\n", bit(80, s));
  bit_set(80, s);
  DEBUG_PRINT("%s\n", s);
  DEBUG_PRINT("%d\n", bit(80, s));
  bit_clear(80, s);
  DEBUG_PRINT("%d\n", bit(80, s));
  DEBUG_PRINT("%s\n", s);
  bit_toggle(80, s);
  DEBUG_PRINT("%d\n", bit(80, s));
  DEBUG_PRINT("%s\n", s);
  bit_toggle(80, s);
  DEBUG_PRINT("%d\n", bit(80, s));
  DEBUG_PRINT("%s\n", s);
  DEBUG_PRINT("%zu\n", extract_bits_from_bytes("AAA", 0, 8));
  DEBUG_PRINT("strlen %s: %zu\n", s, str_len(s));
  DEBUG_PRINT("strlen %s: %zu\n", "hello", str_len("hello"));
  int a = 3499995;
  char *t = itoa(a);
  DEBUG_PRINT("strlen %s: %zu\n", t, str_len(t));

  char sa[] = "3499995";
  int st = atoi(sa);
  DEBUG_PRINT("atoi: %d\n", st);

  int b = -3499995;
  char *tt = itoa(b);
  DEBUG_PRINT("strlen %s: %zu\n", tt, str_len(tt));

  str_split_result sresult = {0};
  str_split(&sresult, "TEST\nTEST\n", '\n');
  for (x = 0; x < sresult.size; x++) {
    DEBUG_PRINT("splitest result[%d] = %s\n", x, sresult.substrings[x]);
  }

  str_split(&sresult, "", '\n');
  if (sresult.size == 0) {
    DEBUG_PRINT("ok\n");
  }

  // TODO: benchmark over a huge buffer
  benchmark((function_entry){.name = "benchssplit", .ptr = &benchssplit});

  free_str_split_result(&sresult);

  DEBUG_PRINT("str_to_hex %s => \n%s\n", tstr, str_to_hex(tstr, str_len(tstr)));
  DEBUG_PRINT("bin_to_hex %s => \n%s\n", tstr, bin_to_hex(tstr, str_len(tstr)));

  benchmark((function_entry){.name = "testBinToHex", .ptr = &testBinToHex});
  benchmark((function_entry){.name = "testStrToHex", .ptr = &testStrToHex});

  char *tstr2 = "\xFF\xFF\xFF\x00";
  DEBUG_PRINT("str_to_hex %s => \n%s\n", tstr2, str_to_hex(tstr2, 4));

  // Queue
  Test list;
  QInit(&list);

  DEBUG_PRINT("%d\n", list.value);

  for (i = 0; i < 10; i++) {
    Test *tmp = (Test *)malloc(sizeof(Test));
    tmp->value = i;
    QPush(tmp, &list);
  }

  Test *addHead = (Test *)malloc(sizeof(Test));
  addHead->value = 10;
  QUnshift(addHead, &list);

  Test *ptr;
  ptr = list.next;

  QForEach(&list, print);

  QForEach(&list, add);

  QForEach(&list, print);

  DEBUG_PRINT("List item count: %d\n", QCount(&list));

  QWipe(&list);

  DEBUG_PRINT("List item count: %d\n", QCount(&list));

  Test *add = (Test *)malloc(sizeof(Test));
  add->value = 1;

  QInsert(add, list.last);

  DEBUG_PRINT("List item count: %d\n", QCount(&list));

  QForEach(&list, print);

  free(add);

  // Benchmark
  benchmark((function_entry){.name = "testBenchmark", .ptr = &testBenchmark});

  // Maths
  DEBUG_PRINT("DEG2RAD: %.5f\n", DEG2RAD(90.0));

  DEBUG_PRINT("RAD2DEG: %.2f\n", RAD2DEG(1.57080));

  DEBUG_PRINT("SQR: %.2f\n", SQR(5.0));

  DEBUG_PRINT("SQRTF: %.2f\n", SQRTF(25.0));

  DEBUG_PRINT("FABS: %.2f\n", FABS(-25.0));

  DEBUG_PRINT("FMAX: %.2f\n", FMAX(5.0, 15.0));

  DEBUG_PRINT("FMIN: %.2f\n", FMIN(5.0, 15.0));

  DEBUG_PRINT("DSQR: %.2f\n", DSQR(5.0));

  DEBUG_PRINT("DMAX: %.2f\n", DMAX(5.0, 15.0));

  DEBUG_PRINT("DMIN: %.2f\n", DMIN(5.0, 15.0));

  DEBUG_PRINT("LMAX: %ld\n", LMAX(5, 15));

  DEBUG_PRINT("LMIN: %ld\n", LMIN(5, 15));

  DEBUG_PRINT("IMAX: %d\n", IMAX(-5, -15));

  DEBUG_PRINT("IMIN: %d\n", IMIN(-5, -15));

  uint8 *v1 = cvector(1, 10);
  free_cvector(v1, 1);

  int *v2 = ivector(1, 10);
  free_ivector(v2, 1);

  real32 *v3 = vector(1, 20);
  free_vector(v3, 1);

  real64 *v4 = dvector(1, 20);
  free_dvector(v4, 1);

  real32 **m = matrix(0, 20, 0, 20);
  m[0][0] = 420.69;
  DEBUG_PRINT("TEST matrix: %.2f\n", m[0][0]);
  free_matrix(m, 0, 0);

  real64 **m2 = dmatrix(0, 20, 0, 20);
  m2[0][0] = 420.69;
  DEBUG_PRINT("TEST dmatrix: %.2f\n", m2[0][0]);
  free_dmatrix(m2, 0, 0);

  int **m3 = imatrix(0, 20, 0, 20);
  m3[0][0] = 420;
  DEBUG_PRINT("TEST imatrix: %d\n", m3[0][0]);
  free_imatrix(m3, 0, 0);

  real32 ***tensor = f3tensor(0, 20, 0, 20, 0, 20);
  tensor[0][0][0] = 420.69;
  DEBUG_PRINT("TEST tensor: %.2f\n", tensor[0][0][0]);
  free_f3tensor(tensor, 0, 0, 0);

  // Tasks
  int itask = 10;

  DEBUG_PRINT("TASKS:\n");
  while (itask > 0) {
    testingTasks();
    itask--;
  }

  // Clipboard
  clipboard_write("TEST Clipboard");
  DEBUG_PRINT("%s\n", clipboard_read());

  // Hashtable
  ht *tbl = ht_new();
  ht_insert(tbl, "test", "value");
  DEBUG_PRINT("hashtable search key test %s\n", ht_get(tbl, "test"));

  ht_insert(tbl, "test", "value2");
  DEBUG_PRINT("hashtable search key test %s\n", ht_get(tbl, "test"));

  // Dynamic array
  int *arr_test = array(int);
  DEBUG_PRINT("test\n");
  DEBUG_PRINT("array_test capacity %zu\n", array_capacity(arr_test));
  array_push(arr_test, 3);

  DEBUG_PRINT("array_test length %zu\n", array_length(arr_test));
  DEBUG_PRINT("array_test[0] %d\n", arr_test[0]);
  DEBUG_PRINT("array_test capacity %zu\n", array_capacity(arr_test));

  array_push(arr_test, 4);
  array_push(arr_test, 5);
  array_push(arr_test, 6);
  array_push(arr_test, 7);

  DEBUG_PRINT("array_test length %zu\n", array_length(arr_test));
  DEBUG_PRINT("array_test[0] %d\n", arr_test[0]);
  DEBUG_PRINT("array_test[1] %d\n", arr_test[1]);
  DEBUG_PRINT("array_test[2] %d\n", arr_test[2]);
  DEBUG_PRINT("array_test[3] %d\n", arr_test[3]);
  DEBUG_PRINT("array_test[4] %d\n", arr_test[4]);

  array_remove(arr_test, 0);
  DEBUG_PRINT("array_test length %zu\n", array_length(arr_test));
  DEBUG_PRINT("array_test[0] %d\n", arr_test[0]);
  DEBUG_PRINT("array_test[1] %d\n", arr_test[1]);
  DEBUG_PRINT("array_test[2] %d\n", arr_test[2]);
  DEBUG_PRINT("array_test[3] %d\n", arr_test[3]);

  array_remove(arr_test, 1);
  DEBUG_PRINT("array_test length %zu\n", array_length(arr_test));
  DEBUG_PRINT("array_test[0] %d\n", arr_test[0]);
  DEBUG_PRINT("array_test[1] %d\n", arr_test[1]);
  DEBUG_PRINT("array_test[2] %d\n", arr_test[2]);

  array_pop(arr_test);
  DEBUG_PRINT("array_test length %zu\n", array_length(arr_test));
  DEBUG_PRINT("array_test last %d\n", arr_test[array_length(arr_test) - 1]);

  return 0;
}

int main() { run(); }
