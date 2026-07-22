/* Fill in this machine's link-sync record from a 4-halfword request and mark it
 * pending, so the next Ov002_LinkSyncStep publishes it.
 *
 * The record's first byte is three fields: kind in bits 0..2, the sender's slot
 * in bits 3..5, and the "fresh" mark in bit 6. Slot and fresh are written as two
 * consecutive statements and mwcc folds them into one store -- that is the
 * `and #0xff; orr #0x40` pair, not a single hand-built constant.
 *
 * Kind is 1 for request[2] == 0; for request[2] == 1 it is 2 or 0 depending on
 * request[3]. Any other value leaves the previous kind alone. */
typedef struct {
    unsigned char nKind : 3;    /* +0x00 bits 0..2 */
    unsigned char nSlot : 3;    /*       bits 3..5 */
    unsigned char bFresh : 1;   /*       bit 6 */
    unsigned char bValueA;      /* +0x01 */
    unsigned char bValueB;      /* +0x02 */
    unsigned char pad03;
} Ov002LinkRecord;

typedef struct {
    Ov002LinkRecord local;          /* +0x00 this machine's record */
    Ov002LinkRecord aPeers[4];      /* +0x04 last full broadcast received */
    Ov002LinkRecord aSlots[4];      /* +0x14 the table we publish */
    unsigned char bSlotsDirty : 1;  /* +0x24 bit 0 */
    unsigned char bLocalPending : 1;/*       bit 1 */
    unsigned char bMirrorReady : 1; /*       bit 2 */
} Ov002LinkSyncCtx;

extern int func_02030788(void);

extern Ov002LinkSyncCtx *data_ov002_0207f9f4;

void func_ov002_02066f14(unsigned short *request) {
    Ov002LinkSyncCtx *ctx = data_ov002_0207f9f4;

    if (ctx == 0) {
        return;
    }

    ctx->local.bValueA = request[0];
    ctx->local.bValueB = request[1];
    ctx->local.nSlot = (unsigned char)func_02030788();
    ctx->local.bFresh = 1;

    /* case 1 is written first so it is the inline fall-through, matching the
     * ROM's `cmp #0 / beq out-of-line / cmp #1 / bne end` dispatch. */
    switch (request[2]) {
    case 1:
        if (request[3] == 0) {
            ctx->local.nKind = 2;
        } else {
            ctx->local.nKind = 0;
        }
        break;

    case 0:
        ctx->local.nKind = 1;
        break;
    }

    ctx->bLocalPending = 1;
}
