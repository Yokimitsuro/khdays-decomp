typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

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
    u8 bLive;                        /* 0x14e */
    u8 pad14f[1];
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
    u8 pad119[3];
    int nHalfBound;                  /* 0x11c */
    u8 pad120[4];
    int nRate;                       /* 0x124 */
    u8 pad128[0x38];
    int bTracked;                   /* 0x160 */
    u8 pad164[4];
    struct SlotPart *pParts;         /* 0x168 */
    int nLife;                       /* 0x16c */
    int nField170;                   /* 0x170 */
};

struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[15];    /* 0x18 */
    void *pOwner;                    /* 0x54 */
    struct Actor *pActor;            /* 0x58 */
};

#define PART_STRIDE 0x150
#define FLAG_ACTIVE 0x20
#define MODE_HARD 1
#define ANGLE_STEP 4
#define ANGLE_BIAS 0x8000
#define HALF_ONE 0x800
#define FX32_SHIFT 12

extern short data_0203d210[];

extern struct VecFx32 *func_ov022_0208a96c(struct ReactionCtx *pCtx);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pVec, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, void *pTarget,
                                u16 *pAnim, int nIndex);
extern void WM_EndKeySharing_0x020b15a4(void *pOwner, u16 *pAnim);
extern int func_ov022_0208acc4(int nKind, int nReaction);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAt,
                                int nReaction);
extern int func_02023c40(void);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);

void func_ov022_0208cfbc(struct ReactionCtx *pCtx)
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
    pSlot->nGroup = (u8)pActor->nField66;
    pSlot->nSeq = pSlot->nSeq + 1;
    vecAt = *func_ov022_0208a96c(pCtx);
    nIndex = (nAngle >> ANGLE_STEP) * 2;
    nCos = data_0203d210[nIndex + 1];
    nSin = data_0203d210[nIndex];
    MTX_RotY33_(&mtx, nSin, nCos);
    MTX_MultVec33(&vecAt, &mtx, &vecAt);
    VEC_Add(&vecAt, &pActor->vecAt, &vecAt);
    func_ov022_0208a8bc(pCtx, (u8 *)pCtx->pOwner + 4, &pSlot->nFlags, 0);
    pPart = 0;
    pSlot->vecAt = vecAt;
    pSlot->nAngle = nAngle;
    i = 0;
    pSlot->nFlags = pSlot->nFlags | FLAG_ACTIVE;
    pSlot->nField170 = 1;
    while (i < pSlot->nPartCount) {
        if (pSlot->pParts[i].nState == 0) {
            pPart = &pSlot->pParts[i];
            break;
        }
        i = i + 1;
    }
    if ((pSlot->nBoundMask & (1 << i)) == 0) {
        WM_EndKeySharing_0x020b15a4(pCtx->pOwner, pPart->anim);
        pSlot->nBoundMask = pSlot->nBoundMask | (1 << i);
    }
    func_ov022_0208a8bc(pCtx, pPart->anim, &pPart->nSlotFlags, 1);
    func_ov022_0208acdc(pCtx, &vecAt,
                        func_ov022_0208acc4(pSlot->nKind, 0));
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
    pPart->bLive = 1;
    pSlot->bTracked = 1;
    pSlot->nHalfBound =
        (int)(((long long)pSlot->nLife * HALF_ONE + HALF_ONE)
              >> FX32_SHIFT);
    pPart->vecVel.x = nSin;
    pPart->vecVel.y = 0;
    pPart->vecVel.z = nCos;
    if (func_02023c40() == MODE_HARD) {
        nRate = pSlot->nRate * 3 / 2;
    } else {
        nRate = pSlot->nRate;
    }
    func_01ffa724(nRate, &pPart->vecVel, &pPart->vecVel);
}
