/* Ov022_ArmSlotAtActor -- arm a reaction slot on the actor itself.
 *
 * The state's own offset vector is turned by the actor's facing, sampled from
 * the shared sine table at the facing's top bits, and added to where the actor
 * is; that point goes through the notifier and becomes the slot's aim. The slot
 * takes the actor's slot index, a fresh sequence number and the facing, and its
 * arming state is stamped. If the actor is aiming at something the heading is
 * recomputed towards it, and an anchor is placed a fixed distance behind the
 * aim along that heading, raised by the same amount. Every part the slot owns
 * then has its key released once and its animations bound.
 */

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

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                      /* 0x80 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;         /* 0x020 */
    u8 pad024[0x42];
    short nSlotIndex;                /* 0x066 */
    u8 pad068[0x424];
    struct VecFx32 vecAim;           /* 0x48c */
};

/* Ov022SlotPart */
struct SlotPart {
    u8 pad000[0x1c];
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0x106];
    u16 binding[2];                  /* 0x124 */
    u8 pad128[0x25];
    u8 nSlotIndex : 3;               /* 0x14d */
    u8 nSpare : 5;
    u8 pad14e[2];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                        /* 0x000 */
    u8 nParts;                       /* 0x001 */
    u8 nSeq;                         /* 0x002 */
    u8 pad003[1];
    u32 nBoundMask;                  /* 0x004 */
    u16 nSlotFlags;                  /* 0x008 */
    u8 pad00a[0x7a];
    u16 nAngle;                      /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[0x57];
    struct SlotPart *pParts;         /* 0x168 */
    u8 pad16c[4];
    /* The four fields an arming entry stamps together. */
    struct SlotStamp {
        int bSeqPending;             /* 0x170 */
        u8 nTurns;                   /* 0x174 */
        u8 nArmed;                   /* 0x175 */
        u8 pad176[2];
        int nMarkNext;               /* 0x178 */
    } stamp;
    u8 pad17c[0x10];
    u16 nBackAngle;                  /* 0x18c */
    u8 pad18e[2];
    struct VecFx32 vecBack;          /* 0x190 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];    /* 0x18 */
    u8 pad44[0x10];
    int nTrack;                      /* 0x54 */
    struct Actor *pActor;            /* 0x58 */
};

/* Two signed halfwords per angle step: the sine first, then the cosine. */
extern short data_0203d210[];

extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, int nTrack,
                                u16 *pFlags, int nArg3);
extern struct VecFx32 *func_ov022_0208a96c(struct ReactionCtx *pCtx);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pIn, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *pA, struct VecFx32 *pB,
                    struct VecFx32 *pOut);
extern int func_ov022_0208acc4(int nKind, int nArg1);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAt,
                                int nReaction);
extern int func_ov022_020ad114(struct Actor *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Subtract(struct VecFx32 *pA, struct VecFx32 *pB,
                         struct VecFx32 *pOut);
extern int FX_Atan2(int x, int z);
extern void VEC_MultAdd(int nScale, struct VecFx32 *pVec,
                        struct VecFx32 *pAdd, struct VecFx32 *pDst);
extern void WM_EndKeySharing_0x020b15a4(int nTrack, u16 *pBinding);

#define HALF_TURN 0x8000
#define SLOT_FLAG_ARMED 0x20
#define SLOT_ARMED 1
#define SLOT_TURNS 2
#define BACK_REACH 0x800

void func_ov022_0208e404(struct ReactionCtx *pCtx)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAim;
    struct VecFx32 vecDir;
    struct VecFx32 vecToTarget;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    struct SlotPart *pPart;
    struct VecFx32 *pOffset;
    struct SlotStamp *pStamp;
    int nReaction;
    int nIndex;
    int i;
    u16 nBack;
    u16 nFacing;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nBack = pActor->pNode->nAngle - HALF_TURN;
    pSlot->nSlotIndex = (s8)pActor->nSlotIndex;
    nFacing = nBack + HALF_TURN;
    pSlot->nSeq = pSlot->nSeq + 1;
    pOffset = func_ov022_0208a96c(pCtx);
    nIndex = nFacing >> 4;
    vecAim = *pOffset;
    MTX_RotY33_(&mtx, data_0203d210[nIndex * 2], data_0203d210[nIndex * 2 + 1]);
    MTX_MultVec33(&vecAim, &mtx, &vecAim);
    VEC_Add(&vecAim, &pActor->vecAim, &vecAim);
    func_ov022_0208a8bc(pCtx, pCtx->nTrack + 4, &pSlot->nSlotFlags, 0);
    nReaction = func_ov022_0208acc4(pSlot->nKind, 0);
    func_ov022_0208acdc(pCtx, &vecAim, nReaction);
    pSlot->vecAim = vecAim;
    pSlot->nAngle = nFacing;
    pSlot->nSlotFlags |= SLOT_FLAG_ARMED;
    pStamp = &pSlot->stamp;
    pStamp->bSeqPending = SLOT_ARMED;
    pStamp->nTurns = SLOT_TURNS;
    pStamp->nArmed = 0;
    pStamp->nMarkNext = 0;
    if (func_ov022_020ad114(pActor) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(pActor), &pActor->vecAim,
                     &vecToTarget);
        nFacing = FX_Atan2(vecToTarget.x, vecToTarget.z);
    }
    nIndex = nFacing >> 4;
    vecAim = pActor->vecAim;
    vecDir.x = data_0203d210[nIndex * 2];
    vecDir.y = 0;
    vecDir.z = data_0203d210[nIndex * 2 + 1];
    VEC_MultAdd(-BACK_REACH, &vecDir, &vecAim, &vecAim);
    pSlot->vecBack = vecAim;
    pSlot->nBackAngle = nFacing;
    pSlot->vecBack.y = pSlot->vecBack.y + BACK_REACH;
    i = 0;
    while (i < pSlot->nParts) {
        pPart = &pSlot->pParts[i];
        if ((pSlot->nBoundMask & (1 << i)) == 0) {
            WM_EndKeySharing_0x020b15a4(pCtx->nTrack, pPart->binding);
            pSlot->nBoundMask = pSlot->nBoundMask | (1 << i);
        }
        pPart->nSlotIndex = (u8)pActor->nSlotIndex;
        func_ov022_0208a8bc(pCtx, (int)pPart->binding, &pPart->nSlotFlags, 1);
        i = i + 1;
    }
}
