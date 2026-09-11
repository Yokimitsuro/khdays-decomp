/* Ov022_StepReactionState -- drive a reaction context through its states.
 *
 * Only a context whose slot mask allows it runs at all. Each state hands the
 * frame to the per-slot handler taken from the handler table after its own
 * work, and a message id of 0xffff means no message is in flight:
 *
 *   0  waiting: outside a ready session, a context flagged 4 starts (state 3),
 *      posts its move mode and label, swaps flag 4 for 0x80.
 *   1  sends the open message for the slot; once it has an id, state 2.
 *   2  when the message is gone the label is rebuilt and the slot starts.
 *   3  raises flag 8 when the owner reports its bit and flag 0x10 when the cue
 *      track ends; with both up it goes to 6 in a ready session, else 7.
 *   4  after the message is gone, the handler's result (or flag 0x40) decides
 *      whether the close message is sent (state 8), unless the actor's bit 12
 *      is set.
 *   5  when the message is gone the sub-state dispatch begins (state 6).
 *   6  with no message pending: flag 0x20 sends message 1 (state 4), otherwise
 *      an actor with bit 12, flag 0x80 and an animation frame past 0x12000
 *      takes the actor's hit reaction as the kind and marshals it (state 5).
 *      A successful handler with flag 0x40, no message, no bit 12 and no flag
 *      0x80 sends the close message (state 8).
 *   7  a successful handler (flag 0x40) or flag 0x20 closes (state 8).
 *   8  in a ready session, once the message is gone the timer restarts and
 *      state 9 begins; outside one, flag 0x200 clears the context.
 *   9  while the actor's hit reaction differs from the slot's move mode the
 *      timer runs, and past 0x9000 the context is cleared.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

/* Ov022Actor */
struct Actor {
    u8 pad0000[0x464];
    u64 nFlags2;                     /* 0x0464 */
    u8 pad046c[0x250];
    int nHitReaction;                /* 0x06bc */
    u8 pad06c0[0xf0];
    int nAnimFrame;                  /* 0x07b0 */
    u8 pad07b4[0x5dc];
    int animReq[4];                  /* 0x0d90 Ov022AnimRequest */
    u8 aSubBlocks[1];                /* 0x0da0 Ov022ActorSubBlock[2], cue track first */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u16 nFlags;                      /* 0x00 */
    u8 nState;                       /* 0x02 */
    u8 pad03[1];
    int nTimer;                      /* 0x04 */
    struct Actor *pShooter;          /* 0x08 */
    int nSlot;                       /* 0x0c */
    int nCue;                        /* 0x10 */
    int nKind;                       /* 0x14 */
    u8 pad18[0x3c];
    u8 *pOwner;                      /* 0x54 */
    struct Actor *pActor;            /* 0x58 */
    short aHitIds[8];                /* 0x5c */
    u16 nMsgId;                      /* 0x6c */
    u8 pad6e[2];
};

#define MSG_NONE 0xffff
#define ALL_SLOTS 0xffffffff
#define FLAG_START 0x4
#define FLAG_OWNER_BIT 0x8
#define FLAG_CUE_DONE 0x10
#define FLAG_20 0x20
#define FLAG_40 0x40
#define FLAG_80 0x80
#define FLAG_200 0x200
#define ACTOR_BIT12 0x1000ULL
#define FRAME_LIMIT 0x12000
#define TIMEOUT 0x9000
#define FLAG_SET(nFlags, nBit) (((nFlags) & (nBit)) > 0)

extern int (*const data_ov022_020b2a5c[])(struct ReactionCtx *pCtx, int nDelta);

extern int func_ov022_0209029c(u16 *pCtx, unsigned int nMask);
extern int func_02030694(void);
extern int func_ov022_02090978(struct ReactionCtx *pCtx, int nSlot);
extern void func_ov022_020b19ec(int *pAnimReq, int nMode);
extern void func_ov022_0208a830(struct ReactionCtx *pCtx, int nSlot);
extern int func_ov022_0208a464(struct ReactionCtx *pCtx, int nKind, int *pSlot);
extern int func_02031440(unsigned int nMsgId);
extern int func_ov022_020b1510(u8 *pOwner);
extern int func_ov022_020b1cec(u8 *pCueTrack, int nCue);
extern void func_ov022_0208a6d0(struct ReactionCtx *pCtx);
extern void func_ov022_0208a624(struct ReactionCtx *pCtx, int nKind);
extern void func_ov022_0208a790(struct ReactionCtx *pCtx);

