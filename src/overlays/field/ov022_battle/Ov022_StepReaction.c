/* Ov022_StepReaction -- drive one reaction slot forward by a frame of time.
 *
 * The counterpart of the reaction entries: they arm a slot, this runs it. The
 * slot's timer takes the frame's delta and the state decides what happens next.
 *
 *   0  finished -- report it and let the caller retire the slot
 *   1  wind-up: once the interval is up the pending power is swapped in, and
 *      when the animation reports a beat the slot moves to the repeat state
 *      with a fresh binding, fresh loop flags and a fresh interval
 *   2  repeat: every interval counts one repetition and restarts the timer,
 *      and once the count reaches its limit the slot moves on
 *   3  recovery: on the next beat the slot index is cleared and the slot waits
 *   4  wait: it ends on the next input, or once the timer passes the hold
 *
 * Returns whether the slot has finished this frame.
 */

/* Ov022ActorSlot */

#include "nitro/types.h"
#include "game/engine.h"

struct ActorSlot {
    u8 pad000[2];
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0xae];
    int aEntryFlags[3];          /* 0x0b8 */
    u8 pad0c4[0x4c];
    signed char nSlotIndex;      /* 0x110 */
    u8 pad111[7];
    u8 nState;                   /* 0x118 */
    u8 pad119[3];
    int nTimer;                  /* 0x11c */
    int nPower;                  /* 0x120 */
    int nRadius;                 /* 0x124 */
    int bPowerPending;           /* 0x128 */
    int nInterval;               /* 0x12c */
    u8 pad130[8];
    int nRepeat;                 /* 0x138 */
    int nRepeatMax;              /* 0x13c */
    u8 pad140[4];
    int nPowerNext;              /* 0x144 */
    int nIntervalNext;           /* 0x148 */
    u8 pad14c[4];
    int nLoopFlags;              /* 0x150 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x10];
    u8 *pLevelAnim;                 /* 0x54: the cast's level animation (its grid entry) */
};

#define WAIT_HOLD 0x3000

extern void Ov022_ApplyReactionHit(struct ReactionCtx *pCtx, struct ActorSlot *pSlot);
extern void Ov022_BindBlockAnimations(struct ReactionCtx *pCtx, void *pTarget, u16 *pFlags,
                                int nBinding);
extern unsigned short Sequence_UpdateTracks(u16 *pFlags, int nDelta);

int Ov022_StepReaction(struct ReactionCtx *pCtx, int nDelta)
{
    struct ActorSlot *pSlot;
    int bDone;
    int nLoop;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    bDone = 0;
    pSlot->nTimer = pSlot->nTimer + nDelta;
    switch (pSlot->nState) {
    case 0:
        bDone = 1;
        break;
    case 1:
        if (pSlot->nTimer >= pSlot->nInterval && pSlot->bPowerPending != 0) {
            Ov022_ApplyReactionHit(pCtx, pSlot);
            pSlot->bPowerPending = 0;
            pSlot->nPower = pSlot->nPowerNext;
        }
        if (Sequence_UpdateTracks(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nTimer = 0;
            pSlot->nState = 2;
            Ov022_BindBlockAnimations(pCtx, pCtx->pLevelAnim + 4, &pSlot->nSlotFlags, 1);
            nLoop = pSlot->nLoopFlags;
            pSlot->aEntryFlags[2] = nLoop;
            pSlot->aEntryFlags[1] = nLoop;
            pSlot->aEntryFlags[0] = nLoop;
            pSlot->nInterval = pSlot->nIntervalNext;
        }
        break;
    case 2:
        if (pSlot->nTimer >= pSlot->nInterval) {
            pSlot->nRepeat = pSlot->nRepeat + 1;
            Ov022_ApplyReactionHit(pCtx, pSlot);
            pSlot->nTimer = 0;
        }
        if (Sequence_UpdateTracks(&pSlot->nSlotFlags, nDelta) != 0
            && pSlot->nRepeat >= pSlot->nRepeatMax) {
            pSlot->nState = 3;
        }
        break;
    case 3:
        if (Sequence_UpdateTracks(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nSlotIndex = -1;
            pSlot->nTimer = 0;
            pSlot->nState = 4;
        }
        break;
    case 4:
        if (Session_IsReady() != 0) {
            if (pSlot->nTimer >= WAIT_HOLD) {
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
