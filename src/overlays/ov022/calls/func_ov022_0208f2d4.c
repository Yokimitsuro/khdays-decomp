/* Ov022_EnterGroundReaction -- open a reaction slot whose part settles on the
 * ground.
 *
 * The slot takes the actor's slot index and a fresh sequence number, and its
 * aim point is the shared aim offset turned by the actor's node angle and added
 * to the actor's aim; the aim is bound on the owner's track and announced
 * through the notifier before it is stored with the angle and the sequence
 * marked pending. The first idle part is bound on the owner's track once (the
 * bound mask remembers which already are), put in state 1 with the actor's
 * slot index as its group and its timer cleared, bound to the shared sequence
 * (index 2 when the slot's 0x134 word is positive, else 1), and given the
 * angle.
 *
 * Where the part lands depends on the target: with a valid target the part is
 * settled straight down from the target's position; without one it is cast
 * along the facing from half a unit behind the actor's aim, raised by half a
 * unit, for the slot's interval length. Unless bit 0 of the slot's 0x164 word
 * is set the start point is jittered by up to 1.5 units on x and z. The
 * settled point becomes the part's position.
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
    int nTimer;                      /* 0x000 */
    struct VecFx32 vecPos;           /* 0x004 */
    struct VecFx32 vecVel;           /* 0x010 */
    u16 nSlotFlags;                  /* 0x01c */
    u8 pad01e[0x7a];
    u16 nAngle;                      /* 0x098 */
    u8 pad09a[0x8a];
    u16 binding[2];                  /* 0x124 */
    u8 pad128[0x24];
    u8 nState;                       /* 0x14c */
    u8 nGroup : 3;                   /* 0x14d */
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
    u16 nFlags;                      /* 0x008 */
    u8 pad00a[0x7a];
    u16 nAngle;                      /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;           /* 0x0ac */
    u8 pad0b8[0x58];
    s8 nSlotIndex;                   /* 0x110 */
    u8 pad111[0xb];
    int nHalfBound;                  /* 0x11c */
    u8 pad120[0xc];
    int nInterval;                   /* 0x12c reach of the cast without a target */
    u8 pad130[4];
    int nField134;                   /* 0x134 positive: bind the part on index 2 */
    u8 pad138[0x2c];
    int nField164;                   /* 0x164 bit 0 disables the start jitter */
    struct SlotPart *pParts;         /* 0x168 */
    u8 pad16c[4];
    int bSeqPending;                 /* 0x170 */
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
#define FX32_HALF 0x800
#define JITTER_RANGE 0x3000
#define JITTER_HALF 0x1800
#define NO_JITTER 1

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern struct VecFx32 *func_ov022_0208a96c(struct ReactionCtx *pCtx);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(struct VecFx32 *pVec, struct MtxFx33 *pMtx,
                          struct VecFx32 *pOut);
extern void VEC_Add(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void VEC_MultAdd(int nScale, struct VecFx32 *pA, struct VecFx32 *pB,
                        struct VecFx32 *pOut);
extern void func_ov022_0208a8bc(struct ReactionCtx *pCtx, void *pTarget,
                                u16 *pFlags, int nIndex);
extern int func_ov022_0208acc4(int nKind, int nReaction);
extern void func_ov022_0208acdc(struct ReactionCtx *pCtx, struct VecFx32 *pAim,
                                int nReaction);
extern void WM_EndKeySharing_0x020b15a4(void *pOwner, u16 *pBinding);
extern int func_ov022_020ad114(struct Actor *pActor);
extern struct VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc,
                          struct VecFx32 *pDst);
extern int func_02023e80(u32 nRange);
extern void func_ov022_0208e80c(struct VecFx32 *pOut, struct ReactionCtx *pCtx,
                                struct VecFx32 *pOrigin, struct VecFx32 *pDir,
                                int nRadius, unsigned int nGroup);

