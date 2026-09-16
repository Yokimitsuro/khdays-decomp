/* func_ov023_02087cec -- Ov023_ActorWithinReach: whether the actor's walk target (+0x15c0) is
 * within 0x19a of the position pPos would reach after one step of pStep scaled by nScale
 * (VEC_MultAdd-like: nScale * step + pos).  With flag bit 4 (+0x1a28) the height is ignored.
 * Returns 1 when the remaining distance (VEC_Mag) is below 0x19a. */
typedef unsigned char  u8;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Actor {
    u8   pad_0000[0x15c0];
    VecFx32 vTarget;          /* 0x15c0 */
    u8   pad_15cc[0x1a28 - 0x15cc];
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void func_01ffa724(int nScale, const VecFx32 *pVec, VecFx32 *pOut); /* VEC_Scale */
extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int  VEC_Mag(const VecFx32 *pVec);

int func_ov023_02087cec(Ov023Actor *pActor, VecFx32 *pPos, VecFx32 *pStep, int nScale)
{
    VecFx32 vNext;
    VecFx32 vDelta;

    func_01ffa724(nScale, pStep, &vDelta);
    VEC_Add(pPos, &vDelta, &vNext);
    VEC_Subtract(&pActor->vTarget, &vNext, &vDelta);
    if (pActor->nFlags & 0x10) {
        vDelta.y = 0;
    }
    return VEC_Mag(&vDelta) < 0x19a;
}
