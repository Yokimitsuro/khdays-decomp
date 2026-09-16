/* func_ov023_0208557c -- Ov023_CmdShowCharacterPanel: script command that opens an ov002
 * character panel for a screen.  Only while the ov002 panel system is available (020573a4).
 * Operand 1 is the screen.  The panel name is the event's pending name (+0x4a4 of the event
 * block) when set, else operand 0's string, prefixed by operand 2's number when present
 * ("%d%s"); the name is split at its separator into the event's pending name
 * (Ov023_SplitPath 0208552c), widened (0202fcb8) and requested as a choice-less ov002 panel
 * (02057300, mode 0, selection = the event's word at +0x484); on success the screen's model
 * flag (scene +0x875d8, Ov023_SetScreenModel 02083a68) is raised. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

typedef struct Ov023PanelRequest {
    u16  *pTitle;             /* 0x00 */
    u16  *apChoices[3];       /* 0x04 */
    int  nFlags;              /* 0x10 */
    int  nSelection;          /* 0x14 */
    int  nMode;               /* 0x18 */
    int  nRequestType;        /* 0x1c */
    int  nReserved;           /* 0x20 */
} Ov023PanelRequest;          /* the ov002 panel request */

typedef struct Ov023EventBlock {
    u8   pad_000[0x484];
    int  nWord484;            /* 0x484 */
    u8   pad_488[0x4a4 - 0x488];
    char szPendingName[0x100]; /* 0x4a4 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int   func_ov002_020573a4(void);                             /* the ov002 panel system is up */
extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern char *func_02021948(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern void  OS_SPrintf(char *pBuffer, const char *pFormat, ...);
extern void  func_ov023_0208552c(char *pszPath, char *pszTail);     /* Ov023_SplitPath */
extern void  func_0202fcb8(char *pszSrc, u16 *pDst);                /* widen a string */
extern int   func_ov002_02057300(Ov023PanelRequest *pRequest, int nArg); /* open an ov002 panel */
extern void  func_ov023_02083a68(int nValue, int nScreen);          /* Ov023_SetScreenModel */
extern char  data_ov023_0208a5d8[];                                 /* "%s" */
extern char  data_ov023_0208a5dc[];                                 /* "%d%s" */

void func_ov023_0208557c(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    char szPath[0x100];
    u16  wszName[0x100];
    Ov023PanelRequest request;
    int  nScreen;
    int  nNumber;

    if (func_ov002_020573a4() != 0) {
        nScreen = func_02021980(pCtx, pOperand + 1);
        if (pCtx->pEvent->szPendingName[0] != 0) {
            OS_SPrintf(szPath, data_ov023_0208a5d8, pCtx->pEvent->szPendingName);
        } else if (pOperand[2].nType != 0) {
            nNumber = func_02021980(pCtx, pOperand + 2);
            OS_SPrintf(szPath, data_ov023_0208a5dc, nNumber, func_02021948(pCtx, pOperand));
        } else {
            OS_SPrintf(szPath, data_ov023_0208a5d8, func_02021948(pCtx, pOperand));
        }
        func_ov023_0208552c(szPath, pCtx->pEvent->szPendingName);
        func_0202fcb8(szPath, wszName);
        request.pTitle = wszName;
        request.apChoices[0] = request.apChoices[1] = request.apChoices[2] = 0;
        request.nMode = 0;
        request.nFlags = 0;
        request.nSelection = pCtx->pEvent->nWord484;
        if (func_ov002_02057300(&request, 0) != 0) {
            func_ov023_02083a68(1, nScreen);
        }
    }
}
