/* Ov022_StepSlotParts -- run one frame of every part a slot owns.
 *
 * Each part in a state other than idle picks its step from the table by state
 * and runs it; a slot with any such part is not finished. When the slot is
 * still running it also ages its own timer, retires the pending sequence once
 * the tracks report it done, and arms the next part while there are any left --
 * either because the timer has reached the delay or because none has been armed
 * yet. A slot that ends the frame with nothing left running is closed and gives
 * its sequence slot back.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022AnimBlock */
struct AnimBlock {
    u16 nFlags;                  /* 0x00 */
    u8 pad02[0xa2];
    struct VecFx32 vecAt;        /* 0xa4 */
    int aEntryFlags[3];          /* 0xb0 */
};

/* Ov022SlotPart */
struct SlotPart {
    int nTimer;                  /* 0x000 */
    struct VecFx32 vecPos;       /* 0x004 */
    struct VecFx32 vecVel;       /* 0x010 */
    struct AnimBlock anim;       /* 0x01c */
    u8 pad0d8[0x70];
    void *pOwner;                /* 0x148 */
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
    int nPending;                /* 0x170 */
    s8 nTurns;                   /* 0x174 */
    u8 nArmed;                   /* 0x175 */
    u8 nArmMax;                  /* 0x176 */
    u8 pad177;
    int nMarkNext;               /* 0x178 */
    int nArmDelay;               /* 0x17c */
};

struct Actor;

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x14];
    struct Actor *pActor;        /* 0x58 */
};

typedef int (*PartStep)(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta);

/* One step routine per part state; the idle state is never looked up. */
extern PartStep data_ov022_020b29d0[];

extern int func_0202a818(u16 *pFlags, int nDelta);
extern int func_ov022_0208e978(struct ReactionCtx *pCtx,
                               struct ActorSlot *pSlot, int nArmed);

#define PART_STRIDE 0x150

int func_ov022_0208e66c(struct ReactionCtx *pCtx, int nDelta, int nArg2,
                        PartStep pStep)
{
    struct ActorSlot *pSlot;
    struct SlotPart *pPart;
    int bDone;
    int nPart;
    int nOffset;
    int nState;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 1;
    nPart = 0;
    if (nPart < pSlot->nParts) {
        nOffset = 0;
        do {
            pPart = (struct SlotPart *)((u8 *)pSlot->pParts + nOffset);
            nState = pPart->nState;
            if (nState != 0) {
                pStep = data_ov022_020b29d0[nState];
                bDone = 0;
                if (pStep != 0) {
                    pStep(pCtx, pPart, nDelta);
                }
            }
            nPart++;
            nOffset += PART_STRIDE;
        } while (nPart < pSlot->nParts);
    }
    if ((u8)pSlot->nTurns == 0) {
        return bDone;
    }
    pSlot->nMarkNext = pSlot->nMarkNext + nDelta;
    if (pSlot->nPending != 0 && func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
        pSlot->nPending = 0;
    }
    if (pSlot->nArmed < pSlot->nArmMax) {
        bDone = 0;
        if ((pSlot->nMarkNext >= pSlot->nArmDelay || pSlot->nArmed == 0)
            && func_ov022_0208e978(pCtx, pSlot, pSlot->nArmed) != 0) {
            pSlot->nMarkNext = 0;
            pSlot->nArmed = pSlot->nArmed + 1;
        }
    }
    if (bDone != 0) {
        pSlot->nTurns = 0;
        pSlot->nSeq = pSlot->nSeq - 1;
    }
    return bDone;
}
