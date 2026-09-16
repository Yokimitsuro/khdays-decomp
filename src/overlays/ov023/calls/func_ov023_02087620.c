/* func_ov023_02087620 -- Ov023_ActorStepTrack: advance an actor along its motion track and
 * return the step.  The track position is sampled (020875b0), the difference from the last
 * sample (+0x159c) rotated by the entity's heading (+0x15e0; +0x80, FX_SinCosTable_, MTX_RotY43_
 * / MTX_MultVec43) into pOut, and the sample kept.  While a turn is pending (+0x15b4) the
 * track's own heading is derived from the first word of its entry (+0xac4 + track * 0x58,
 * FX_AcosIdx 02005430): turn state 1 rewinds the actor's angle (+0x1a30 / +0x1a34) by the
 * heading's change since the last offset (+0x15a8) and pushes it onto the entity, and the
 * heading, negated when the entry's third word is not negative, becomes the new offset. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct MtxFx43 {
    int  a[12];               /* 0x00 */
} MtxFx43;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x06];
    u16  nAngle;              /* 0x80 */
} Ov023Entity;

typedef struct Ov023TrackHead {
    int  nCos;                /* 0x00 */
    int  nField04;            /* 0x04 */
    int  nDirection;          /* 0x08 */
    int  aField0c[6];         /* 0x0c */
} Ov023TrackHead;             /* 0x24 */

typedef struct Ov023Track {
    Ov023TrackHead head;      /* 0x00 */
    VecFx32 vPos;             /* 0x24 */
    u8   pad_30[0x58 - 0x30];
} Ov023Track;                 /* 0x58 */

typedef struct Ov023Actor {
    u8   pad_0000[0xac4];
    Ov023Track aTrack[1];     /* 0x0ac4 */
    u8   pad_0b1c[0x159c - 0xb1c];
    VecFx32 vTrackPos;        /* 0x159c */
    int  nAngleOffset;        /* 0x15a8 */
    int  nField15ac;          /* 0x15ac */
    int  nTrack;              /* 0x15b0 */
    int  nTurnState;          /* 0x15b4 */
    u8   pad_15b8[0x15e0 - 0x15b8];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a30 - 0x15e4];
    int  nAngle;              /* 0x1a30 */
    int  nAngleTarget;        /* 0x1a34 */
} Ov023Actor;

extern void  func_ov023_020875b0(Ov023Actor *pActor, VecFx32 *pOut); /* Ov023_ActorSampleTrack */
extern void  VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void  MTX_Identity43_(MtxFx43 *pMtx);
extern void  MTX_RotY43_(MtxFx43 *pMtx, int nSin, int nCos);
extern void  MTX_MultVec43(const VecFx32 *pVec, const MtxFx43 *pMtx, VecFx32 *pOut);
extern u16   func_02005430(int nCos);                               /* FX_AcosIdx */
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */

/* Give an entity a heading unless it is locked (bit 5 of its flags). */
static inline void Ov023_EntitySetAngle(Ov023Entity *pEntity, int nAngle)
{
    if (!(pEntity->nFlags & 0x20)) {
        pEntity->nAngle = nAngle;
        pEntity->wFlags |= 0x20;
    }
}

void func_ov023_02087620(Ov023Actor *pActor, VecFx32 *pOut)
{
    MtxFx43 mtx;
    VecFx32 vPos;
    u16 nHeading;
    int nAngle;

    nHeading = pActor->pEntity->nAngle;
    func_ov023_020875b0(pActor, &vPos);
    VEC_Subtract(&vPos, &pActor->vTrackPos, pOut);
    MTX_Identity43_(&mtx);
    MTX_RotY43_(&mtx, data_0203d210[(nHeading >> 4) * 2], data_0203d210[(nHeading >> 4) * 2 + 1]);
    MTX_MultVec43(pOut, &mtx, pOut);
    pActor->vTrackPos = vPos;
    if (pActor->nTurnState != 0) {
        Ov023TrackHead head;

        head = pActor->aTrack[pActor->nTrack].head;
        nAngle = func_02005430(head.nCos);
        if (pActor->nTurnState == 1) {
            pActor->nAngle -= nAngle - pActor->nAngleOffset;
            pActor->nAngle = (u16)pActor->nAngle;
            pActor->nAngleTarget = pActor->nAngle;
            Ov023_EntitySetAngle(pActor->pEntity, pActor->nAngle);
        }
        if (head.nDirection >= 0) {
            nAngle = -nAngle;
        }
        pActor->nAngleOffset = nAngle;
    }
}
