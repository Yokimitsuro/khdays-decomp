/* func_ov023_02084168 -- Ov023_CmdPlaceActor: script command that places an actor.  Operand 0
 * is the actor (resolved by 02020d10), operand 1 the placement mode, operands 3..5 the position.
 * Without operand 2 the position is applied directly (Entity_SetPosition 0202ba78) with the
 * facing of operand 6 in degrees (x 65536 / 360) stored on the entity (0202bfcc; +0x80, flag
 * bit 5 of +4) unless its bit 5 at +0 is set.  With an "AnchorPos<n>" operand the position is
 * rotated by anchor n's angle (event block +0x474, sin / cos from FX_SinCosTable_) and offset
 * by its position (+0x444), the entity taking the anchor's angle; any other name is passed to
 * the setter as the anchor.  The entity is then shown (0202beb8 1) and, when the actor table
 * (+0x440) exists and the entity's bit 5 (0202c424) is clear, the actor's model is placed too
 * (Ov023_PlaceActorModel 020887dc).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x440];
    Ov023Actor *pActors;      /* 0x440 */
    VecFx32 aAnchorPos[4];    /* 0x444 */
    int  aAnchorAngle[4];     /* 0x474 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x06];
    u16  nAngle;              /* 0x80 */
} Ov023Entity;

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern char *func_02021948(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern int   func_02021994(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern int   func_02020d10(Ov023ScriptCtx *pCtx, int nIndex);      /* resolve an actor index */
/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern void  func_0202ba78(u16 nEntity, u16 nMode, char *pszAnchor, VecFx32 *pPos); /* Entity_SetPosition */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */
extern void  func_0202beb8(u16 nEntity, int bVisible);              /* Entity_SetVisible */
extern int   func_0202c424(u16 nEntity);                            /* Entity_GetFlags */
extern int   strncmp(const char *pA, const char *pB, int nCount);
extern int   func_020200b4(char *pszNumber);                        /* parse a number */
extern int   func_02005418(int nA, int nB);                           /* FX_Mul */
extern void  func_ov023_020887dc(Ov023Actor *pActor, char *pszAnchor, VecFx32 *pPos, int nMode, int nActor); /* Ov023_PlaceActorModel */
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */
extern char  data_ov023_0208a5cc[];                                 /* "AnchorPos" */

int func_ov023_02084168(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    VecFx32 vPos;
    int nActor;
    int nMode;
    char *pszAnchor;
    int nAngle;
    int nAnchor;
    int nX;
    int nSin;
    s16 nCos;
    int nZ;
    Ov023Entity *pEntity;

    nActor = func_02020d10(pCtx, func_02021980(pCtx, pOperand));
    nMode = func_02021980(pCtx, pOperand + 1);
    vPos.x = func_02021994(pCtx, pOperand + 3);
    vPos.y = func_02021994(pCtx, pOperand + 4);
    vPos.z = func_02021994(pCtx, pOperand + 5);
    if (pOperand[2].nType == 0) {
        pszAnchor = 0;
        nAngle = (u16)func_02020400(func_02021980(pCtx, pOperand + 6) << 16, 360);
        func_0202ba78((u16)nActor, (u16)nMode, 0, &vPos);
        pEntity = func_0202bfcc((u16)nActor);
        if (!(pEntity->nFlags & 0x20)) {
            pEntity->nAngle = nAngle;
            pEntity->wFlags |= 0x20;
        }
    } else {
        pszAnchor = func_02021948(pCtx, pOperand + 2);
        if (strncmp(pszAnchor, data_ov023_0208a5cc, 9) == 0) {
            pszAnchor += 9;
            nAnchor = func_020200b4(pszAnchor);
            nSin = data_0203d210[(pCtx->pEvent->aAnchorAngle[nAnchor] >> 4) * 2];
            nCos = data_0203d210[(pCtx->pEvent->aAnchorAngle[nAnchor] >> 4) * 2 + 1];
            nX = pCtx->pEvent->aAnchorPos[nAnchor].x + func_02005418(nCos, vPos.x) + func_02005418(nSin, vPos.z);
            nZ = pCtx->pEvent->aAnchorPos[nAnchor].z + func_02005418(-nSin, vPos.x) + func_02005418(nCos, vPos.z);
            vPos.x = nX;
            vPos.z = nZ;
            vPos.y = vPos.y + pCtx->pEvent->aAnchorPos[nAnchor].y;
            func_0202ba78((u16)nActor, (u16)nMode, 0, &vPos);
            nAngle = pCtx->pEvent->aAnchorAngle[nAnchor];
            pEntity = func_0202bfcc((u16)nActor);
            if (!(pEntity->nFlags & 0x20)) {
                pEntity->nAngle = nAngle;
                pEntity->wFlags |= 0x20;
            }
            pszAnchor = 0;
        } else {
            func_0202ba78((u16)nActor, (u16)nMode, pszAnchor, &vPos);
        }
    }
    func_0202beb8((u16)nActor, 1);
    if (pCtx->pEvent->pActors != 0 && !(func_0202c424((u16)nActor) & 0x20)) {
        func_ov023_020887dc(&pCtx->pEvent->pActors[nActor], pszAnchor, &vPos, nMode, nActor);
    }
    return 1;
}
