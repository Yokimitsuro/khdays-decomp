#define NULL ((void *)0)

typedef unsigned char u8;
typedef unsigned int u32;

/* Threads carry their queue links inline: the scheduler never allocates nodes.
   Only the three fields this file touches are named; the rest of the thread
   record is not this function's business. */
typedef struct OSThread {
    u8 _reserved0[0x70];
    u32 priority;              /* 0x70, lower value means it runs sooner */
    u8 _reserved74[0x8];
    struct OSThread *prev;     /* 0x7c */
    struct OSThread *next;     /* 0x80 */
} OSThread;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

/* Insert a thread into a priority-ordered queue, keeping equal priorities in
   arrival order. A thread already on the queue is left where it is. */
void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *pAfter;
    OSThread *pBefore;

    for (pAfter = queue->head;
         pAfter != NULL && pAfter->priority <= thread->priority;
         pAfter = pAfter->next) {
        if (pAfter == thread) {
            return;
        }
    }

    if (pAfter == NULL) {
        pBefore = queue->tail;
        if (pBefore == NULL) {
            queue->head = thread;
        } else {
            pBefore->next = thread;
        }
        thread->prev = pBefore;
        thread->next = NULL;
        queue->tail = thread;
        return;
    }

    pBefore = pAfter->prev;
    if (pBefore == NULL) {
        queue->head = thread;
    } else {
        pBefore->next = thread;
    }
    thread->prev = pBefore;
    thread->next = pAfter;
    pAfter->prev = thread;
}
