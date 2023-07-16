#include "queue.h"

// Queue (linked list)
void QInit(void *head) {
  // Init the first element, head is only a placeholder that hold the queue,
  // to get the first element you will need to do head.next
  ((CQueue *)head)->next = (CQueue *)head;
  ((CQueue *)head)->last = (CQueue *)head;
}

void QInsert(void *entry, void *pred) {
  CQueue *succ;
  succ = ((CQueue *)pred)->next;
  ((CQueue *)entry)->last = (CQueue *)pred;
  ((CQueue *)entry)->next = succ;
  succ->last = (CQueue *)entry;
  ((CQueue *)pred)->next = (CQueue *)entry;
}

// insert at end
void QPush(void *entry, void *q) { QInsert(entry, ((CQueue *)q)->last); }

// insert at start
void QUnshift(void *entry, void *q) { QInsert(entry, q); }

// remove queue entry from queue
void QRemove(void *entry) {
  ((CQueue *)entry)->last->next = ((CQueue *)entry)->next;
  ((CQueue *)entry)->next->last = ((CQueue *)entry)->last;
}

// Free entries in queue, not head.
void QWipe(void *head) {
  CQueue *tmpq = ((CQueue *)head)->next, *tmpq1;
  while (tmpq != head) {
    tmpq1 = ((CQueue *)tmpq)->next;
    QRemove(tmpq);
    free(tmpq);
    tmpq = tmpq1;
  }
}

int QCount(void *head) {
  // Count of nodes in queue, not head.
  CQueue *tmpq = ((CQueue *)head)->next;
  int res = 0;
  while (tmpq != head) {
    res++;
    tmpq = ((CQueue *)tmpq)->next;
  }
  return res;
}

// for each element in queue, call callback function
// passing pointer of current element
void QForEach(void *head, QCallback cb) {
  CQueue *ptr = ((CQueue *)head)->next;
  while (ptr != head) {
    cb(ptr);
    ptr = ptr->next;
  }
}
