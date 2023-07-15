#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct CQueue CQueue;
typedef struct CQueue
{
    CQueue *next;
    CQueue *last;
} CQueue;
typedef void (*QCallback)(void *);

extern void QInit(void *head);
extern void QInsert(void *entry, void *pred);
extern void QPush(void *entry, void *q);
extern void QUnshift(void *entry, void *q);
extern void QRemove(void *entry);
extern void QWipe(void *head);
extern int QCount(void *head);
extern void QForEach(void *head, QCallback cb);

#endif
