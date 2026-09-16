/* func_ov023_02085a44 -- Ov023_CmdSetAnchor: script command that defines one of the event's
 * four anchors (event block +0x444 positions, +0x474 angles).  Operand 0 is the anchor, 6 its
 * angle in degrees (x 182, kept as a u16); the position is operands 3..5, or, when operand 2
 * names a spot, that spot on the model (0202c3e4 with the model id 0202bf84) of the actor in
 * operand 1.  Returns 1. */
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

typedef struct Ov023EventBlock {
    u8   pad_000[0x444];
    VecFx32 aAnchorPos[4];    /* 0x444 */
    int  aAnchorAngle[4];     /* 0x474 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern int   func_02021994(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern char *func_02021948(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern int   func_0202bf84(u16 nEntity);                            /* Entity_GetModelId */
extern void  func_0202c3e4(u16 nModel, char *pszSpot, VecFx32 *pOut); /* Model_GetSpotPosition */

int func_ov023_02085a44(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    VecFx32 vPos;
    int nAnchor;
    int nAngle;
    int nActor;
    char *pszSpot;

    nAnchor = func_02021980(pCtx, pOperand);
    nAngle = func_02021980(pCtx, pOperand + 6);
    if (pOperand[2].nType == 0) {
        VecFx32 vRead;

        vRead.x = func_02021994(pCtx, pOperand + 3);
        vRead.y = func_02021994(pCtx, pOperand + 4);
        vRead.z = func_02021994(pCtx, pOperand + 5);
        vPos = vRead;
    } else {
        nActor = func_02021980(pCtx, pOperand + 1);
        pszSpot = func_02021948(pCtx, pOperand + 2);
        func_0202c3e4(func_0202bf84((u16)nActor), pszSpot, &vPos);
    }
    pCtx->pEvent->aAnchorPos[nAnchor] = vPos;
    pCtx->pEvent->aAnchorAngle[nAnchor] = (u16)(nAngle * 0xb6);
    return 1;
}
