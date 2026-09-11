/* ov022: drive the context's slot forward by a frame, spawning hits on the beat.
 *
 * The slot's own state picks what runs: 0 reports it finished, 4 waits for the
 * next input or the hold to expire, and 2 does the work.
 *
 * In state 2 the timer is measured against the slot's interval in whole units.
 * Only on an exact beat does anything happen, and which of two hits it is
 * depends on how far the timer has run: past the threshold the slot fires the
 * late hit, and only if its flag word allows it; before the threshold it fires
 * the early one and then resets the shorts. Each hit is a request and a query
 * built on the stack and handed to the same asker, and a query that comes back
 * accepted is notified.
 *
 * The late hit's answer replaces the beat test for the early one, so the two
 * can never both fire in a frame.
 *
 * Register layout (nDelta r4, pCtx r5, pSlot r6, bDone r7, pActor r8, nBusy
 * sb, nTimer sl) comes from the declaration order pSlot, bDone, pActor,
 * nBusy, nTimer TOGETHER with the fill order of the two parameter blocks
 * (nField20 before nField08, nPhase before the vector): either alone leaves
 * the allocator in a different regime. The beat test calls the divide helper
 * explicitly and reads the remainder from r1, as the rest of the tree does.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define BEAT_THRESHOLD 0x23000
#define WAIT_HOLD 0x3000
#define HIT_KIND 0xb

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* what the asker is told about where the hit lands */
struct Ov022ActionQuery {
    struct VecFx32 vecPos;       /* 0x00 */
    int nRadius;                 /* 0x0c */
    unsigned int nGroup;         /* 0x10 */
    struct VecFx32 vecDir;       /* 0x14 */
    int nConeLimit;              /* 0x20 */
    short *pHitIds;              /* 0x24 */
    int nField28;                /* 0x28 */
};

/* what it is asked about the hit itself */
struct Ov022ActionParams {
    int nValue;                  /* 0x00 */
    int nField04;                /* 0x04 */
    int nField08;                /* 0x08 */
    int nField0c;                /* 0x0c */
    u8 nLevel;                   /* 0x10 */
    u8 pad11[3];
    struct VecFx32 vecField14;   /* 0x14 */
    int nField20;                /* 0x20 */
    u8 nPhase;                   /* 0x24 */
    u8 bFlagA : 1;               /* 0x25 */
    u8 bFlagB : 1;
    u8 nRest25 : 6;
    u8 pad26[2];
};

/* Ov022ActorSlot */
struct Ov022ActorSlot {
    u8 pad000[2];
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0xa2];
    struct VecFx32 vecAim;       /* 0x0ac */
    u8 pad0b8[0x58];
    signed char nSlotIndex;      /* 0x110 */
    u8 pad111[7];
    u8 nState;                   /* 0x118 */
    u8 pad119[3];
    int nTimer;                  /* 0x11c */
    u8 pad120[0xc];
    int nInterval;               /* 0x12c */
    int nField130;               /* 0x130 */
    int nField134;               /* 0x134 */
    int nField138;               /* 0x138 */
    int nField13c;               /* 0x13c */
    u8 pad140[0x18];
    u32 nFlags158;               /* 0x158 */
};

struct Ov022Actor;

/* Ov022ReactionCtx */
struct Ov022ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[0x34];
    struct Ov022ActorSlot *pSlot;     /* 0x44 */
    u8 pad48[0x10];
    struct Ov022Actor *pActor;        /* 0x58 */
    short aHitIds[8];            /* 0x5c */
};

extern const struct VecFx32 data_02041dc8;

/* ABI view of the div/mod helper: quotient in r0, remainder in r1.
 * The 64-bit declaration lets the caller access r1 without inline assembly. */
extern long long func_02020400(int a, int b);
extern int func_ov022_020a216c(struct Ov022Actor *pActor, int nValue,
                               int nActionLevel);
extern int func_ov022_0208ac10(struct Ov022ReactionCtx *pCtx, struct Ov022ActionQuery *pReq,
                               struct Ov022ActionParams *pQry);
extern int func_ov022_0208acc4(int nKind, int nMode);
extern void func_ov022_0208acdc(struct Ov022ReactionCtx *pCtx, struct Ov022ActionQuery *pReq,
                                int nReaction);
