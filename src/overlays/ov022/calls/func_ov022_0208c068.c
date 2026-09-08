/* Ov022_StepSlotPartsD -- drive every part of a slot forward by a frame.
 *
 * The fourth of the multi-part drivers, and the only one that treats state 3
 * differently from the others: it runs the same table step but throws the
 * answer away, so a part in that state can never take the slot down. States 1
 * and 4 go through the table and do count, state 2 has a routine of its own,
 * and a part in state 0 is free and is skipped.
 *
 * As in the single-part driver, an animation still running on the slot's own
 * tracks also keeps it busy, and the slot is finished only when nothing had
 * anything to do.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* one of the 0x150-byte parts the slot owns */
struct SlotPart {
    u8 pad000[0x14c];
    u8 nState;                   /* 0x14c */
    u8 pad14d[3];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000;
    u8 nParts;                   /* 0x001 */
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0x15e];
    struct SlotPart *pParts;     /* 0x168 */
    u8 pad16c[4];
    int nAnimHold;               /* 0x170 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
};

typedef int (*StepFn)(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                      int nDelta);

extern StepFn const data_ov022_020b29bc[];

extern int func_0202a818(u16 *pFlags, int nDelta);
extern void func_ov022_0208c164(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                                int nDelta);

int func_ov022_0208c068(struct ReactionCtx *pCtx, int nDelta)
{
    struct ActorSlot *pSlot;
    struct SlotPart *pPart;
    int bDone;
    int i;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 1;
    for (i = 0; i < pSlot->nParts; i++) {
        pPart = &pSlot->pParts[i];
        if (pPart->nState != 0) {
            bDone = 0;
            switch (pPart->nState) {
            case 3:
                data_ov022_020b29bc[pPart->nState](pCtx, pPart, nDelta);
                break;
            case 2:
                func_ov022_0208c164(pCtx, pPart, nDelta);
                break;
            case 1:
            case 4:
                if (data_ov022_020b29bc[pPart->nState](pCtx, pPart, nDelta) != 0) {
                    pSlot->nSeq = pSlot->nSeq - 1;
                }
                break;
            }
        }
    }
    if (pSlot->nAnimHold != 0) {
        if (func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nAnimHold = 0;
        }
        bDone = 0;
    }
    return bDone;
}
