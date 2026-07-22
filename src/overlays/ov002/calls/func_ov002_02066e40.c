/* Look one peer's published record up by slot and unpack it into a 4-halfword
 * reply. Only the last received broadcast is searched, and only while it is
 * marked ready.
 *
 * Two ways to report nothing, and they are different states: no context, no
 * broadcast or no matching slot all leave the reply untouched; a match whose
 * "fresh" bit (0x40) has already been consumed returns immediately without even
 * reaching the reply. Both report 0.
 *
 * reply[2] is the "is this an accept" flag -- kind 2 or kind 4 -- which is why
 * the ROM range-folds the pair with cmp/cmpne. It is materialised TWICE (once
 * for the pair test, once for the halfword store), so the flag has to go through
 * a local and be stored as `isAccept ? 1 : 0`; folding the two costs 12 bytes.
 *
 * Declaring the loop counter at function scope is load-bearing: it is what puts
 * `found` in r3 and the field scratch in ip. With `int i` scoped to the loop the
 * two swap, and no ordering of result/found fixes it -- five permutations were
 * tried. */
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

extern Ov002LinkSyncCtx *data_ov002_0207f9f4;

int func_ov002_02066e40(unsigned short *reply, unsigned int slot) {
    Ov002LinkSyncCtx *ctx = data_ov002_0207f9f4;
    int i;
    int result = 1;
    Ov002LinkRecord *found = 0;

    if (ctx == 0) {
        return 0;
    }

    if (ctx->bMirrorReady) {
        for (i = 0; i < 4; i++) {
            if (slot == ctx->aPeers[i].nSlot) {
                found = &ctx->aPeers[i];
                if (found->bFresh == 0) {
                    return 0;
                }
                break;
            }
        }
    }

    if (found == 0) {
        result = 0;
    } else {
        int isAccept;

        reply[0] = found->bValueA;
        reply[1] = found->bValueB;
        isAccept = found->nKind == 2 || found->nKind == 4;
        reply[2] = isAccept ? 1 : 0;
        reply[3] = 0;
    }
    return result;
}
