/* Ov022_StepSlotByPartState -- drive a slot forward through its part's state.
 *
 * Unlike the drivers that switch on the slot's own state, this one reads the
 * state of the slot's first part and looks the step up in a table, so a state
 * with no entry simply does nothing. A step that reports it finished takes one
 * off the slot's sequence count.
 *
 * Two more things can keep the slot busy: an animation still running on the
 * slot's own tracks, and a part in state 1, whose timer runs until it reaches
 * the slot's limit and then hands over.
 *
 * The slot is finished only when none of the three had anything to do.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* one of the 0x150-byte parts the slot owns */
struct SlotPart {
    int nTimer;                  /* 0x000 */
    u8 pad004[0x148];
    u8 nState;                   /* 0x14c */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 pad000[2];
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0x136];
    int nLimit;                  /* 0x140 */
    u8 pad144[0x24];
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

extern StepFn const data_ov022_020b29d0[];

extern int func_0202a818(u16 *pFlags, int nDelta);
extern void func_ov022_0208e978(struct ReactionCtx *pCtx, struct ActorSlot *pSlot,
                                int nMode);

int func_ov022_0208f5cc(struct ReactionCtx *pCtx, int nDelta)
{
    struct ActorSlot *pSlot;
    StepFn pfnStep;
    int bDone;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 1;
    if (pSlot->pParts->nState != 0) {
        bDone = 0;
        pfnStep = data_ov022_020b29d0[pSlot->pParts->nState];
        if (pfnStep != 0) {
            if (pfnStep(pCtx, pSlot->pParts, nDelta) != 0) {
                pSlot->nSeq = pSlot->nSeq - 1;
            }
        }
    }
    if (pSlot->nAnimHold != 0) {
        if (func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nAnimHold = 0;
        }
        bDone = 0;
    }
    if (pSlot->pParts->nState == 1) {
        pSlot->pParts->nTimer = pSlot->pParts->nTimer + nDelta;
        if (pSlot->pParts->nTimer >= pSlot->nLimit) {
            func_ov022_0208e978(pCtx, pSlot, 0);
        }
        bDone = 0;
    }
    return bDone;
}
