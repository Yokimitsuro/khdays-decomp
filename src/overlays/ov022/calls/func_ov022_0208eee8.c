/* Ov022_EnterChainReaction -- open a chained reaction slot on the actor.
 *
 * The slot takes the actor's slot index and a fresh sequence number. Its aim
 * point is the shared aim offset turned by the actor's node angle and added to
 * the actor's aim, which is bound on the owner's track and announced through
 * the notifier before it is stored with the angle; the slot then starts with
 * its sequence pending, two turns, nothing armed and no next mark.
 *
 * The chain's back angle is the node angle unless the actor still has a valid
 * target, in which case it faces the target; the back point is the actor's aim
 * advanced by nAdvance along that angle. Finally every part is bound on the
 * owner's track once (the bound mask remembers which already are), takes the
 * actor's slot index as its group, is bound to the shared sequence and is
 * marked not live.
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
    int m[3][3];
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad000[0x80];
    u16 nAngle;                      /* 0x080 */
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
    u8 nGroup : 3;                   /* 0x14d */
    u8 nSpare : 5;
    u8 bLive;                        /* 0x14e */
    u8 pad14f[1];
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                        /* 0x000 */
    u8 nParts;                       /* 0x001 */
    u8 nSeq;                         /* 0x002 */
    u8 pad003[1];
    u32 nBoundMask;                  /* 0x004 */
    u16 nFlags;                      /* 0x008 */
    u8 pad00a[0x7a];
    u16 nAngle;                      /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[0x57];
    struct SlotPart *pParts;         /* 0x168 */
    u8 pad16c[4];
    int bSeqPending;                 /* 0x170 */
    s8 nTurns;                       /* 0x174 */
    u8 nArmed;                       /* 0x175 */
    u8 pad176[2];
    int nMarkNext;                   /* 0x178 */
    u8 pad17c[4];
    int nAdvance;                    /* 0x180 */
    u8 pad184[8];
    u16 nBackAngle;                  /* 0x18c */
    u8 pad18e[2];
    struct VecFx32 vecBack;          /* 0x190 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                       /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[15];    /* 0x18 */
    void *pOwner;                    /* 0x54 */
    struct Actor *pActor;            /* 0x58 */
};

#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define FLAG_ACTIVE 0x20
#define TURNS_START 2

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern struct VecFx32 *func_ov022_0208a96c(struct ReactionCtx *pCtx);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pVec, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void VEC_Subtract(struct VecFx32 *a, struct VecFx32 *b,
                         struct VecFx32 *pOut);
extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, void *pTarget,
                                u16 *pFlags, int nIndex);
extern int func_ov022_0208acc4(int nKind, int nReaction);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAim,
                                int nReaction);
extern int func_ov022_020ad114(struct Actor *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern int FX_Atan2(int x, int z);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
extern void WM_EndKeySharing_0x020b15a4(void *pOwner, u16 *pBinding);

typedef char Ov022ResetCarrierRequires32BitUnsigned[(sizeof(unsigned int) == 4) ? 1 : -1];

#pragma push
#pragma opt_dead_assignments off
void func_ov022_0208eee8(struct ReactionCtx *pCtx)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAim;
    struct VecFx32 vecDir;
    struct VecFx32 vecToTarget;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    u16 nAngle;
    int nTrig;
    struct SlotPart *pPart;
    int nPart;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nAngle = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS;
    pSlot->nSlotIndex = (u8)pActor->nSlotIndex;
    pSlot->nSeq = pSlot->nSeq + 1;
    vecAim = *func_ov022_0208a96c(pCtx);
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    MTX_RotY33_(&mtx, data_0203d210[nTrig], data_0203d210[nTrig + 1]);
    MTX_MultVec33(&vecAim, &mtx, &vecAim);
    VEC_Add(&vecAim, &pActor->vecAim, &vecAim);
    func_ov022_0208a8bc(pCtx, (u8 *)pCtx->pOwner + 4, &pSlot->nFlags, 0);
    func_ov022_0208acdc(pCtx, &vecAim, func_ov022_0208acc4(pSlot->nKind, 0));
    /* MWCC ARM32 matching device. Both assignments zero-extend a 32-bit
     * value; the upper word is therefore always zero. The first assignment
     * is redundant at runtime, but its placement controls temporary lifetimes
     * with opt_dead_assignments off. Do not turn this into an extra callee arg. */
    unsigned long long resetCarrier;
    resetCarrier = (unsigned int)(unsigned long long)pSlot;
    pSlot->vecAim = vecAim;
    pSlot->nAngle = nAngle;
    pSlot->nFlags |= FLAG_ACTIVE;
    pSlot->bSeqPending = 1;
    pSlot->nTurns = TURNS_START;
    resetCarrier = (unsigned int)(unsigned long long)pActor;
    pSlot->nArmed = (unsigned int)(resetCarrier >> 32);
    pSlot->nMarkNext = (unsigned int)(resetCarrier >> 32);
    if (func_ov022_020ad114(pActor) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(pActor), &pActor->vecAim, &vecToTarget);
        nAngle = FX_Atan2(vecToTarget.x, vecToTarget.z);
    }
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    vecDir.x = data_0203d210[nTrig];
    vecDir.y = 0;
    vecDir.z = data_0203d210[nTrig + 1];
    func_01ffa724(pSlot->nAdvance, &vecDir, &vecDir);
    VEC_Add(&pActor->vecAim, &vecDir, &vecAim);
    pSlot->nBackAngle = nAngle;
    pSlot->vecBack = vecAim;
    for (nPart = 0; nPart < pSlot->nParts; nPart++) {
        pPart = &pSlot->pParts[nPart];
        if ((pSlot->nBoundMask & (1 << nPart)) == 0) {
            WM_EndKeySharing_0x020b15a4(pCtx->pOwner, pPart->binding);
            pSlot->nBoundMask = pSlot->nBoundMask | (1 << nPart);
        }
        pPart->nGroup = (u8)pActor->nSlotIndex;
        func_ov022_0208a8bc(pCtx, pPart->binding, &pPart->nSlotFlags, 1);
        pPart->bLive = 0;
    }
}

#pragma pop
