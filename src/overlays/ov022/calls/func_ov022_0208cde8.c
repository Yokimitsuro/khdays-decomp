/* Ov022_StepSlotState3 -- the slot's step while it is half bound.
 *
 * While the slot's half-bound mark is still set, it asks the shared action
 * query whether its aim point lands, with no direction at all: the point is
 * the slot's aim, the direction is zero, the group is the slot's own index and
 * the reach is whatever power is pending. The parameters carry the actor's
 * value for the slot's initial power, a fixed kind and level, and the phase
 * derived from the slot number.
 *
 * Either way the slot's tracks are advanced by the frame delta, and when they
 * report done the half-bound mark is cleared and the slot moves to state four.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022ActorSlot */
struct Ov022ActorSlot {
    u8 pad000[8];
    u16 nSlotFlags;                  /* 0x008 */
    u8 pad00a[0xa2];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[7];
    u8 nState;                       /* 0x118 */
    u8 pad119[3];
    int nHalfBound;                  /* 0x11c */
    u8 pad120[8];
    int bPowerPending;               /* 0x128 */
    u8 pad12c[4];
    int nPowerInit;                  /* 0x130 */
    u8 pad134[8];
    u8 nRepeatMax;                   /* 0x13c */
};

/* Ov022ReactionCtx */
struct Ov022ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct Ov022ActorSlot *aSlots[11];    /* 0x18 */
    u8 pad44[0x14];
    void *pActor;                    /* 0x58 */
    short aHitIds[8];                /* 0x5c */
};

/* Ov022ActionQuery */
struct Ov022ActionQuery {
    struct VecFx32 vecPos;           /* 0x00 */
    int nRadius;                     /* 0x0c */
    int nGroup;                      /* 0x10 */
    struct VecFx32 vecDir;           /* 0x14 */
    int nConeLimit;                  /* 0x20 */
    short *pHitIds;                  /* 0x24 */
    int nField28;                    /* 0x28 */
};

/* Ov022ActionParams */
struct Ov022ActionParams {
    int nValue;                      /* 0x00 */
    int nField04;                    /* 0x04 */
    int nField08;                    /* 0x08 */
    int nField0c;                    /* 0x0c */
    u8 nLevel;                       /* 0x10 */
    u8 pad11[3];
    struct VecFx32 vecField14;       /* 0x14 */
    int nField20;                    /* 0x20 */
    u8 nPhase;                       /* 0x24 */
    u8 bFlagA : 1;                   /* 0x25 */
    u8 bFlagB : 1;
    u8 nRest : 6;
    u8 pad26[2];
};

#define HALF_BOUND 0x9000
#define CONE_FULL 0x1000
#define PHASE_COUNT 3
#define ACTION_KIND 8
#define ACTION_LEVEL 3
#define FIELD14_SPAN 0x100
#define SLOT_STATE_DONE 4

extern int func_ov022_020a216c(void *pActor, int nField, int nActionLevel);
extern void func_ov022_0208ac10(struct Ov022ReactionCtx *pCtx,
                                struct Ov022ActionQuery *pQuery,
                                struct Ov022ActionParams *pParams);
extern int func_0202a818(u16 *pTracks, int nDelta);

int func_ov022_0208cde8(struct Ov022ReactionCtx *pCtx, int nDelta)
{
    struct Ov022ActionQuery query;
    struct Ov022ActionParams params;
    struct Ov022ActorSlot *pSlot;
    void *pActor;
    int nSlot;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pActor = pCtx->pActor;
    if (pSlot->nHalfBound == HALF_BOUND) {
        query.vecPos = pSlot->vecAim;
        query.vecDir.z = 0;
        query.vecDir.y = 0;
        query.vecDir.x = 0;
        query.nGroup = pSlot->nSlotIndex;
        query.nRadius = pSlot->bPowerPending;
        query.nField28 = 0;
        query.nConeLimit = CONE_FULL;
        query.pHitIds = pCtx->aHitIds;
        params.nValue = func_ov022_020a216c(
            pActor, pSlot->nPowerInit,
            (params.nField0c = ACTION_LEVEL));
        params.nField08 = ACTION_KIND;
        params.vecField14.x = FIELD14_SPAN;
        params.vecField14.z = FIELD14_SPAN;
        params.vecField14.y = 0;
        params.bFlagA = 0;
        params.bFlagB = 0;
        params.nField20 = 0;
        params.nLevel = (u8)pSlot->nRepeatMax;
        params.nField04 = 0;
        nSlot = pCtx->nSlot;
        params.nPhase = (u8)(nSlot % PHASE_COUNT);
        func_ov022_0208ac10(pCtx, &query, &params);
    }
    if (func_0202a818(&pSlot->nSlotFlags, nDelta) != 0) {
        pSlot->nHalfBound = 0;
        pSlot->nState = SLOT_STATE_DONE;
    }
    return 0;
}
