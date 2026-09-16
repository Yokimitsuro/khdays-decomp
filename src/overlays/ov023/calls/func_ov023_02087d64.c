/* func_ov023_02087d64 -- Ov023_ActorWalkStep: one frame of an actor walking to its target
 * (+0x15c0).  The remaining vector from the entity's position (+0x15e0; +0xa8), ignoring
 * height with flag bit 4 (+0x1a28), is measured (VEC_Mag): within 0x19a the walk ends -- the
 * velocity cleared (Ov023_ActorSetVelocity 02088da0), the speed (+0x15d8) and target zeroed.
 * Otherwise the step is the speed / 30 (capped at the distance) and the velocity becomes the
 * remaining vector scaled by step / distance (FX_Mul, FX_Div); while a walk motion is pending
 * (+0x15dc), reaching the target within the actor's period (+4, as fx32) with flag bit 7
 * resets its model (02089174) and reaching it within 10 units (0xa000) starts the motion
 * (Ov023_ActorPlayMotion 020894c0 with 0 / 10 / 1) and forgets it. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    int  nPeriod;             /* 0x0004 */
    u8   pad_0008[0x15c0 - 0x8];
    VecFx32 vTarget;          /* 0x15c0 */
    u8   pad_15cc[0x15d8 - 0x15cc];
    int  nWalkSpeed;          /* 0x15d8 */
    int  nWalkMotion;         /* 0x15dc */
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a28 - 0x15e4];
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int  VEC_Mag(const VecFx32 *pVec);
extern int  FX_Inv(int nNumerator, int nDenominator);              /* the SDK divide (FX_Inv in the symbol table) */
extern void func_ov023_02088da0(Ov023Actor *pActor, VecFx32 *pVelocity); /* Ov023_ActorSetVelocity */
extern int  func_ov023_02087cec(Ov023Actor *pActor, VecFx32 *pPos, VecFx32 *pStep, int nScale); /* Ov023_ActorWithinReach */
extern void func_ov023_02089174(Ov023Actor *pActor);               /* Ov023_ResetActorModel */
extern void func_ov023_020894c0(Ov023Actor *pActor, char *pszName, int nMotion, int nA, int nB, int nC); /* Ov023_ActorPlayMotion */

void func_ov023_02087d64(Ov023Actor *pActor)
{
    VecFx32 vPos;
    VecFx32 vDelta;
    int nStep;
    int nDistance;

    vPos = pActor->pEntity->vPos;
    nStep = pActor->nWalkSpeed / 30;
    VEC_Subtract(&pActor->vTarget, &vPos, &vDelta);
    if (pActor->nFlags & 0x10) {
        vDelta.y = 0;
    }
    nDistance = VEC_Mag(&vDelta);
    if (nDistance < 0x19a) {
        func_ov023_02088da0(pActor, 0);
        pActor->nWalkSpeed = 0;
        pActor->vTarget.x = pActor->vTarget.y = pActor->vTarget.z = 0;
        return;
    }
    if (nDistance < nStep) {
        nStep = nDistance;
    }
    vDelta.x = FX_Inv((int)(((long long)vDelta.x * nStep + 0x800) >> 12), nDistance);
    if (!(pActor->nFlags & 0x10)) {
        vDelta.y = FX_Inv((int)(((long long)vDelta.y * nStep + 0x800) >> 12), nDistance);
    }
    vDelta.z = FX_Inv((int)(((long long)vDelta.z * nStep + 0x800) >> 12), nDistance);
    func_ov023_02088da0(pActor, &vDelta);
    if (pActor->nWalkMotion != -1) {
        if (func_ov023_02087cec(pActor, &vPos, &vDelta, pActor->nPeriod << 12) && (pActor->nFlags & 0x80)) {
            func_ov023_02089174(pActor);
        }
        if (func_ov023_02087cec(pActor, &vPos, &vDelta, 0xa000)) {
            func_ov023_020894c0(pActor, 0, pActor->nWalkMotion, 0, 10, 1);
            pActor->nWalkMotion = -1;
        }
    }
}
