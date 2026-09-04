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

/* Unlink a specific thread from a queue. Returns the thread when it was found
   and removed, or NULL when it was not on this queue. */
OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *pCur;
    OSThread *pNext;
    OSThread *pPrev;

    for (pCur = queue->head; pCur != NULL; pCur = pNext) {
        pNext = pCur->next;
        if (pCur == thread) {
            pPrev = pCur->prev;
            if (queue->head == pCur) {
                queue->head = pNext;
            } else {
                pPrev->next = pNext;
            }
            if (queue->tail == pCur) {
                queue->tail = pPrev;
            } else {
                pNext->prev = pPrev;
            }
            break;
        }
    }

    return pCur;
}
