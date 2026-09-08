/* Ov022_StepChargeSlot -- one frame of the slot that carries a charge.
 *
 * The slot's timer always takes the frame first. While the session is ready and
 * this is a trigger slot on an actor carrying the marked flag, the slot hands
 * its initial power to the actor as its interrupt charge -- once, which the
 * sent bit remembers -- and an armed slot in the second state asks the actor to
 * hold the trigger.
 *
 * Then the slot's own state decides the frame: the first state reports the slot
 * finished; the second aims it at the actor's aim point lifted a fixed amount,
 * applies the pending hit once the interval has passed, and steps its tracks,
 * which on ending clear the slot index, reset the timer and move it to the
 * fourth state; the fourth waits out the hold -- or ends at once if the session
 * is not ready -- then steps the sequence back one and returns to the first.
 *
 * The state test is a switch, not a chain of ifs: that is what tests all three
 * states up front and leaves each body out of line, and the two pointers are
 * declared with the actor first because that is what colours it below the slot.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned long long u64;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                        /* 0x000 */
    u8 pad001;
    u8 nSeq;                         /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;                  /* 0x008 */
    u8 pad00a[0xa2];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[7];
    u8 nState;                       /* 0x118 */
    u8 pad119[3];
    int nTimer;                      /* 0x11c */
    u8 pad120[8];
    int bPowerPending;               /* 0x128 */
    int nInterval;                   /* 0x12c */
    int nPowerInit;                  /* 0x130 */
    u8 bArmed : 1;                   /* 0x134 bit 0 */
    u8 nSpare : 2;
    u8 bChargeSent : 1;              /*       bit 3 */
    u8 nSpareTop : 4;
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x464];
    u64 nFlags2;                     /* 0x464 */
    u8 pad46c[0x20];
    struct VecFx32 vecAim;           /* 0x48c */
    u8 pad498[0x1c];
    int nInterruptCharge;            /* 0x4b4 */
    u8 pad4b8[0x1dc];
    u8 nStateFlags;                  /* 0x694: bit 6 holds the trigger */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];    /* 0x18 */
    u8 pad44[0x14];
    struct Actor *pActor;            /* 0x58 */
};

/* Session_IsReady */
extern int func_02030694(void);
/* Ov022_ApplyReactionHit */
extern void func_ov022_0208fb34(struct ReactionCtx *pCtx,
                                struct ActorSlot *pSlot);
/* Sequence_UpdateTracks */
extern int func_0202a818(u16 *pFlags, int nDelta);

#define KIND_TRIGGER 0xc
#define ACTOR_FLAG_CHARGE 0x1000ULL
#define ACTOR_TRIGGER_HELD 0x40
#define AIM_LIFT 0x119a
#define HOLD_LIMIT 0x3000

int func_ov022_0208f980(struct ReactionCtx *pCtx, int nDelta)
{
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    int bDone;
    struct VecFx32 vecAim;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 0;
    pSlot->nTimer = pSlot->nTimer + nDelta;
    if (func_02030694() != 0 && pSlot->nKind == KIND_TRIGGER
        && (pActor->nFlags2 & ACTOR_FLAG_CHARGE) != 0) {
        if (pSlot->nPowerInit > 0 && pSlot->bChargeSent == 0) {
            pActor->nInterruptCharge = pSlot->nPowerInit;
            pSlot->bChargeSent = 1;
        }
        if (pSlot->bArmed != 0 && pSlot->nState == 2) {
            pActor->nStateFlags |= ACTOR_TRIGGER_HELD;
        }
    }
    switch (pSlot->nState) {
    case 0:
        bDone = 1;
        break;
    case 2:
        vecAim = pActor->vecAim;
        vecAim.y = vecAim.y + AIM_LIFT;
        pSlot->vecAim = vecAim;
        if (pSlot->nTimer >= pSlot->nInterval && pSlot->bPowerPending != 0) {
            func_ov022_0208fb34(pCtx, pSlot);
            pSlot->bPowerPending = 0;
        }
        if (func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nSlotIndex = -1;
            pSlot->nTimer = 0;
            pSlot->nState = 4;
        }
        break;
    case 4:
        if (func_02030694() != 0) {
            if (pSlot->nTimer >= HOLD_LIMIT) {
                bDone = 1;
            }
        } else {
            bDone = 1;
        }
        if (bDone != 0) {
            pSlot->nSeq = pSlot->nSeq - 1;
            pSlot->nState = 0;
        }
        break;
    }
    return bDone;
}
