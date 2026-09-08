typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct Actor;

struct ActorSlot {
    u8 pad000[0x114];
    u16 nOpen;                       /* 0x114 */
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[16];   /* 0x18 */
    void *pActor;                    /* 0x58 */
};

struct SlotTail {
    u8 nState;                       /* 0x00 */
    u8 pad01[1];
    short nTag;                      /* 0x02 */
    u8 pad04[8];
    int nRate;                       /* 0x0c */
    short nField10;                  /* 0x10 */
    u8 pad12[2];
    int nReach;                      /* 0x14 */
    int nWindow;                     /* 0x18 */
    u8 pad1c[0xc];
    int nMark;                       /* 0x28 */
};

struct SlotPart {
    int nTimer;                      /* 0x000 */
    struct VecFx32 vecPos;           /* 0x004 */
    struct VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0xa2];
    struct VecFx32 vecAt;            /* 0x0c0 */
    u8 pad0cc[0x7c];
    struct SlotTail *pOwner;         /* 0x148 */
    u8 nState;                       /* 0x14c */
};

#define SLOT_OPEN 0xffff
#define DOT_LIMIT 0xa00
#define FX32_ONE 0x1000
#define MODE_HARD 1
#define STATE_LIVE 2
#define REACTION_KIND 2

extern int func_ov022_020ad114(void *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(void *pActor);
extern void VEC_Subtract(struct VecFx32 *a, struct VecFx32 *b,
                         struct VecFx32 *pOut);
extern int VEC_DotProduct(struct VecFx32 *a, struct VecFx32 *b);
extern int func_01ff8d18(struct VecFx32 *pSrc, struct VecFx32 *pDst);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
extern void VEC_MultAdd(int nScale, struct VecFx32 *pVec,
                        struct VecFx32 *pAdd, struct VecFx32 *pDst);
extern int func_02023c40(void);
extern int func_ov022_0208a9ac(int nSpeed, int nDecay, int nTimer);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void func_ov022_0208b400(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart,
                                struct VecFx32 *pAt, struct VecFx32 *pDir);
extern int func_01ff8e94(struct VecFx32 *a, struct VecFx32 *b);
extern int func_ov022_0208acc4(int nKind, int nReaction);
extern void func_ov022_0208a50c(struct ReactionCtx *pCtx,
                                struct SlotPart *pPart, int nReaction);
extern int func_0202a818(u16 *pFlags, int nDelta);

int func_ov022_0208ae90(struct ReactionCtx *pCtx, struct SlotPart *pPart,
                        int nDelta)
{
    struct VecFx32 vecAt;
    struct VecFx32 vecToTarget;
    struct VecFx32 vecStep;
    void *pActor;
    struct SlotTail *pOwner;
    int nSpeed;

    pActor = pCtx->pActor;
    pOwner = pPart->pOwner;
    if (pCtx->aSlots[pCtx->nSlot]->nOpen == SLOT_OPEN) {
        pPart->nTimer = pPart->nTimer + nDelta;
        vecAt = pPart->vecAt;
        if (func_ov022_020ad114(pActor) != 0
            && pPart->nTimer >= pOwner->nMark) {
            VEC_Subtract(func_ov022_020ad0c0(pActor), &vecAt, &vecToTarget);
            if (VEC_DotProduct(&vecToTarget, &pPart->vecVel) >= -DOT_LIMIT) {
                func_01ff8d18(&vecToTarget, &vecToTarget);
                func_01ff8d18(&pPart->vecVel, &pPart->vecVel);
                func_01ffa724(pOwner->nTag, &vecToTarget, &vecToTarget);
                VEC_MultAdd(FX32_ONE - pOwner->nTag, &pPart->vecVel,
                            &vecToTarget, &pPart->vecVel);
                func_01ff8d18(&pPart->vecVel, &pPart->vecVel);
                if (func_02023c40() == MODE_HARD) {
                    nSpeed = pOwner->nRate * 3 / 2;
                } else {
                    nSpeed = pOwner->nRate;
                }
                func_01ffa724(nSpeed, &pPart->vecVel, &pPart->vecVel);
            }
        }
        vecStep = pPart->vecVel;
        if (pOwner->nField10 != 0) {
            func_01ffa724(func_ov022_0208a9ac(pOwner->nRate, pOwner->nField10,
                                              pPart->nTimer),
                          &pPart->vecVel, &vecStep);
        }
        VEC_Add(&vecAt, &vecStep, &vecAt);
        pPart->vecAt = vecAt;
        func_ov022_0208b400(pCtx, pPart, &vecAt, &pPart->vecVel);
        if (pPart->nState == STATE_LIVE
            && (func_01ff8e94(&pPart->vecPos, &vecAt) > pOwner->nReach
                || pPart->nTimer >= pOwner->nWindow)) {
            func_ov022_0208a50c(pCtx, pPart,
                                func_ov022_0208acc4(pOwner->nState,
                                                    REACTION_KIND));
        }
    }
    func_0202a818(&pPart->nSlotFlags, nDelta);
    return 0;
}
