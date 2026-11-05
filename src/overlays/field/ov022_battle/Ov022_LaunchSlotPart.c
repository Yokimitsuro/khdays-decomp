/* Launches a part from an actor slot: rotates its offset by the actor's heading to place it, sets
 * its velocity and lifetime, binds its animations and plays its launch reaction. */

#include "nitro/types.h"

struct VecFx32 {
    int x;
    int y;
    int z;
};

struct MtxFx33 {
    int m[9];
};

struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                      /* 0x80 */
};

struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;         /* 0x020 */
    u8 pad024[0x42];
    short nField66;                  /* 0x066 */
    u8 pad068[0x424];
    struct VecFx32 vecAt;            /* 0x48c */
};

struct SlotPart {
    int nTimer;                      /* 0x000 */
    struct VecFx32 vecPos;           /* 0x004 */
    struct VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0x7a];
    u16 nAngle;                      /* 0x098 */
    u8 pad09a[0x26];
    struct VecFx32 vecAt;            /* 0x0c0 */
    int nLifeX;                      /* 0x0cc */
    int nLifeY;                      /* 0x0d0 */
    int nLifeZ;                      /* 0x0d4 */
    u8 pad0d8[0x4c];
    u16 anim[2];                     /* 0x124 */
    u8 pad128[0x24];
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
    u8 nSpare : 5;
    u8 pad14e[2];
};

struct ActorSlot {
    u8 pad00[1];
    u8 nPartCount;                   /* 0x001 */
    u8 nSeq;                         /* 0x002 */
    u8 pad03[1];
    u32 nBoundMask;                  /* 0x004 */
    u16 nFlags;                      /* 0x008 */
    u8 pad0a[0x7a];
    u16 nAngle;                      /* 0x084 */
    u8 pad86[0x26];
    struct VecFx32 vecAt;            /* 0x0ac */
    u8 pad0b8[0x58];
    u8 nGroup;                       /* 0x110 */
    u8 pad111[7];
    u8 nKind;                        /* 0x118 */
    u8 pad119[0xb];
    int nRate;                       /* 0x124 */
    u8 pad128[0x40];
    struct SlotPart *pParts;         /* 0x168 */
    int nLife;                       /* 0x16c */
    int nField170;                   /* 0x170 */
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[15];    /* 0x18 */
    void *pLevelAnim;                    /* 0x54: the cast's level animation (its grid entry) */
    struct Actor *pActor;            /* 0x58 */
};

#define PART_STRIDE 0x150
#define FLAG_ACTIVE 0x20
#define FRAME_RATE_20FPS 1   /* GetFrameRateMode(): 0 = 30 fps, 1 = 20 fps, 2 = 60 fps */
#define ANGLE_STEP 4
#define ANGLE_BIAS 0x8000

extern short data_0203d210[];

extern struct VecFx32 *func_ov022_0208a96c(struct ReactionCtx *pCtx);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pVec, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void Ov022_BindBlockAnimations(struct ReactionCtx *pCtx, void *pTarget,
                                u16 *pAnim, int nIndex);
extern void func_ov022_020b15a4(void *pLevelAnim, u16 *pAnim);
extern int Ov022_ClampReactionForKind10(int nKind, int nReaction);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAt,
                                int nReaction);
extern int GetFrameRateMode(void);
extern void ScaleVec3Fx12(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);

void Ov022_LaunchSlotPart(struct ReactionCtx *pCtx)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAt;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    u16 nAngle;
    int nIndex;
    short nSin;
    short nCos;
    struct SlotPart *pPart;
    int i;
    int nLife;
    int nRate;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nAngle = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS;
    vecAt = *func_ov022_0208a96c(pCtx);
    nIndex = (nAngle >> ANGLE_STEP) * 2;
    nCos = data_0203d210[nIndex + 1];
    nSin = data_0203d210[nIndex];
    MTX_RotY33_(&mtx, nSin, nCos);
    MTX_MultVec33(&vecAt, &mtx, &vecAt);
    VEC_Add(&vecAt, &pActor->vecAt, &vecAt);
    Ov022_BindBlockAnimations(pCtx, (u8 *)pCtx->pLevelAnim + 4, &pSlot->nFlags, 0);
    pPart = 0;
    pSlot->vecAt = vecAt;
    pSlot->nAngle = nAngle;
    i = 0;
    pSlot->nFlags = pSlot->nFlags | FLAG_ACTIVE;
    pSlot->nGroup = (u8)pActor->nField66;
    pSlot->nField170 = 1;
    pSlot->nSeq = pSlot->nSeq + 1;
    while (i < pSlot->nPartCount) {
        if (pSlot->pParts[i].nState == 0) {
            pPart = &pSlot->pParts[i];
            break;
        }
        i = i + 1;
    }
    if ((pSlot->nBoundMask & (1 << i)) == 0) {
        func_ov022_020b15a4(pCtx->pLevelAnim, pPart->anim);
        pSlot->nBoundMask = pSlot->nBoundMask | (1 << i);
    }
    Ov022_BindBlockAnimations(pCtx, pPart->anim, &pPart->nSlotFlags, 1);
    func_ov022_0208acdc(pCtx, &vecAt,
                        Ov022_ClampReactionForKind10(pSlot->nKind, 0));
    pPart->vecAt = vecAt;
    pPart->nAngle = nAngle;
    pPart->nSlotFlags = pPart->nSlotFlags | FLAG_ACTIVE;
    nLife = pSlot->nLife;
    pPart->nLifeZ = nLife;
    pPart->nLifeY = nLife;
    pPart->nLifeX = nLife;
    pPart->nGroup = (u8)pActor->nField66;
    pPart->vecPos = vecAt;
    pPart->nState = 1;
    pPart->nTimer = 0;
    pPart->vecVel.x = nSin;
    pPart->vecVel.y = 0;
    pPart->vecVel.z = nCos;
    if (GetFrameRateMode() == FRAME_RATE_20FPS) {
        nRate = pSlot->nRate * 3 / 2;
    } else {
        nRate = pSlot->nRate;
    }
    ScaleVec3Fx12(nRate, &pPart->vecVel, &pPart->vecVel);
}
