/* func_020329e8 -- ScriptPool_AllocSlot: takes a script slot from the pool's free list
 * (+0xb46e4) and pushes it on the active list (+0xb46e8); the slot starts in state 5 when the
 * pool's +0xb47b4 resident flag is set (else 1) and gets the next 24-bit serial (data_020429e8).
 * Returns 0 when no slot is free. Counterpart of func_02032a7c (ScriptPool_FreeSlot). */
typedef struct ScriptSlot {
    struct ScriptSlot *next;
    struct ScriptSlot *prev;
    char pad08[0x14 - 0x8];
    unsigned short state;
    unsigned short pad16;
    unsigned int serial;
} ScriptSlot;

typedef struct ScriptPool {
    char pad0[0xb46e4];
    ScriptSlot *freeHead;
    ScriptSlot *activeHead;
    char pad[0xb47b4 - 0xb46ec];
    unsigned char resident;
} ScriptPool;

extern ScriptPool *data_0204c234;
extern unsigned int data_020429e8;

ScriptSlot *func_020329e8(void)
{
    ScriptPool *pool = data_0204c234;
    ScriptSlot *slot = pool->freeHead;

    if (slot == 0) {
        return 0;
    }
    pool->freeHead = slot->next;
    if (slot->next != 0) {
        slot->next->prev = 0;
    }
    slot->next = pool->activeHead;
    slot->prev = 0;
    if (pool->activeHead != 0) {
        pool->activeHead->prev = slot;
    }
    pool->activeHead = slot;
    slot->state = pool->resident != 0 ? 5 : 1;
    {
        /* the serial is stored twice (the first store is dead); with a single store the
         * increment and the mask are scheduled in the other order */
        unsigned long serial = slot->serial = data_020429e8++ & 0xffffff;
        slot->serial = serial;
    }
    return slot;
}