void func_ov022_0209045c(struct ReactionCtx *pCtx, int nDelta)
{
    struct Actor *pActor;
    int nResult;
    u16 nFlags;

    if (func_ov022_0209029c((u16 *)pCtx, ALL_SLOTS) == 0) {
        return;
    }
    pActor = pCtx->pActor;
    switch (pCtx->nState) {
    case 0:
        if (func_02030694() == 0 && (pCtx->nFlags & FLAG_START) != 0) {
            pCtx->nState = 3;
            func_ov022_020b19ec(pActor->animReq,
                                func_ov022_02090978(pCtx, pCtx->nSlot));
            func_ov022_0208a830(pCtx, pCtx->nSlot);
            pCtx->nFlags &= ~FLAG_START;
            pCtx->nFlags |= FLAG_80;
        }
        if (pCtx->nSlot >= 0) {
            data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        }
        break;
    case 1:
        pCtx->nMsgId = func_ov022_0208a464(pCtx, 0, &pCtx->nSlot);
        if (pCtx->nMsgId != MSG_NONE) {
            pCtx->nState = 2;
        }
        break;
    case 2:
        if (func_02031440(pCtx->nMsgId) == 0) {
            pCtx->nMsgId = MSG_NONE;
            pCtx->nState = 3;
            func_ov022_0208a830(pCtx, pCtx->nSlot);
        }
        data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        break;
    case 3:
        if (!FLAG_SET(pCtx->nFlags, FLAG_OWNER_BIT)
            && func_ov022_020b1510(pCtx->pOwner) != 0) {
            pCtx->nFlags |= FLAG_OWNER_BIT;
        }
        if (!FLAG_SET(pCtx->nFlags, FLAG_CUE_DONE)
            && func_ov022_020b1cec(pActor->aSubBlocks, pCtx->nCue) != 0) {
            pCtx->nFlags |= FLAG_CUE_DONE;
        }
        if ((pCtx->nFlags & FLAG_CUE_DONE) != 0 && (pCtx->nFlags & FLAG_OWNER_BIT) != 0) {
            if (func_02030694() != 0) {
                pCtx->nState = 6;
            } else {
                pCtx->nState = 7;
            }
        }
        data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        break;
    case 4:
        if (func_02031440(pCtx->nMsgId) == 0) {
            pCtx->nMsgId = MSG_NONE;
        }
        nResult = data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        if (pCtx->nMsgId != MSG_NONE) {
            return;
        }
        if ((pActor->nFlags2 & ACTOR_BIT12) != 0) {
            return;
        }
        if ((pCtx->nFlags & FLAG_40) != 0) {
            if (nResult != 0) {
                pCtx->nMsgId = func_ov022_0208a464(pCtx, 5, 0);
                if (pCtx->nMsgId != MSG_NONE) {
                    pCtx->nState = 8;
                }
            }
            return;
        }
        pCtx->nMsgId = func_ov022_0208a464(pCtx, 5, 0);
        if (pCtx->nMsgId != MSG_NONE) {
            pCtx->nState = 8;
        }
        break;
    case 5:
        if (func_02031440(pCtx->nMsgId) == 0) {
            func_ov022_0208a6d0(pCtx);
            pCtx->nMsgId = MSG_NONE;
            pCtx->nState = 6;
        }
        data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        break;
    case 6:
        if (pCtx->nMsgId == MSG_NONE) {
            nFlags = pCtx->nFlags;
            if ((nFlags & FLAG_20) != 0) {
                pCtx->nMsgId = func_ov022_0208a464(pCtx, 1, 0);
                if (pCtx->nMsgId != MSG_NONE) {
                    pCtx->nState = 4;
                }
            } else if ((pActor->nFlags2 & ACTOR_BIT12) != 0 && (nFlags & FLAG_80) != 0
                       && pActor->nAnimFrame >= FRAME_LIMIT) {
                pCtx->nKind = pActor->nHitReaction;
                func_ov022_0208a624(pCtx, pCtx->nKind);
                if (pCtx->nMsgId != MSG_NONE) {
                    pCtx->nState = 5;
                }
            }
        }
        nResult = data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        if (nResult == 0) {
            return;
        }
        nFlags = pCtx->nFlags;
        if ((nFlags & FLAG_40) == 0) {
            return;
        }
        if (pCtx->nMsgId != MSG_NONE) {
            return;
        }
        if ((pActor->nFlags2 & ACTOR_BIT12) != 0) {
            return;
        }
        if ((nFlags & FLAG_80) != 0) {
            return;
        }
        pCtx->nMsgId = func_ov022_0208a464(pCtx, 5, 0);
        if (pCtx->nMsgId != MSG_NONE) {
            pCtx->nState = 8;
        }
        break;
    case 7:
        nResult = data_ov022_020b2a5c[pCtx->nSlot](pCtx, nDelta);
        if ((pCtx->nFlags & FLAG_40) != 0) {
            if (nResult != 0) {
                pCtx->nState = 8;
            }
        } else if ((pCtx->nFlags & FLAG_20) != 0) {
            pCtx->nState = 8;
        }
        break;
    case 8:
        if (func_02030694() != 0) {
            if (func_02031440(pCtx->nMsgId) == 0) {
                pCtx->nTimer = 0;
                pCtx->nState = 9;
            }
        } else if ((pCtx->nFlags & FLAG_200) != 0) {
            func_ov022_0208a790(pCtx);
        }
        break;
    case 9:
        if (pActor->nHitReaction != func_ov022_02090978(pCtx, pCtx->nSlot)) {
            pCtx->nTimer += nDelta;
            if (pCtx->nTimer >= TIMEOUT) {
                func_ov022_0208a790(pCtx);
            }
        }
        break;
    }
}
