/* Ov022_StepAnchorDelta -- how far the actor's anchor moved this frame, in
 * the node's own frame.
 *
 * The vector from the spare slot to the anchor slot is taken (scaled by the
 * inverse of the anchor scale when that is not one) and its difference from
 * last frame's is turned by the negated node angle into pOut. Flag bits 29
 * and 30 mark a frame whose delta must be zero. When the node's animation
 * flags carry bit 2 the output is zeroed and both bits are raised; otherwise
 * bit 30 drops unless bit 29 is up, and bit 29 drops. The vector is kept for
 * the next frame.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

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
    u8 pad00[4];
    u16 nAnimFlags;                  /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                      /* 0x80 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                      /* 0x0000 */
    u8 pad0008[0x18];
    struct ActorNode *pNode;         /* 0x0020 */
    u8 pad0024[0x434];
    int nAnchorScale;                /* 0x0458 */
    u8 pad045c[0xc0];
    int nSlotSpare;                  /* 0x051c */
    int nSlotAnchor;                 /* 0x0520 */
    u8 pad0524[0x3c8];
    struct VecFx32 vecAnchorDelta;   /* 0x08ec */
};

#define FLAG_BIT29 (1ULL << 29)
#define FLAG_BIT30 (1ULL << 30)
#define FX32_ONE 0x1000
#define ANGLE_BIAS 0x8000
#define ANGLE_STEP 4
#define ANIM_HOLD 0x4

extern short data_0203d210[];            /* sin, cos pairs by angle >> 4 */

extern int FX_Inv(int nNumerator, int nDenominator);
extern void MTX_RotY33_(struct MtxFx33 *pMtx, int nSin, int nCos);
extern void func_ov022_020ad7f0(struct Actor *pActor, int nSlot, struct VecFx32 *pOut);
extern void VEC_Subtract(struct VecFx32 *a, struct VecFx32 *b, struct VecFx32 *pOut);
extern void func_01ffa724(int nFactor, struct VecFx32 *pSrc, struct VecFx32 *pDst);
extern void MTX_MultVec33(struct VecFx32 *pVec, struct MtxFx33 *pMtx, struct VecFx32 *pOut);

void func_ov022_0209fe20(struct Actor *pActor, struct VecFx32 *pOut)
{
    struct MtxFx33 mtx;
    struct VecFx32 vecAnchor;
    struct VecFx32 vecSpare;
    int nScale;
    u16 nAngle;
    int nTrig;

    nAngle = pActor->pNode->nAngle - ANGLE_BIAS;
    nScale = FX32_ONE;
    if (pActor->nAnchorScale != FX32_ONE) {
        nScale = FX_Inv(FX32_ONE, pActor->nAnchorScale);
    }
    nTrig = (nAngle >> ANGLE_STEP) * 2;
    MTX_RotY33_(&mtx, -data_0203d210[nTrig], -data_0203d210[nTrig + 1]);
    func_ov022_020ad7f0(pActor, pActor->nSlotAnchor, &vecAnchor);
    func_ov022_020ad7f0(pActor, pActor->nSlotSpare, &vecSpare);
    VEC_Subtract(&vecAnchor, &vecSpare, &vecAnchor);
    if (nScale != FX32_ONE) {
        func_01ffa724(nScale, &vecAnchor, &vecAnchor);
    }
    if ((pActor->nFlags & FLAG_BIT29) != 0 || (pActor->nFlags & FLAG_BIT30) != 0) {
        pOut->x = 0;
        pOut->y = 0;
        pOut->z = 0;
    } else {
        VEC_Subtract(&vecAnchor, &pActor->vecAnchorDelta, pOut);
        MTX_MultVec33(pOut, &mtx, pOut);
    }
    if ((pActor->pNode->nAnimFlags & ANIM_HOLD) != 0) {
        pOut->z = 0;
        pOut->y = 0;
        pOut->x = 0;
        pActor->nFlags |= FLAG_BIT29;
        pActor->nFlags |= FLAG_BIT30;
    } else {
        if ((pActor->nFlags & FLAG_BIT29) == 0) {
            pActor->nFlags &= ~FLAG_BIT30;
        }
        pActor->nFlags &= ~FLAG_BIT29;
    }
    pActor->vecAnchorDelta = vecAnchor;
}
