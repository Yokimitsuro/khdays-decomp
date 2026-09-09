typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* The shot block of a slot, which the ROM addresses through its own base. */
struct SlotShot {
    u8 nState;                       /* 0x00 */
    u8 pad01[3];
    int nHalfBound;                  /* 0x04 */
    int nPower;                      /* 0x08 */
    int nRadius;                     /* 0x0c */
    short nPowerPending;             /* 0x10 */
    u8 pad12[6];
    int nPowerInit;                  /* 0x18 */
    int nField1c;                    /* 0x1c */
    int nRepeat;                     /* 0x20 */
    u8 pad24[4];
    int nField28;                    /* 0x28 */
    u8 pad2c[0x1c];
    int bTracked;                    /* 0x48 */
};

struct ActorSlot {
    u8 pad000[0x111];
    u8 nWeight;                      /* 0x111 */
    u8 pad112[2];
    u16 nOpen;                       /* 0x114 */
    u8 pad116[2];
    struct SlotShot shot;            /* 0x118 */
};

struct SlotPart {
    int nTimer;                      /* 0x000 */
    u8 pad004[0xc];
    struct VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0xa2];
    struct VecFx32 vecAt;            /* 0x0c0 */
    int aBound[3];                   /* 0x0cc */
    u8 pad0d8[0x4c];
    u16 binding[2];                  /* 0x124 */
    u8 pad128[0x24];
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
    u8 nSpare : 5;
    u8 bLive;                        /* 0x14e */
    u8 pad14f[1];
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[15];    /* 0x18 */
    void *pOwner;                    /* 0x54 */
    void *pActor;                    /* 0x58 */
};

/* The block the mover fills before asking the world where it stops. */
struct MoveProbe {
    struct VecFx32 vecPos;           /* 0x00 */
    struct VecFx32 vecDir;           /* 0x0c */
    int nRadius;                     /* 0x18 */
    int nDrop;                       /* 0x1c */
    int nSlotIndex;                  /* 0x20 */
    struct VecFx32 vecHit;           /* 0x24 */
};

#define SLOT_OPEN 0xffff
#define MARGIN_LIMIT 0x59a
#define HIT_RISE 0x200
#define MODE_HARD 1
#define STATE_LIVE 2
#define REACTION_KIND 2
#define WEIGHT_LIGHT 3
#define CAST_STOPPED 1
#define CAST_LANDED 2
#define CAST_BLOCKED 3
#define BIND_LANDED 3

extern int func_ov022_0208a9ac(int nRadius, int nPending, int nTimer);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
extern int func_02023c40(void);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern int func_ov022_0208acc4(int nState, int nReaction);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int func_ov022_0208aa28(struct ReactionCtx *pCtx,
                               struct MoveProbe *pProbe);
extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, u16 *pBinding,
                                u16 *pFlags, int nIndex);
extern int func_0202a818(u16 *pFlags, int nDelta);

int func_ov022_0208d310(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecStep;
    struct MoveProbe probe;
    struct ActorSlot *pSlot;
    struct SlotShot *pShot;
    int nRise;
    int nScale;
    int nGravity;
    int nBound;
    int bEnded;
    int nResult;

    pSlot = pCtx->aSlots[pCtx->nSlot];
    pShot = &pSlot->shot;
    nRise = pShot->nPower + HIT_RISE;
    if (pSlot->nOpen == SLOT_OPEN) {
        pShot->bTracked = 0;
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->vecAt;
        vecStep = pPart->vecVel;
        if (pPart->nTimer >= pShot->nField28 && pPart->bLive != 0) {
            nScale = func_ov022_0208a9ac(pShot->nRadius, pShot->nPowerPending,
                                         pPart->nTimer);
            func_01ffa724(nScale, &pPart->vecVel, &vecStep);
            if (nScale <= MARGIN_LIMIT) {
                if (pSlot->nWeight <= WEIGHT_LIGHT) {
                    if (func_02023c40() == MODE_HARD) {
                        nGravity = 0x180;
                    } else {
                        nGravity = 0x100;
                    }
                    vecStep.y = vecStep.y - nGravity;
                } else {
                    if (func_02023c40() == MODE_HARD) {
                        nGravity = 0x300;
                    } else {
                        nGravity = 0x200;
                    }
                    vecStep.y = vecStep.y - nGravity;
                }
            }
        }
        VEC_Add(&vecAt, &vecStep, &vecAt);
        pPart->vecAt = vecAt;
        func_ov022_0208b400(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == STATE_LIVE
            && pPart->nTimer >= pShot->nPowerInit) {
            func_ov022_0208a50c(pCtx, pPart,
                                func_ov022_0208acc4(pShot->nState,
                                                    REACTION_KIND));
        }
        if (pPart->bLive != 0 && pPart->nState == STATE_LIVE) {
            probe.vecPos = vecAt;
            probe.vecDir = pPart->vecVel;
            probe.vecDir.y = vecStep.y;
            probe.nRadius = pShot->nHalfBound;
            probe.nDrop = pShot->nPower;
            bEnded = 0;
            probe.nSlotIndex = pPart->nGroup;
            nResult = func_ov022_0208aa28(pCtx, &probe);
            switch (nResult) {
            case CAST_STOPPED:
                pPart->vecVel.z = 0;
                pPart->vecVel.y = 0;
                pPart->vecVel.x = 0;
                func_ov022_0208a8bc(pCtx, pPart->binding, &pPart->nSlotFlags,
                                    BIND_LANDED);
                nBound = pShot->nRepeat;
                pPart->aBound[2] = nBound;
                pPart->aBound[1] = nBound;
                pPart->aBound[0] = nBound;
                pShot->nHalfBound = pShot->nField1c;
                pPart->bLive = 0;
                break;
            case CAST_LANDED:
                vecAt = probe.vecHit;
                vecAt.y = vecAt.y + nRise;
                pPart->vecAt = vecAt;
                func_ov022_0208a8bc(pCtx, pPart->binding, &pPart->nSlotFlags,
                                    BIND_LANDED);
                nBound = pShot->nRepeat;
                pPart->aBound[2] = nBound;
                pPart->aBound[1] = nBound;
                pPart->aBound[0] = nBound;
                pShot->nHalfBound = pShot->nField1c;
                pPart->bLive = 0;
                pPart->vecVel.z = 0;
                pPart->vecVel.y = 0;
                pPart->vecVel.x = 0;
                break;
            case CAST_BLOCKED:
                bEnded = 1;
                break;
            }
            if (bEnded != 0) {
                func_ov022_0208a50c(pCtx, pPart,
                                    func_ov022_0208acc4(pShot->nState,
                                                        REACTION_KIND));
            }
        }
    }
    func_0202a818(&pPart->nSlotFlags, nDelta);
    return 0;
}
