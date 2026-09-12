extern int data_0204c234;

typedef struct {
    unsigned char pad0[3];
    unsigned char stamp;
} RingSlot;

typedef struct {
    RingSlot slots[32];
    unsigned short from;
    unsigned short count;
    unsigned char tick;
} RingQueue;

void func_02032870(void) {
    RingQueue *q = (RingQueue *)(*(int *)&data_0204c234 + 0xb4718);
    unsigned short i = 0;
    unsigned char tick;
    unsigned short count;
    unsigned short remaining;

    q->tick = q->tick + 1;
    tick = q->tick;
    count = q->count;
    remaining = count;

    for (; i < count; i++) {
        unsigned short idx = (q->from + i) & 0x1f;
        unsigned char stamp = q->slots[idx].stamp;
        unsigned char diff = (stamp > tick) ? (unsigned char)(tick + 0x100 - stamp) : (unsigned char)(tick - stamp);
        if (diff < 8) break;
        remaining--;
    }

    if (count != remaining) {
        q->from = (q->from + count - remaining) & 0x1f;
        q->count = remaining;
    }
}