extern void func_ov022_0208a6b0(struct Ov022ReactionCtx *pCtx);
extern int func_0202a818(u16 *pFlags, int nDelta);
extern int func_02030694(void);
int func_ov022_0208ded4(struct Ov022ReactionCtx *pCtx, int nDelta)
{
    struct Ov022ActionQuery reqLate;
    struct Ov022ActionParams qryLate;
    struct Ov022ActionQuery reqEarly;
    struct Ov022ActionParams qryEarly;
    struct Ov022ActorSlot *pSlot;
    int bDone;
    struct Ov022Actor *pActor;
    int nBusy;
    int nTimer;

    pSlot = pCtx->pSlot;
    pActor = pCtx->pActor;
    pSlot->nTimer = pSlot->nTimer + nDelta;
    bDone = 0;
    switch (pSlot->nState) {
    case 0:
        bDone = 1;
        break;
    case 2:
        nTimer = pSlot->nTimer;
        nBusy = 0;
        if ((int)(func_02020400(nTimer >> 12, pSlot->nInterval >> 12) >> 32) != 0) {
            nBusy = 1;
        }
        if (nBusy == 0 && nTimer >= BEAT_THRESHOLD
            && (pSlot->nFlags158 & 1) != 0) {
            reqLate.vecPos = pSlot->vecAim;
            reqLate.vecDir = data_02041dc8;
            reqLate.nGroup = pSlot->nSlotIndex;
            reqLate.nRadius = pSlot->nField130;
            reqLate.nConeLimit = 0x1000;
            reqLate.pHitIds = pCtx->aHitIds;
            reqLate.nField28 = 0;
            qryLate.nValue = func_ov022_020a216c(
                pActor, pSlot->nField138, (qryLate.nField0c = 2));
            qryLate.nField20 = 0;
            qryLate.nField08 = 8;
            qryLate.bFlagA = 0;
            qryLate.bFlagB = 0;
            qryLate.nLevel = (u8)(pSlot->nField13c >> 12);
            qryLate.nField04 = 0;
            qryLate.nPhase = (u8)(pCtx->nSlot % 3);
            qryLate.vecField14.x = 0;
            qryLate.vecField14.y = WAIT_HOLD;
            qryLate.vecField14.z = 0;
            nBusy = func_ov022_0208ac10(pCtx, &reqLate, &qryLate);
            if (nBusy == 1) {
                func_ov022_0208acdc(pCtx, &reqLate,
                                    func_ov022_0208acc4(HIT_KIND, 1));
            }
        }
        if (nBusy == 0 && pSlot->nTimer < BEAT_THRESHOLD) {
            reqEarly.vecPos = pSlot->vecAim;
            reqEarly.vecDir = data_02041dc8;
            reqEarly.nGroup = pSlot->nSlotIndex;
            reqEarly.nRadius = pSlot->nField130;
            reqEarly.nConeLimit = 0x1000;
            reqEarly.pHitIds = pCtx->aHitIds;
            reqEarly.nField28 = 0;
            qryEarly.nValue = func_ov022_020a216c(
                pActor, pSlot->nField134, (qryEarly.nField0c = 2));
            qryEarly.nField08 = 8;
            qryEarly.nField0c = 2;
            qryEarly.nField20 = 1;
            qryEarly.bFlagA = 0;
            qryEarly.bFlagB = 0;
            qryEarly.nLevel = 0;
            qryEarly.nField04 = 0;
            qryEarly.nPhase = (u8)(pCtx->nSlot % 3);
            qryEarly.vecField14.x = 0x600;
            qryEarly.vecField14.y = 0;
            qryEarly.vecField14.z = -0x400;
            if (func_ov022_0208ac10(pCtx, &reqEarly, &qryEarly) == 1) {
                func_ov022_0208acdc(pCtx, &reqEarly,
                                    func_ov022_0208acc4(HIT_KIND, 1));
            }
            func_ov022_0208a6b0(pCtx);
        }
        if (func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
            pSlot->nTimer = 0;
            pSlot->nSlotIndex = -1;
            pSlot->nState = 4;
        }
        break;
    case 4:
        if (func_02030694() != 0) {
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