/* Byte-exact only with dead-assignment elimination off for this function (as ov004 dd70,
 * ov000 73e4, ov008 2528): with it on, build 139 hoists the bSeqPending constant into the
 * flags-load shadow where the ROM keeps it at its store. Restored after the function. */
#pragma push
#pragma opt_dead_assignments off
void func_ov022_0208f2d4(struct ReactionCtx *pCtx)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAim;
    struct VecFx32 vecDir;
    struct VecFx32 vecJitter;
    struct VecFx32 vecSettled;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    u16 nAngle;
    int nIndex;
    short nSin;
    short nCos;
    struct SlotPart *pPart;
    int i;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nAngle = (u16)(pActor->pNode->nAngle - ANGLE_BIAS) + ANGLE_BIAS;
    pSlot->nSlotIndex = (u8)pActor->nSlotIndex;
    pSlot->nSeq = pSlot->nSeq + 1;
    vecAim = *func_ov022_0208a96c(pCtx);
    nIndex = (nAngle >> ANGLE_STEP) * 2;
    nCos = data_0203d210[nIndex + 1];
    nSin = data_0203d210[nIndex];
    MTX_RotY33_(&mtx, nSin, nCos);
    MTX_MultVec33(&vecAim, &mtx, &vecAim);
    VEC_Add(&vecAim, &pActor->vecAim, &vecAim);
    func_ov022_0208a8bc(pCtx, (u8 *)pCtx->pOwner + 4, &pSlot->nFlags, 0);
    func_ov022_0208acdc(pCtx, &vecAim, func_ov022_0208acc4(pSlot->nKind, 0));
    pPart = 0;
    pSlot->vecAim = vecAim;
    pSlot->nAngle = nAngle;
    pSlot->nFlags = pSlot->nFlags | FLAG_ACTIVE;
    i = 0;
    pSlot->bSeqPending = 1;
    while (i < pSlot->nParts) {
        if (pSlot->pParts[i].nState == 0) {
            pPart = &pSlot->pParts[i];
            break;
        }
        i = i + 1;
    }
    if ((pSlot->nBoundMask & (1 << i)) == 0) {
        WM_EndKeySharing_0x020b15a4(pCtx->pOwner, pPart->binding);
        pSlot->nBoundMask = pSlot->nBoundMask | (1 << i);
    }
    pPart->nState = 1;
    pPart->nGroup = (u8)pActor->nSlotIndex;
    pPart->nTimer = 0;
    if (pSlot->nField134 > 0) {
        func_ov022_0208a8bc(pCtx, pPart->binding, &pPart->nSlotFlags, 2);
    } else {
        func_ov022_0208a8bc(pCtx, pPart->binding, &pPart->nSlotFlags, 1);
    }
    pPart->nAngle = nAngle;
    pPart->nSlotFlags = pPart->nSlotFlags | FLAG_ACTIVE;
    if (func_ov022_020ad114(pActor) != 0) {
        vecDir.x = 0;
        vecDir.y = 0;
        vecDir.z = 0;
        vecAim = *func_ov022_020ad0c0(pActor);
    } else {
        vecDir.x = nSin;
        vecDir.y = 0;
        vecDir.z = nCos;
        VEC_MultAdd(-FX32_HALF, &vecDir, &vecAim, &vecAim);
        func_01ffa724(pSlot->nInterval, &vecDir, &vecDir);
        vecAim = pActor->vecAim;
        vecAim.y = vecAim.y + FX32_HALF;
    }
    if ((pSlot->nField164 & NO_JITTER) == 0) {
        vecJitter.x = func_02023e80(JITTER_RANGE) - JITTER_HALF;
        vecJitter.z = func_02023e80(JITTER_RANGE) - JITTER_HALF;
        vecJitter.y = 0;
        VEC_Add(&vecAim, &vecJitter, &vecAim);
    }
    func_ov022_0208e80c(&vecSettled, pCtx, &vecAim, &vecDir, pSlot->nHalfBound,
                        pSlot->nSlotIndex);
    pPart->vecPos = vecSettled;
}

#pragma pop
