/* Ov022_RunContactMode2 -- fire a combo slot's contact through the actor's
 * own contact hook.
 *
 * Nothing with flag bit 27. A slot whose cue frame has come (and is not
 * negative) is cued once: its side raises flag-3 bit 46 or 47. A slot whose
 * start frame has come fires once: the contact point is the actor's aim plus
 * the side's slot position relative to the spare slot, turned by the node's
 * facing (or nothing when the side has no slot); the hook is called with it
 * and flag bit 22 raised, and its answer is the result.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int m[3][3];
} MtxFx33;

/* Ov022ComboSlot */
struct ComboSlot {
    u8 pad00[4];
    int nStartFrame;             /* 0x04 */
    int nCueFrame;               /* 0x08 negative: never cued */
    u8 pad0c[0xc];
    s8 nSide;                    /* 0x18 0 or 1 */
    u8 pad19[0x1b];
    union {
        u8 nFlags;               /* 0x34 */
        struct {
            u8 bFired : 1;       /* bit 0 */
            u8 bCued : 1;        /* bit 1 */
            u8 nRest : 6;
        } bits;
    } f;
};

/* Ov022ActorNode */
struct ActorNode {
    u8 pad00[0x80];
    u16 nAngle;                  /* 0x80 */
};

struct Actor;

typedef int (*ContactFn)(struct Actor *pActor, VecFx32 *pPos, struct ComboSlot *pSlot, int bFull);

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;     /* 0x0020 */
    u8 pad0024[0x448];
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x18];
    VecFx32 vecAim;              /* 0x048c */
    u8 pad0498[0x7c];
    int nSlotSideA;              /* 0x0514 */
    int nSlotSideB;              /* 0x0518 */
    int nSlotSpare;              /* 0x051c */
    u8 pad0520[0x160];
    ContactFn pfnContact;        /* 0x0680 */
    u8 pad0684[0x12c];
    int nAnimFrame;              /* 0x07b0 */
};

#define FLAG_BIT22 (1ULL << 22)
#define FLAG_BIT27 (1ULL << 27)
#define FLAG3_BIT46 (1ULL << 46)
#define FLAG3_BIT47 (1ULL << 47)
#define SLOT_CUED 0x2
#define SLOT_NONE (-1)
#define SIDE_A 0
#define SIDE_B 1
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern void func_ov022_020ad7f0(struct Actor *pActor, int nSlot, VecFx32 *pOut);   /* Ov022_GetSlotPos */
extern void MTX_RotY33_(MtxFx33 *pMtx, int nSin, int nCos);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern void MTX_MultVec33(VecFx32 *pVec, MtxFx33 *pMtx, VecFx32 *pOut);
extern void VEC_Add(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);

int func_ov022_020a5d18(struct Actor *pActor, struct ComboSlot *pSlot, int bFull)
{
    VecFx32 vecPos;
    VecFx32 vecOff;
    MtxFx33 mtx;
    VecFx32 vecSpare;
    int nSlot;
    u16 nAngle;
    int nTrig;
    int nRet;

    if ((pActor->nFlags & FLAG_BIT27) != 0) {
        return 0;
    }
    if (pSlot->nCueFrame >= 0 && pSlot->nCueFrame <= pActor->nAnimFrame && !pSlot->f.bits.bCued) {
        switch (pSlot->nSide) {
        case SIDE_A:
            pActor->nFlags3 |= FLAG3_BIT46;
            break;
        case SIDE_B:
            pActor->nFlags3 |= FLAG3_BIT47;
            break;
        }
        pSlot->f.nFlags |= SLOT_CUED;
    }
    if (pSlot->nStartFrame > pActor->nAnimFrame || pSlot->f.bits.bFired) {
        return 0;
    }
    nSlot = SLOT_NONE;
    func_ov022_020ad7f0(pActor, pActor->nSlotSpare, &vecSpare);
    switch (pSlot->nSide) {
    case SIDE_A:
        nSlot = pActor->nSlotSideA;
        break;
    case SIDE_B:
        nSlot = pActor->nSlotSideB;
        break;
    }
    if (nSlot != SLOT_NONE) {
        nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
        nTrig = (nAngle >> ANGLE_STEP) * 2;
        MTX_RotY33_(&mtx, -data_0203d210[nTrig], -data_0203d210[nTrig + 1]);
        func_ov022_020ad7f0(pActor, nSlot, &vecOff);
        VEC_Subtract(&vecOff, &vecSpare, &vecOff);
        MTX_MultVec33(&vecOff, &mtx, &vecOff);
    } else {
        vecOff.z = 0;
        vecOff.y = 0;
        vecOff.x = 0;
    }
    VEC_Add(&vecOff, &pActor->vecAim, &vecPos);
    pSlot->f.bits.bFired = 1;
    nRet = pActor->pfnContact(pActor, &vecPos, pSlot, bFull);
    pActor->nFlags |= FLAG_BIT22;
    return nRet;
}
