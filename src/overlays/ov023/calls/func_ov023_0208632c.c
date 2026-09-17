/* func_ov023_0208632c -- Ov023_CmdPlaceRelative: script command that places one actor next to
 * another.  Operand 0 is the actor to place, operand 1 the reference actor and operand 2 (fx32)
 * the offset; operand 3, when present, is the forward distance, else the offset is used for
 * it too.  The current camera's motion is sampled for its angles (Camera_SampleMotion 02021418
 * on +0x30 of the event block by +0x488) and the offset vector (0, offset, distance) is turned
 * about Y by the camera yaw (MTX_RotY43_ from FX_SinCosTable_, MTX_MultVec43), mirrored in x
 * and added to the reference entity's position (0202bfcc, +0xa8).  The actor's entity is put
 * there (Entity_SetPosition 0202ba78 with the reference's model id 0202bf84), takes the
 * reference's heading (+0x80) unless locked (bit 5 of +0), is shown (0202beb8) and, when the
 * event has actors, its model is placed (Ov023_PlaceActorModel 020887dc).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct MtxFx43 {
    int  a[12];               /* 0x00 */
} MtxFx43;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[2];
    int  nValue;              /* 0x04 */
} Ov023Operand;

typedef struct Ov023Camera {
    u8   pad_00[0x104];
} Ov023Camera;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x30];
    Ov023Camera aCamera[2];   /* 0x030 */
    u8   pad_238[0x440 - 0x238];
    Ov023Actor *pActors;      /* 0x440 */
    u8   pad_444[0x488 - 0x444];
    int  nCamera;             /* 0x488 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x6];
    u16  nAngle;              /* 0x80 */
    u8   pad_82[0xa8 - 0x82];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern int   func_02021994(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern int   func_02020d10(Ov023ScriptCtx *pCtx, int nActor);              /* ScriptVm_ResolveActor */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                            /* Entity_Get */
extern int   func_0202bf84(u16 nEntity);                                   /* Entity_GetModelId */
extern void  func_02021418(Ov023Camera *pCamera, VecFx32 *pPos, VecFx32 *pAngle, int *pDistance, int *pRoll); /* Camera_SampleMotion */
extern void  func_0202ba78(u16 nEntity, u16 nModel, char *pszSpot, VecFx32 *pPos); /* Entity_SetPosition */
extern void  func_0202beb8(u16 nEntity, int bVisible);                     /* Entity_SetVisible */
extern void  func_ov023_020887dc(Ov023Actor *pActor, char *pszAnchor, VecFx32 *pPos, int nModel, int nActor); /* Ov023_PlaceActorModel */
extern void  MTX_Identity43_(MtxFx43 *pMtx);
extern void  MTX_RotY43_(MtxFx43 *pMtx, int nSin, int nCos);
extern void  MTX_MultVec43(const VecFx32 *pVec, const MtxFx43 *pMtx, VecFx32 *pOut);
extern void  VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern const short data_0203d210[];                                        /* FX_SinCosTable_ */

static inline void Ov023_EntitySetAngle(Ov023Entity *pEntity, int nAngle)
{
    if (!(pEntity->nFlags & 0x20)) {
        pEntity->nAngle = nAngle;
        pEntity->wFlags |= 0x20;
    }
}

int func_ov023_0208632c(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    int nActor = func_02021980(pCtx, pOperand);
    int nReference = func_02021980(pCtx, pOperand + 1);
    int nOffset = func_02021994(pCtx, pOperand + 2);
    int nEntity = func_02020d10(pCtx, nActor);
    VecFx32 vCameraAngle;
    VecFx32 vPos;
    MtxFx43 mtxRot;
    VecFx32 vOffset;
    Ov023EventBlock *pEvent = pCtx->pEvent;
    Ov023Entity *pEntity;
    int nHeading;
    int nModel;
    u16 nYaw;
    int nIdx;
    int nSinCos;
    int nDistance;

    func_02021418(&pEvent->aCamera[pEvent->nCamera], 0, &vCameraAngle, 0, 0);
    pEntity = func_0202bfcc((u16)nReference);
    nHeading = pEntity->nAngle;
    vPos = pEntity->vPos;
    nModel = func_0202bf84((u16)nReference);
    nDistance = pOperand[3].nType == 0 ? nOffset : func_02021994(pCtx, pOperand + 3);
    nYaw = (u16)vCameraAngle.x;
    vOffset.x = 0;
    vOffset.y = nOffset;
    vOffset.z = nDistance;
    MTX_Identity43_(&mtxRot);
    nIdx = (int)nYaw >> 4;
    nSinCos = nIdx * 2;
    MTX_RotY43_(&mtxRot, data_0203d210[nSinCos], data_0203d210[nSinCos + 1]);
    MTX_MultVec43(&vOffset, &mtxRot, &vOffset);
    vOffset.x = -vOffset.x;
    VEC_Add(&vPos, &vOffset, &vPos);
    func_0202ba78((u16)nEntity, (u16)nModel, 0, &vPos);
    pEntity = func_0202bfcc((u16)nEntity);
    Ov023_EntitySetAngle(pEntity, nHeading);
    func_0202beb8((u16)nEntity, 1);
    if (pCtx->pEvent->pActors != 0) {
        func_ov023_020887dc(&pCtx->pEvent->pActors[nEntity], 0, &vPos, nModel, nEntity);
    }
    return 1;
}
