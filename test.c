#define DEBUG_MEMORY
#include "utils.h"
#include "benchmark.h"

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

int main(){
    BYTE s[50];
    snprintf(s, sizeof s, "LHELLLLLLLLLLLO");
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", strChOc(s, 'L'));
    DEBUG_PRINT("%d\n", bit(80, s));
    bitSet(80, &s);
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", bit(80, s));
    bitClear(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    bitToggle(80, &s);
    DEBUG_PRINT("%d\n", bit(80, s));
    DEBUG_PRINT("%s\n", s);
    DEBUG_PRINT("%d\n", extractBitsFromBytes("AAA", 4, 4));
    DEBUG_PRINT("strlen %s: %d\n", s, strLen(s));
    DEBUG_PRINT("strlen %s: %d\n", "hello", strLen("hello"));
    int a = 3499995;
    char* t = itoa(a);
    DEBUG_PRINT("strlen %s: %d\n", t, strLen(t));

    int b = -3499995;
    char* tt = itoa(b);
    DEBUG_PRINT("strlen %s: %d\n", tt, strLen(tt));
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

    benchmark((function_entry){ .name="testBenchmark", .ptr=&testBenchmark});
    free(add);
    return 0;
}

