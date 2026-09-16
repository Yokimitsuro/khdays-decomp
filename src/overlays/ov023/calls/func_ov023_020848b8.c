/* func_ov023_020848b8 -- Ov023_ReadTargetPosition: resolve a command's target position for an
 * actor.  Operands 2..4 give an offset vector and operand 6 a distance; operand 1 decides the
 * base: as an fx32 (type 0) the offset itself is the position; as an angle in degrees (type 1)
 * the position is the actor's own (Entity_Get 0202bfcc, +0xa8) plus the distance along the
 * heading (sin, 0, cos from FX_SinCosTable_; VEC_MultAdd); as a string (type 2) it is that
 * spot on the actor's model (0202c3e4 with the entity's model id 0202bf84) plus the offset
 * (VEC_Add). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

extern int   func_02021980(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandInt */
extern int   func_02021994(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandFx32 */
extern char *func_02021948(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandString */
extern Ov023Operand *func_020218a4(void *pCtx, Ov023Operand *pOperand); /* ScriptVm_ResolveOperand */
/* The quotient is the low half of the helper's long long return; writing `/` emits _s32_div_f,
 * which is not linkable here. */
extern long long func_02020400(int nNumerator, int nDenominator);
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */
extern int   func_0202bf84(u16 nEntity);                            /* Entity_GetModelId */
extern void  func_0202c3e4(u16 nModel, char *pszSpot, VecFx32 *pOut); /* Model_GetSpotPosition */
extern void  VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void  VEC_MultAdd(int nScale, const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern const short data_0203d210[];                                 /* FX_SinCosTable_: sin, cos pairs */

void func_ov023_020848b8(void *pCtx, Ov023Operand *pOperand, int nActor, VecFx32 *pOut)
{
    VecFx32 vOffset;
    VecFx32 vDir;
    int nDistance;
    Ov023Operand *pOp;
    int nAngle;
    char *pszSpot;

    nDistance = func_02021994(pCtx, pOperand + 6);
    pOp = func_020218a4(pCtx, pOperand + 1);
    vOffset.x = func_02021994(pCtx, pOperand + 2);
    vOffset.y = func_02021994(pCtx, pOperand + 3);
    vOffset.z = func_02021994(pCtx, pOperand + 4);
    switch (pOp->nType) {
    case 2:
        pszSpot = func_02021948(pCtx, pOp);
        func_0202c3e4(func_0202bf84((u16)nActor), pszSpot, pOut);
        VEC_Add(pOut, &vOffset, pOut);
        break;
    case 1:
        nAngle = (u16)func_02020400(func_02021980(pCtx, pOp) << 16, 360);
        vDir.x = data_0203d210[(nAngle >> 4) * 2];
        vDir.y = 0;
        vDir.z = data_0203d210[(nAngle >> 4) * 2 + 1];
        VEC_MultAdd(nDistance, &vDir, &func_0202bfcc((u16)nActor)->vPos, pOut);
        break;
    case 0:
        *pOut = vOffset;
        break;
    }
}
