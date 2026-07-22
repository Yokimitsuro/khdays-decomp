/* Channel-6 receive handler for the link-sync block. A 4-byte packet is one
 * player's record: bits 3..5 of its first byte are the sender's slot, so it
 * lands in aSlots[that slot] and raises the dirty bit. A 0x10-byte packet is the
 * host's full broadcast of all four records and lands in the mirror. Any other
 * length is dropped.
 *
 * That slot index is the evidence aSlots is four 4-byte records rather than one
 * 0x10-byte blob -- see func_ov002_02066d38, whose MI_CpuFill8 measures the
 * whole object at 0x25 bytes. */
typedef struct {
    unsigned char bLocal[4];        /* +0x00 this machine's record */
    unsigned char aPeers[0x10];     /* +0x04 last full broadcast received, 4 records */
    unsigned char aSlots[4][4];     /* +0x14 the table we publish, one record per player */
    unsigned char bSlotsDirty : 1;  /* +0x24 bit 0 */
    unsigned char bLocalPending : 1;/*       bit 1 */
    unsigned char bMirrorReady : 1; /*       bit 2 */
} Ov002LinkSyncCtx;

typedef struct {
    unsigned char nKind : 3;
    unsigned char nSlot : 3;
} Ov002LinkRecord;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

extern Ov002LinkSyncCtx *data_ov002_0207f9f4;

void func_ov002_02066cc8(Ov002LinkRecord *pkt, int len) {
    Ov002LinkSyncCtx *ctx = data_ov002_0207f9f4;

    switch (len) {
    case 4:
        MI_CpuCopy8(pkt, ctx->aSlots[pkt->nSlot], 4);
        ctx->bSlotsDirty = 1;
        break;

    case 0x10:
        MI_CpuCopy8(pkt, ctx->aPeers, 0x10);
        ctx->bMirrorReady = 1;
        break;
    }
}
