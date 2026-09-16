/* func_ov023_02088da0 -- Ov023_ActorSetVelocity: set an actor's velocity (+0x15cc), or clear
 * it without a vector.  With flag bit 2 (+0x1a28) the actor turns to face it: the target angle
 * (+0x1a34) becomes 0x13fff minus the heading of the normalised vector (VEC_Normalize,
 * FX_Atan2 of z / x), as a u16.  The horizontal step (+0x15e8 x, +0x15ec 0, +0x15f0 z) is the
 * velocity, or zero when it is no longer than 0x10 (VEC_Mag). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Actor {
    u8   pad_0000[0x15cc];
    VecFx32 vVelocity;        /* 0x15cc */
    u8   pad_15d8[0x15e8 - 0x15d8];
    VecFx32 vStep;            /* 0x15e8 */
    u8   pad_15f4[0x1a28 - 0x15f4];
    int  nFlags;              /* 0x1a28 */
    int  nField1a2c;          /* 0x1a2c */
    int  nAngle;              /* 0x1a30 */
    int  nAngleTarget;        /* 0x1a34 */
} Ov023Actor;

extern void func_01ff8d18(const VecFx32 *pVec, VecFx32 *pOut);      /* VEC_Normalize */
extern u16  FX_Atan2(int nY, int nX);
extern int  VEC_Mag(const VecFx32 *pVec);

void func_ov023_02088da0(Ov023Actor *pActor, VecFx32 *pVelocity)
{
    VecFx32 vStep;
    VecFx32 vDir;

    if (pVelocity == 0) {
        pActor->vVelocity.x = 0;
        pActor->vVelocity.y = 0;
        pActor->vVelocity.z = 0;
    } else {
        pActor->vVelocity = *pVelocity;
        if (pActor->nFlags & 4) {
            func_01ff8d18(&pActor->vVelocity, &vDir);
            pActor->nAngleTarget = (u16)(0x13fff - FX_Atan2(vDir.z, vDir.x));
        }
    }
    vStep = pActor->vVelocity;
    if (VEC_Mag(&vStep) <= 0x10) {
        vStep.x = vStep.y = vStep.z = 0;
    }
    pActor->vStep.x = vStep.x;
    pActor->vStep.y = 0;
    pActor->vStep.z = vStep.z;
}
