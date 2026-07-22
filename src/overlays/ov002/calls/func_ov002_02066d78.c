/* Per-frame step of the link-sync block, registered by func_ov002_02066d38.
 *
 * With the local record pending: the host copies it straight into its own slot
 * 0, a client sends it as a 4-byte channel-6 packet. Both paths move 4 bytes,
 * which is why the ROM hoists the size above the branch.
 *
 * With the slots dirty: broadcast all 0x10 bytes of the table, then drop bit
 * 0x40 of each record -- the "just published" mark. Always ends by clearing the
 * mirror-ready bit, and always reports 0. */
typedef struct {
    unsigned char bLocal[4];        /* +0x00 this machine's record */
    unsigned char aPeers[0x10];     /* +0x04 last full broadcast received, 4 records */
    unsigned char aSlots[4][4];     /* +0x14 the table we publish, one record per player */
    unsigned char bSlotsDirty : 1;  /* +0x24 bit 0 */
    unsigned char bLocalPending : 1;/*       bit 1 */
    unsigned char bMirrorReady : 1; /*       bit 2 */
} Ov002LinkSyncCtx;

extern int func_02030694(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_02031258(int channel, const void *src, unsigned int size);

extern Ov002LinkSyncCtx *data_ov002_0207f9f4;

int func_ov002_02066d78(void) {
    Ov002LinkSyncCtx *ctx = data_ov002_0207f9f4;

    if (ctx->bLocalPending) {
        if (func_02030694()) {
            MI_CpuCopy8(ctx->bLocal, ctx->aSlots[0], 4);
            ctx->bSlotsDirty = 1;
        } else {
            func_02031258(6, ctx->bLocal, 4);
        }
        ctx->bLocalPending = 0;
    }

    if (ctx->bSlotsDirty) {
        func_02031258(6, ctx->aSlots[0], 0x10);
        {
            int i = 0;
            unsigned char *rec = ctx->aSlots[0];

            do {
                i++;
                *rec &= ~0x40;
                rec += 4;
            } while (i < 4);
        }
        ctx->bSlotsDirty = 0;
    }

    ctx->bMirrorReady = 0;
    return 0;
}
