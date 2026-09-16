/* func_ov023_0208895c -- Ov023_ActorStep: one frame of an event actor.  With flag bit 9
 * (+0x1a28) the motion queues run first (Ov023_ActorUpdateMotions 02088144) and an actor whose
 * flags are all gone is finished; a hidden actor (bit 5) or an inactive one (bit 0 clear) does
 * nothing more.  The heading (+0x1a30) turns towards its target (+0x1a34) by the turn speed
 * (+0x15b8, as fx32) times 0x888 per frame, slowing to 0x2d8 within 0x2000 of the target and
 * landing exactly on it; the turn direction (+0x15bc) picks the way -- -1 the shorter way, 0
 * always upwards (a target more than half a turn away is reached at once), anything else
 * downwards (within 0xb6 the heading snaps).  The new heading goes to the entity (+0x15e0,
 * +0x80) unless it is locked (bit 5 of +0).  A tracking actor (bit 6) samples its track
 * (Ov023_ActorStepTrack 02087620) adding the velocity (+0x15cc) and keeps the horizontal step
 * (+0x15e8, y 0) unless it is below 0x10; an attached one (bit 12) follows its parent
 * (Ov023_ActorFollowParent 0208776c).  A walk speed (+0x15d8) walks (Ov023_ActorWalkStep
 * 02087d64).  Then, when the velocity or the step is not zero, a grounded actor (bit 4) is
 * re-placed (0202de3c) and, when its slot word (+0x15e4) has bit 2, its entity dropped by 0xcd
 * (0202b450); otherwise the step (or, when that is zero, the velocity) is added to the
 * entity's position.  Bit 7 runs the effect timing (Ov023_ActorStepEffects 02087bc8) and the
 * step is reset to the zero vector (data_02041dc8) for the next frame. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x6];
    u16  nAngle;              /* 0x80 */
    u8   pad_82[0xa8 - 0x82];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x15b8];
    int  nTurnSpeed;          /* 0x15b8: fx32 */
    int  nTurnDirection;      /* 0x15bc: -1 shorter way, 0 up, else down */
    VecFx32 vTarget;          /* 0x15c0 */
    VecFx32 vVelocity;        /* 0x15cc */
    int  nWalkSpeed;          /* 0x15d8 */
    int  nWalkMotion;         /* 0x15dc */
    Ov023Entity *pEntity;     /* 0x15e0 */
    int  nEntityFlags;        /* 0x15e4 */
    VecFx32 vStep;            /* 0x15e8 */
    u8   pad_15f4[0x1a28 - 0x15f4];
    int  nFlags;              /* 0x1a28 */
    int  nModel;              /* 0x1a2c */
    int  nAngle;              /* 0x1a30 */
    int  nAngleTarget;        /* 0x1a34 */
} Ov023Actor;

extern void func_ov023_02088144(Ov023Actor *pActor);               /* Ov023_ActorUpdateMotions */
extern void func_ov023_02087620(Ov023Actor *pActor, VecFx32 *pStep); /* Ov023_ActorStepTrack */
extern void func_ov023_0208776c(Ov023Actor *pActor);               /* Ov023_ActorFollowParent */
extern void func_ov023_02087d64(Ov023Actor *pActor);               /* Ov023_ActorWalkStep */
extern void func_ov023_02087bc8(Ov023Actor *pActor);               /* Ov023_ActorStepEffects */
extern void VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern int  VEC_Mag(const VecFx32 *pVec);
extern void func_0202de3c(Ov023Entity **ppEntity, int nArg);      /* re-place an entity */
extern void func_0202b450(Ov023Entity *pEntity, VecFx32 *pPos);   /* Actor_SetVecAndSyncChild */
extern const VecFx32 data_02041dc8;                                 /* the zero vector */

static inline void Ov023_EntitySetAngle(Ov023Entity *pEntity, int nAngle)
{
    if (!(pEntity->nFlags & 0x20)) {
        pEntity->nAngle = nAngle;
        pEntity->wFlags |= 0x20;
    }
}

