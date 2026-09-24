/* Records (id, kind) in the 32-slot recent-events ring at base+0xb4718, stamped with the current
 * tick: returns 0 when the pair is already queued; a full ring overwrites its oldest slot,
 * otherwise the record is appended. Returns 1 when recorded. */
extern int data_0204c234;

typedef struct {
    unsigned short id;
    unsigned char kind;
    unsigned char stamp;
} RingSlot;

typedef struct {
    RingSlot slots[32];
    unsigned short from;
    unsigned short count;
    unsigned char tick;
} RingQueue;

int func_02032928(unsigned short id, unsigned char kind)
{
    RingQueue *q = (RingQueue *)(*(int *)&data_0204c234 + 0xb4718);
    unsigned short i = 0;
    unsigned short count = q->count;
    RingSlot *slot;

    for (; i < count; i++) {
        slot = &q->slots[(q->from + i) & 0x1f];
        if (slot->id == id && slot->kind == kind) {
            return 0;
        }
    }
    if (count == 32) {
        unsigned short from = q->from;

        q->from = (from + 1) & 0x1f;
        slot = &q->slots[from];
    } else {
        slot = &q->slots[(q->from + count) & 0x1f];
        q->count++;
    }
    slot->id = id;
    slot->kind = kind;
    slot->stamp = q->tick;
    return 1;
}
