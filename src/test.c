#include "utils.h"

// TODO: introduce unit tests instead of this mess

typedef struct Test Test;

typedef struct Test {
    Test *next, *last;
    int value;
} Test;

void print(void *ptr){
    Test *item = (Test *) ptr;
    DEBUG_PRINT("value: %d | next: %d | last: %d\n", item->value, item->next->value, item->last->value);
}

void add(void *ptr){
    Test *item = (Test *) ptr;
    item->value += 1;
}

void testBenchmark() {
    Test list;
    QInit(&list);
    QForEach(&list, add);
}

void testingSub1(){
  TASK_INIT();
  printf("A");
  TASK_YIELD();
  printf("B");
  TASK_YIELD();
  printf("C");
  TASK_END();
}
void testingSub2(){
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

void testingSub3(){
  TASK_INIT();
  while(1){
    printf("*");
    TASK_YIELD();
  }
  TASK_END();
}

void testingTasks(){
  testingSub1();
  testingSub2();
  testingSub3();
  printf("\n");
}

int main(){
    BYTE s[50];
    snprintf(s, sizeof s, "LHELLLLLLLLLLLO");
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", str_ch_oc(s, 'L'));
    DEBUG_PRINT("%d\n", bit(80, s));
    bit_set(80, &s);
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", bit(80, s));
    bit_clear(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    bit_toggle(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    bit_toggle(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", extract_bits_from_bytes("AAA", 0, 8));
    DEBUG_PRINT("strlen %s: %d\n", s, str_len(s));
    DEBUG_PRINT("strlen %s: %d\n", "hello", str_len("hello"));
    int a = 3499995;
    char* t = itoa(a);
    DEBUG_PRINT("strlen %s: %d\n", t, str_len(t));

    char sa[] = "3499995";
    int st = atoi(sa);
    DEBUG_PRINT("atoi: %d\n", st);

    int b = -3499995;
    char* tt = itoa(b);
    DEBUG_PRINT("strlen %s: %d\n", tt, str_len(tt));
    Test list;
    QInit(&list);

    DEBUG_PRINT("%d\n", list.value);

    for (size_t i = 0; i < 10; i++)
    {
        Test *tmp = (Test *) malloc(sizeof(Test));
        tmp->value = i;
        QPush(tmp, &list);
    }

    Test *addHead = (Test *) malloc(sizeof(Test));
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

    Test *add = (Test *) malloc(sizeof(Test));
    add->value = 1;

    QInsert(add, list.last);

    DEBUG_PRINT("List item count: %d\n", QCount(&list));

    QForEach(&list, print);

    free(add);

    benchmark((function_entry) {
      .name="testBenchmark",
      .ptr=&testBenchmark
    });

    DEBUG_PRINT("SQR: %.2f\n", SQR(5.0));

    DEBUG_PRINT("FMAX: %.2f\n", FMAX(5.0, 15.0));

    DEBUG_PRINT("FMIN: %.2f\n", FMIN(5.0, 15.0));

    DEBUG_PRINT("DSQR: %.2f\n", DSQR(5.0));

    DEBUG_PRINT("DMAX: %.2f\n", DMAX(5.0, 15.0));

    DEBUG_PRINT("DMIN: %.2f\n", DMIN(5.0, 15.0));

    DEBUG_PRINT("LMAX: %d\n", LMAX(5, 15));

    DEBUG_PRINT("LMIN: %d\n", LMIN(5, 15));

    DEBUG_PRINT("IMAX: %d\n", IMAX(-5, -15));

    DEBUG_PRINT("IMIN: %d\n", IMIN(-5, -15));

    uint8* v1 = cvector(1, 10);
    free_cvector(v1, 1);

    int* v2 = ivector(1, 10);
    free_ivector(v2, 1);

    real32* v3 = vector(1, 20);
    free_vector(v3, 1);

    real64* v4 = dvector(1, 20);
    free_dvector(v4, 1);

    real32** m = matrix(0, 20, 0, 20);
    m[0][0] = 420.69;
    DEBUG_PRINT("TEST: %.2f\n", m[0][0]);
    free_matrix(m, 0, 0);

    int itask = 10;

    DEBUG_PRINT("TASKS:\n");
    while (itask > 0) {
      testingTasks();
      itask--;
    }

    return 0;
}

