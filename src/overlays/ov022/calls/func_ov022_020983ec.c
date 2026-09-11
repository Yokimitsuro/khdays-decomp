/* Ov022_TryPendingAction -- turn the actor's pending action into a state
 * change; returns the change made, or 0.
 *
 * Action 3 (with nArg 0, and either input bit 2 or flag bit 36 with flag-2
 * bit 7) needs the reaction block and the animation request to agree; it then
 * goes to state 6 when the two flag bits are up, else 0, and tells the actor's
 * hook 0x1a. Action 4 (with nArg 0) needs the slot action allowed and the
 * request to agree; it goes to 0 on input bit 2, else 6 with the two flag
 * bits, else 2, and hands the hook the slot's move mode. When either fails on
 * the local machine, flag-2 bit 55 is raised and the general cases follow.
 *
 * Action 1 raises flag bit 32 when the reach block is active without input
 * bit 2; then state 3 with input bit 2 and neither bit 32 nor flag-2 bit 36,
 * else 0xe (input) or 0xf, and with bit 32 the interrupt charge is stretched
 * to the combo window (or the animation length when the window is unset).
 * Action 2 goes to 0x13 when input bit 2 is set without both flag bits, or
 * without input when the sub kind has bit 7 and flag bit 43 is clear. Actions
 * 5 and 6 go to 0x18 and 0x19.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Actor;

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[4];
    u16 nAnimFlags;                  /* 0x04 */
};

/* Ov022ComboRecord */
struct ComboRecord {
    u8 pad00[0xc];
    int nWindow;                     /* 0x0c */
};

/* Ov022ComboLock */
struct ComboLock {
    u8 pad00[0x14];
    struct ComboRecord *pRecord;     /* 0x14 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad0008[0x14];
    u16 nPendingAction;              /* 0x001c */
    u8 pad001e[2];
    struct ActorNode *pNode;         /* 0x0020 */
    u32 nInputMask;                  /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                     /* 0x0464 */
    u8 pad046c[0x48];
    int nInterruptCharge;            /* 0x04b4 */
    u8 pad04b8[0x26];
    u16 nLatchedArg;                 /* 0x04de */
    u8 pad04e0[0x184];
    void (*pfnPreDraw)(struct Actor *pActor, int nMode); /* 0x0664 */
    u8 pad0668[0x718];
    struct ComboLock *pComboLock;    /* 0x0d80 */
    u8 pad0d84[0xc];
    u8 animReq[0xefc];               /* 0x0d90 */
    u8 blkReach[0x11c];              /* 0x1c8c */
    u8 reactionBlk[0x4e0];           /* 0x1da8 */
    u8 reactionCtx[1];               /* 0x2288 */
};

#define FLAG_BIT32 (1ULL << 32)
#define FLAG_BIT36 (1ULL << 36)
#define FLAG_BIT43 (1ULL << 43)
#define FLAG2_BIT7 (1ULL << 7)
#define FLAG2_BIT36 (1ULL << 36)
#define FLAG2_BIT55 (1ULL << 55)
#define INPUT_BIT2 0x4
#define ACTION_RELEASE 1
#define ACTION_SUB 2
#define ACTION_REACT 3
#define ACTION_SLOT 4
#define ACTION_5 5
#define ACTION_6 6
#define HOOK_REACT 0x1a
#define SUB_KIND_BIT7 0x80
#define WINDOW_UNSET (-0x1000)
#define WINDOW_MAX 0x7fffffff
/* the combo record's window, or the largest value when it is unset */
static inline int ComboWindowOrMax(struct Actor *pActor)
{
    int nWindow = WINDOW_MAX;
    if (pActor->pComboLock->pRecord->nWindow != WINDOW_UNSET) {
        nWindow = pActor->pComboLock->pRecord->nWindow;
    }
    return nWindow;
}

extern int func_ov022_02093be0(u8 *pBlk);
extern int func_ov022_020b1b88(u8 *pAnimReq);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);
extern int func_02030788(void);
extern int func_ov022_0209038c(u8 *pCtx, unsigned int nSlot);
extern int func_ov022_02090978(u8 *pCtx, int nSlot);
extern int func_ov022_02094174(u8 *pBlk);
extern int func_0202aef8(u16 *pAnim, int nTrack);
extern int func_ov022_020ad1d0(struct Actor *pActor);

