typedef struct { void *head; void *tail; } OSThreadQueue;
typedef struct {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    void **msgArray;
    int msgCount;
    int firstIndex;
    int usedCount;
} OSMessageQueue;

static inline void OS_InitThreadQueue(OSThreadQueue *q) {
    q->tail = 0;
    q->head = 0;
}

void OS_InitMessageQueue(OSMessageQueue *mq, void **msgArray, int msgCount) {
    OS_InitThreadQueue(&mq->queueSend);
    OS_InitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}
