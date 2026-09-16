/* func_ov023_020846bc -- Ov023_ResolveSpeakerOperands: read a command's speaker from its
 * operands 2 and 3, one of which may be a string.  Operands 1 and 4 are read and discarded.
 * When operand 2 is the string it is copied out (0201f924) and operand 3 read as the speaker
 * value: for a session slot below 4 that value, unless it is -3 or game flag 0x2001 + slot is
 * clear, selects the slot's occupant (020315c0), else the local player's (02030788), and the
 * member kind (+4) of the occupant found -- 0 without one -- is returned; from slot 4 on the
 * value itself is.  When operand 3 is the string instead, it is copied and operand 2 read;
 * with neither, operand 3 is read. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023SessionSlot {
    int  nField00;            /* 0x00 */
    int  nMemberKind;         /* 0x04 */
} Ov023SessionSlot;

extern int   func_02021980(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandInt */
extern char *func_02021948(void *pCtx, Ov023Operand *pOperand);     /* ScriptVm_ReadOperandString */
extern Ov023Operand *func_020218a4(void *pCtx, Ov023Operand *pOperand); /* ScriptVm_ResolveOperand */
extern void  func_0201f924(char *pszDst, const char *pszSrc);       /* STD_CopyString */
extern int   func_02023588(int nFlag);                              /* GameState_IsFlagSet */
extern int   func_02030788(void);                                   /* Session_GetLocalPlayerIndex */
extern Ov023SessionSlot *func_020315c0(int nSlot);                  /* Session_GetSlotIfOccupied */

void func_ov023_020846bc(void *pCtx, Ov023Operand *pOperand, int nSlot, int *pnKind, char *pszName)
{
    Ov023Operand *pOpA;
    Ov023Operand *pOpB;
    int nValue;
    Ov023SessionSlot *pSlot;

    func_02021980(pCtx, pOperand + 1);
    func_02021980(pCtx, pOperand + 4);
    pOpA = func_020218a4(pCtx, pOperand + 2);
    pOpB = func_020218a4(pCtx, pOperand + 3);
    if (pOpA->nType == 2) {
        func_0201f924(pszName, func_02021948(pCtx, pOpA));
        nValue = func_02021980(pCtx, pOpB);
        if (nSlot < 4) {
            if (nValue == -3 || func_02023588(nSlot + 0x2001) == 0) {
                pSlot = func_020315c0(func_02030788());
            } else {
                pSlot = func_020315c0(nSlot);
            }
            if (pSlot == 0) {
                *pnKind = 0;
            } else {
                *pnKind = pSlot->nMemberKind;
            }
        } else {
            *pnKind = nValue;
        }
    } else if (pOpB->nType == 2) {
        func_0201f924(pszName, func_02021948(pCtx, pOpB));
        *pnKind = func_02021980(pCtx, pOpA);
    } else {
        *pnKind = func_02021980(pCtx, pOpB);
    }
}