int func_ov022_020983ec(struct Actor *pActor, int nArg)
{
    int nResult;
    int bGo;
    int nLimit;

    nResult = 0;
    if (pActor->nPendingAction == ACTION_REACT && nArg == 0
        && ((pActor->nInputMask & INPUT_BIT2) != 0
            || ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0))) {
        if (func_ov022_02093be0(pActor->reactionBlk) != 0
            && func_ov022_020b1b88(pActor->animReq) != 0) {
            if ((pActor->nFlags & FLAG_BIT36) != 0 && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                nResult = func_ov022_020a35f4(pActor, 6);
            } else {
                nResult = func_ov022_020a35f4(pActor, 0);
            }
            pActor->pfnPreDraw(pActor, HOOK_REACT);
            goto done;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
    }
    if (pActor->nPendingAction == ACTION_SLOT && nArg == 0) {
        if (func_ov022_0209038c(pActor->reactionCtx, pActor->nLatchedArg) != 0
            && func_ov022_020b1b88(pActor->animReq) != 0) {
            if ((pActor->nInputMask & INPUT_BIT2) != 0) {
                nResult = func_ov022_020a35f4(pActor, 0);
            } else if ((pActor->nFlags & FLAG_BIT36) != 0
                       && (pActor->nFlags2 & FLAG2_BIT7) != 0) {
                nResult = func_ov022_020a35f4(pActor, 6);
            } else {
                nResult = func_ov022_020a35f4(pActor, 2);
            }
            pActor->pfnPreDraw(pActor,
                               func_ov022_02090978(pActor->reactionCtx, pActor->nLatchedArg));
            goto done;
        }
        if (func_02030788() == 0) {
            pActor->nFlags2 |= FLAG2_BIT55;
        }
    }
    if (pActor->nPendingAction == ACTION_RELEASE) {
        if ((pActor->nInputMask & INPUT_BIT2) == 0 && func_ov022_02094174(pActor->blkReach) != 0) {
            pActor->nFlags |= FLAG_BIT32;
        }
        if ((pActor->nFlags & FLAG_BIT32) == 0 && (pActor->nFlags2 & FLAG2_BIT36) == 0
            && (pActor->nInputMask & INPUT_BIT2) != 0) {
            nResult = func_ov022_020a35f4(pActor, 3);
        } else {
            if ((pActor->nInputMask & INPUT_BIT2) != 0) {
                nResult = func_ov022_020a35f4(pActor, 0xe);
            } else {
                nResult = func_ov022_020a35f4(pActor, 0xf);
            }
            if ((pActor->nFlags & FLAG_BIT32) != 0) {
                if (ComboWindowOrMax(pActor) != WINDOW_MAX) {
                    nLimit = ComboWindowOrMax(pActor);
                } else {
                    nLimit = func_0202aef8(&pActor->pNode->nAnimFlags, 0);
                }
                if (pActor->nInterruptCharge < nLimit) {
                    pActor->nInterruptCharge = nLimit;
                }
            }
        }
    } else if (pActor->nPendingAction == ACTION_SUB) {
        bGo = 0;
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            if ((pActor->nFlags & FLAG_BIT36) == 0 || (pActor->nFlags2 & FLAG2_BIT7) == 0) {
                bGo = 1;
            }
        } else if ((func_ov022_020ad1d0(pActor) & SUB_KIND_BIT7) != 0
                   && (pActor->nFlags & FLAG_BIT43) == 0) {
            bGo = 1;
        }
        if (bGo != 0) {
            nResult = func_ov022_020a35f4(pActor, 0x13);
        }
    } else if (pActor->nPendingAction == ACTION_5) {
        nResult = func_ov022_020a35f4(pActor, 0x18);
    } else if (pActor->nPendingAction == ACTION_6) {
        nResult = func_ov022_020a35f4(pActor, 0x19);
    }
done:
    return nResult;
}
