#pragma thumb on
/* func_02030e7c = MsgQueue_Init (THUMB). Sets up the message-queue context: it lives at the base of
 * the current root heap and is published in data_0204c230. The queue gets two entries (0x20 bytes
 * each, from the default heap); every entry owns two 0x1e0-byte buffers (32-byte aligned) and starts
 * with the first one active. Table6_ResetAll (func_020310e8) then clears the send state, and the two
 * transfer tasks are instantiated (InstantiateClass, func_02023930) from the descriptor template
 * data_02042110 with the class ids of data_02042108. Returns MsgQueue_GetHeap (func_02030fcc). */
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*GameClassFn)(void);

typedef struct MsgQueueBuf {
    int state;                          /* +0x0 */
    unsigned char *pBuffer;             /* +0x4 */
    u16 writeOffset;                    /* +0x8 */
    u16 pad;
} MsgQueueBuf;

typedef struct MsgQueueEntry {
    MsgQueueBuf slots[2];               /* +0x00 */
    MsgQueueBuf *pActive;               /* +0x18 */
    int field1c;                        /* +0x1c */
} MsgQueueEntry;

typedef struct MsgQueueCtx {
    int f0;                             /* +0x000 */
    MsgQueueEntry *entries;             /* +0x004 */
    int count;                          /* +0x008 */
    char pad00c[0x758 - 0xc];
    int classHandle[2];                 /* +0x758: the two transfer tasks */
} MsgQueueCtx;

typedef struct GameClassDescriptor {
    u16 nClassId;                       /* 0x00 */
    u16 nGroupId;                       /* 0x02 */
    GameClassFn pfnCtor;                /* 0x04 */
    GameClassFn pfnMethod;              /* 0x08 */
    int nAuxSize;                       /* 0x0c */
    int ***pArena;                      /* 0x10 */
} GameClassDescriptor;

typedef struct MsgQueueClassIds {
    int id[2];
} MsgQueueClassIds;

extern MsgQueueCtx *NNSi_FndGetCurrentRootHeap(void);
extern void *func_020236cc(u32 size, int **heap);               /* AllocFromExpHeapWrapper */
extern void *func_020236f8(u32 size, int align, int **heap);
extern void func_020310e8(void);                                /* Table6_ResetAll */
extern int func_02023930(const GameClassDescriptor *desc, int param);  /* InstantiateClass */
extern void func_02030fcc(void);                                /* MsgQueue_GetHeap */
extern MsgQueueCtx *data_0204c230;
extern int **data_0204c024;
extern const GameClassDescriptor data_02042110;
extern const MsgQueueClassIds data_02042108;

void *func_02030e7c(void)
{
    MsgQueueClassIds ids;
    GameClassDescriptor desc;
    int j;
    int i;
    /* The context pointer is kept in a one-element array read through an index that is always 0:
     * the element only becomes a register once the index is folded, which gives it the ROM's
     * register (r5 instead of r4). */
    MsgQueueCtx *ctx[1];
    int n = 0;

    ctx[n] = NNSi_FndGetCurrentRootHeap();
    data_0204c230 = ctx[n];
    ctx[n]->count = 2;
    ctx[n]->entries = func_020236cc(ctx[n]->count * sizeof(MsgQueueEntry), data_0204c024);
    for (i = 0; i < ctx[n]->count; i++) {
        for (j = 0; j < 2; j++) {
            ctx[n]->entries[i].slots[j].pBuffer = func_020236f8(0x1e0, 0x20, data_0204c024);
            ctx[n]->entries[i].slots[j].writeOffset = 0;
            ctx[n]->entries[i].slots[j].state = 0;
        }
        ctx[n]->entries[i].field1c = 0;
        ctx[n]->entries[i].pActive = &ctx[n]->entries[i].slots[0];
    }
    func_020310e8();
    ctx[n]->f0 = 0;
    desc = data_02042110;
    ids = data_02042108;
    for (i = 0; i < 2; i++) {
        desc.nClassId = ids.id[i];
        ctx[n]->classHandle[i] = func_02023930(&desc, i);
    }
    return func_02030fcc;
}