void func_ov023_0208895c(Ov023Actor *pActor)
{
    VecFx32 vStep;
    VecFx32 vPos;
    int nFlags;
    int nDelta;
    int nTurn;
    int nAngle;

    nDelta = pActor->nAngleTarget - pActor->nAngle;
    vStep.x = vStep.y = vStep.z = 0;
    nFlags = pActor->nFlags;
    if (nFlags & 0x200) {
        func_ov023_02088144(pActor);
        nFlags = pActor->nFlags;
        if (nFlags == 0) {
            return;
        }
    }
    if (nFlags & 0x20) {
        return;
    }
    if (!(nFlags & 1)) {
        return;
    }
    if (nDelta < 0) {
        nDelta += 0x10000;
    }
    if ((nDelta < 0x8000 && pActor->nTurnDirection == -1) || pActor->nTurnDirection == 0) {
        if (nDelta < 0x8000) {
            if (nDelta > 0x2000) {
                nTurn = (int)(((long long)pActor->nTurnSpeed * 0x888 + 0x800) >> 12);
            } else {
                nTurn = (int)(((long long)pActor->nTurnSpeed * 0x2d8 + 0x800) >> 12);
                if (nDelta <= nTurn) {
                    nTurn = nDelta;
                }
            }
            nAngle = nTurn + pActor->nAngle;
            if (nAngle > 0xffff) {
                nAngle -= 0x10000;
            }
        } else {
            nAngle = pActor->nAngle + nDelta;
        }
    } else if (nDelta > 0xb6) {
        if (nDelta < 0xe000) {
            nTurn = (int)(((long long)pActor->nTurnSpeed * 0x888 + 0x800) >> 12);
        } else {
            nTurn = (int)(((long long)pActor->nTurnSpeed * 0x2d8 + 0x800) >> 12);
            if (nDelta >= 0x10000 - nTurn) {
                nTurn = 0x10000 - nDelta;
            }
        }
        nAngle = pActor->nAngle - nTurn;
        if (nAngle < 0) {
            nAngle += 0x10000;
        }
    } else {
        nAngle = pActor->nAngle + nDelta;
    }
    pActor->nAngle = nAngle;
    Ov023_EntitySetAngle(pActor->pEntity, nAngle);
    if (pActor->nFlags & 0x40) {
        func_ov023_02087620(pActor, &vStep);
        VEC_Add(&vStep, &pActor->vVelocity, &vStep);
        if (VEC_Mag(&vStep) <= 0x10) {
            vStep.x = vStep.y = vStep.z = 0;
        }
        pActor->vStep.x = vStep.x;
        pActor->vStep.y = 0;
        pActor->vStep.z = vStep.z;
    } else if (pActor->nFlags & 0x1000) {
        func_ov023_0208776c(pActor);
    }
    if (pActor->nWalkSpeed != 0) {
        func_ov023_02087d64(pActor);
    }
    if (pActor->nFlags & 0x10) {
        if (VEC_Mag(&pActor->vVelocity) != 0 || VEC_Mag(&vStep) != 0) {
            func_0202de3c(&pActor->pEntity, 0);
            if (pActor->nEntityFlags & 4) {
                vPos = pActor->pEntity->vPos;
                vPos.y -= 0xcd;
                func_0202b450(pActor->pEntity, &vPos);
            }
        }
    } else {
        if (VEC_Mag(&pActor->vVelocity) != 0 || VEC_Mag(&vStep) != 0) {
            vPos = pActor->pEntity->vPos;
            if (VEC_Mag(&vStep) != 0) {
                VEC_Add(&vPos, &vStep, &vPos);
            } else {
                VEC_Add(&vPos, &pActor->vVelocity, &vPos);
            }
            func_0202b450(pActor->pEntity, &vPos);
        }
    }
    if (pActor->nFlags & 0x80) {
        func_ov023_02087bc8(pActor);
    }
    pActor->vStep.x = data_02041dc8.x;
    pActor->vStep.y = 0;
    pActor->vStep.z = data_02041dc8.z;
}
