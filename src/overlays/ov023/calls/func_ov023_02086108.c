/* func_ov023_02086108 -- Ov023_CmdPlaceObject: script command that places one of the scene's
 * model objects (Ov023_PlaceObject 02083afc).  Operand 1 is the object's index, 2 / 3 its
 * position and 4 / 5 its angles in degrees; operand 0, when given, names the resource to start
 * it on.  Returns 1. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

extern int   func_02021980(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandInt */
extern char *func_02021948(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandString */
extern void  func_ov023_02083afc(const char *pszResource, int nIndex, int nX, int nY, int nAngleA, int nAngleB); /* Ov023_PlaceObject */

int func_ov023_02086108(void *pCtx, Ov023Operand *pOperand)
{
    int nIndex;
    int nX;
    int nY;
    int nAngleA;
    int nAngleB;

    nIndex = func_02021980(pCtx, pOperand + 1);
    nX = func_02021980(pCtx, pOperand + 2);
    nY = func_02021980(pCtx, pOperand + 3);
    nAngleA = func_02021980(pCtx, pOperand + 4);
    nAngleB = func_02021980(pCtx, pOperand + 5);
    if (pOperand->nType != 0) {
        func_ov023_02083afc(func_02021948(pCtx, pOperand), nIndex, nX, nY, nAngleA, nAngleB);
    } else {
        func_ov023_02083afc(0, nIndex, nX, nY, nAngleA, nAngleB);
    }
    return 1;
}
