#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "mem.h"

typedef struct CQueue
{
    struct CQueue *next;
    struct CQueue *last;
} CQueue;

typedef void (*QCallback)(void *);

void QInit(void *head);
void QInsert(void *entry, void *pred);
void QPush(void *entry, void *q);
void QUnshift(void *entry, void *q);
void QRemove(void *entry);
void QWipe(void *head);
int QCount(void *head);
void QForEach(void *head, QCallback cb);

#endif
