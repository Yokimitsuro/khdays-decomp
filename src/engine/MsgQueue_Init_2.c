#include "nitro/types.h"

#include "game/class_descriptor.h"
#include "game/heap.h"
#pragma thumb on
/* MsgQueue_Init_2 = MsgQueue_Init (THUMB). Sets up the message-queue context: it lives at the base of
 * the current root heap and is published in gMsgQueue. The queue gets two entries (0x20 bytes
 * each, from the default heap); every entry owns two 0x1e0-byte buffers (32-byte aligned) and starts
 * with the first one active. Table6_ResetAll (Table6_ResetAll) then clears the send state, and the two
 * transfer tasks are instantiated (InstantiateClass, InstantiateClass) from the descriptor template
 * data_02042110 with the class ids of data_02042108. Returns MsgQueue_GetHeap (MsgQueue_GetHeap). */

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

typedef struct MsgQueueClassIds {
    int id[2];
} MsgQueueClassIds;

extern MsgQueueCtx *NNSi_FndGetCurrentRootHeap(void);
extern void Table6_ResetAll(void);                                /* Table6_ResetAll */
extern int InstantiateClass(const GameClassDescriptor *desc, int param);  /* InstantiateClass */
extern void MsgQueue_GetHeap(void);                                /* MsgQueue_GetHeap */
extern MsgQueueCtx *gMsgQueue;
extern GameHeap *gMainHeap;
extern const GameClassDescriptor data_02042110;
extern const MsgQueueClassIds data_02042108;

void *MsgQueue_Init_2(void)
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
    gMsgQueue = ctx[n];
    ctx[n]->count = 2;
    ctx[n]->entries = AllocFromExpHeapWrapper(ctx[n]->count * sizeof(MsgQueueEntry), gMainHeap);
    for (i = 0; i < ctx[n]->count; i++) {
        for (j = 0; j < 2; j++) {
            ctx[n]->entries[i].slots[j].pBuffer = ExpHeap_AllocOrDefault(0x1e0, 0x20, gMainHeap);
            ctx[n]->entries[i].slots[j].writeOffset = 0;
            ctx[n]->entries[i].slots[j].state = 0;
        }
        ctx[n]->entries[i].field1c = 0;
        ctx[n]->entries[i].pActive = &ctx[n]->entries[i].slots[0];
    }
    Table6_ResetAll();
    ctx[n]->f0 = 0;
    desc = data_02042110;
    ids = data_02042108;
    for (i = 0; i < 2; i++) {
        desc.nClassId = ids.id[i];
        ctx[n]->classHandle[i] = InstantiateClass(&desc, i);
    }
    return MsgQueue_GetHeap;
}
