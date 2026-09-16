/* func_ov023_0208776c -- Ov023_ActorFollowParent: place an actor that hangs off a parent (+0).
 * The position starts as the parent's entity position (+0x15e0; +0xa8).  A parent with no
 * track (+0x15b0 == -1) only passes its heading (+0x80) to the actor's entity; otherwise the
 * parent's track step (020875b0) is rotated by the parent's heading (FX_SinCosTable_,
 * MTX_RotY43_ / MTX_MultVec43) and added, with the actor's height offset (+0x15ac) on y.
 * The position is then applied to the actor's entity (0202b450). */
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
    u8   pad_82[0xa8 - 0x82];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    u8   pad_0004[0x15ac - 0x4];
    int  nHeightOffset;       /* 0x15ac */
    int  nTrack;              /* 0x15b0 */
    u8   pad_15b4[0x15e0 - 0x15b4];
    Ov023Entity *pEntity;     /* 0x15e0 */
} Ov023Actor;

extern void  func_ov023_020875b0(Ov023Actor *pActor, VecFx32 *pOut); /* Ov023_ActorSampleTrack */
extern void  MTX_Identity43_(MtxFx43 *pMtx);
extern void  MTX_RotY43_(MtxFx43 *pMtx, int nSin, int nCos);
extern void  MTX_MultVec43(const VecFx32 *pVec, const MtxFx43 *pMtx, VecFx32 *pOut);
extern void  func_0202b450(Ov023Entity *pEntity, VecFx32 *pPos);   /* Entity_SetPositionNow */
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */

/* Give an entity a heading unless it is locked (bit 5 of its flags). */
static inline void Ov023_EntitySetAngle(Ov023Entity *pEntity, int nAngle)
{
    if (!(pEntity->nFlags & 0x20)) {
        pEntity->nAngle = nAngle;
        pEntity->wFlags |= 0x20;
    }
}

void func_ov023_0208776c(Ov023Actor *pActor)
{
    MtxFx43 mtx;
    VecFx32 vPos;
    VecFx32 vStep;
    u16 nHeading;

    nHeading = pActor->pParent->pEntity->nAngle;
    vPos = pActor->pParent->pEntity->vPos;
    if (pActor->pParent->nTrack != -1) {
        func_ov023_020875b0(pActor->pParent, &vStep);
        MTX_Identity43_(&mtx);
        MTX_RotY43_(&mtx, data_0203d210[(nHeading >> 4) * 2], data_0203d210[(nHeading >> 4) * 2 + 1]);
        MTX_MultVec43(&vStep, &mtx, &vStep);
        vPos.x = vPos.x + vStep.x;
        vPos.z = vPos.z + vStep.z;
        vPos.y = vPos.y + pActor->nHeightOffset;
    } else {
        Ov023_EntitySetAngle(pActor->pEntity, nHeading);
    }
    func_0202b450(pActor->pEntity, &vPos);
}
