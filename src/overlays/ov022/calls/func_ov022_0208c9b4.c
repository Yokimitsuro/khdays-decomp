/* Ov022_EnterReactionAtOffset -- arm a reaction whose aim point sits away from
 * the actor.
 *
 * The state's own offset vector is turned by the actor's facing, sampled from
 * the shared sine table at the facing's top bits, and added to where the actor
 * is; that point goes through the notifier and becomes the slot's aim. The slot
 * also takes the actor's slot index, a fresh sequence number and the facing
 * itself, the entry flags are broadcast across all three words, and the state is
 * armed with its timer cleared. The speed cap goes to the model as a whole
 * number.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

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
    u16 nAngle;                  /* 0x80 */
};

/* Ov022Actor */
struct Actor {
    u8 pad000[0x20];
    struct ActorNode *pNode;     /* 0x020 */
    u8 pad024[0x42];
    short nSlotIndex;            /* 0x066 */
    u8 pad068[0x424];
    struct VecFx32 vecAim;       /* 0x48c */
};

/* Ov022ActorSlot */
struct ActorSlot {
    u8 nKind;                    /* 0x000 */
    u8 pad001;
    u8 nSeq;                     /* 0x002 */
    u8 pad003[5];
    u16 nSlotFlags;              /* 0x008 */
    u8 pad00a[0x76];
    int nModel;                  /* 0x080 */
    u16 nAngle;                  /* 0x084 */
    u8 pad086[0x26];
    struct VecFx32 vecAim;       /* 0x0ac */
    int aEntryFlags[3];          /* 0x0b8 */
    u8 pad0c4[0x4c];
    s8 nSlotIndex;               /* 0x110 */
    u8 pad111[7];
    u8 nState;                   /* 0x118 */
    u8 pad119[3];
    int nTimer;                  /* 0x11c */
    u8 pad120[0xc];
    int nInterval;               /* 0x12c */
    u8 pad130[4];
    int nField134;               /* 0x134 */
};

/* Ov022ReactionCtx */
struct ReactionCtx {
    u8 pad00[0xc];
    int nSlot;                   /* 0x0c */
    u8 pad10[8];
    struct ActorSlot *aSlots[11];/* 0x18 */
    u8 pad44[0x10];
    int nTrack;                  /* 0x54 */
    struct Actor *pActor;        /* 0x58 */
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
extern void func_02016d10(int nModel, int nSpeed);

#define HALF_TURN 0x8000
#define SLOT_FLAG_ARMED 0x20
#define SLOT_ARMED 1
#define SLOT_SPEED 0x1f000

void func_ov022_0208c9b4(struct ReactionCtx *pCtx)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAim;
    struct Actor *pActor;
    struct ActorSlot *pSlot;
    struct VecFx32 *pOffset;
    int nReaction;
    int nIndex;
    u16 nBack;
    u16 nFacing;

    pActor = pCtx->pActor;
    pSlot = pCtx->aSlots[pCtx->nSlot];
    nBack = pActor->pNode->nAngle - HALF_TURN;
    pSlot->nSlotIndex = (s8)pActor->nSlotIndex;
    nFacing = nBack + HALF_TURN;
    pSlot->nSeq = pSlot->nSeq + 1;
    func_ov022_0208a8bc(pCtx, pCtx->nTrack + 4, &pSlot->nSlotFlags, 0);
    pOffset = func_ov022_0208a96c(pCtx);
    nIndex = nFacing >> 4;
    vecAim = *pOffset;
    MTX_RotY33_(&mtx, data_0203d210[nIndex * 2], data_0203d210[nIndex * 2 + 1]);
    MTX_MultVec33(&vecAim, &mtx, &vecAim);
    VEC_Add(&vecAim, &pActor->vecAim, &vecAim);
    nReaction = func_ov022_0208acc4(pSlot->nKind, 0);
    func_ov022_0208acdc(pCtx, &vecAim, nReaction);
    pSlot->vecAim = vecAim;
    pSlot->nAngle = nFacing;
    pSlot->nSlotFlags |= SLOT_FLAG_ARMED;
    pSlot->aEntryFlags[0] = pSlot->aEntryFlags[1] = pSlot->aEntryFlags[2] =
        pSlot->nField134;
    pSlot->nState = SLOT_ARMED;
    pSlot->nTimer = 0;
    pSlot->nInterval = SLOT_SPEED;
    func_02016d10(pSlot->nModel, pSlot->nInterval >> 12);
}
