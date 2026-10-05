/* Ov023_CmdShowCharacterPanel -- Ov023_CmdShowCharacterPanel: script command that opens an ov002
 * character panel for a screen.  Only while the ov002 panel system is available (020573a4).
 * Operand 1 is the screen.  The panel name is the event's pending name (+0x4a4 of the event
 * block) when set, else operand 0's string, prefixed by operand 2's number when present
 * ("%d%s"); the name is split at its separator into the event's pending name
 * (Ov023_SplitPath 0208552c), widened (0202fcb8) and requested as a choice-less ov002 panel
 * (02057300, mode 0, selection = the event's word at +0x484); on success the screen's model
 * flag (scene +0x875d8, Ov023_SetScreenModel 02083a68) is raised. */

#include "nitro/types.h"

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

extern int   Ov002_GetPanelField018c(void);                             /* the ov002 panel system is up */
extern int   ScriptVm_ReadOperandInt(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern char *ByteCode_ResolveOperand(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void  Ov023_SplitPath(char *pszPath, char *pszTail);     /* Ov023_SplitPath */
extern void  Utf8_ToUcs2(char *pszSrc, u16 *pDst);                /* widen a string */
extern int   Ov002_TryBeginPanelRequest(Ov023PanelRequest *pRequest, int nArg); /* open an ov002 panel */
extern void  Ov023_SetScriptSlotWord(int nValue, int nScreen);          /* Ov023_SetScreenModel */
extern char  gOv023StrFmt[];                                 /* "%s" */
extern char  gOv023IntStrFmt[];                                 /* "%d%s" */

void Ov023_CmdShowCharacterPanel(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    char szPath[0x100];
    u16  wszName[0x100];
    Ov023PanelRequest request;
    int  nScreen;
    int  nNumber;

    if (Ov002_GetPanelField018c() != 0) {
        nScreen = ScriptVm_ReadOperandInt(pCtx, pOperand + 1);
        if (pCtx->pEvent->szPendingName[0] != 0) {
            OS_SPrintf(szPath, gOv023StrFmt, pCtx->pEvent->szPendingName);
        } else if (pOperand[2].nType != 0) {
            nNumber = ScriptVm_ReadOperandInt(pCtx, pOperand + 2);
            OS_SPrintf(szPath, gOv023IntStrFmt, nNumber, ByteCode_ResolveOperand(pCtx, pOperand));
        } else {
            OS_SPrintf(szPath, gOv023StrFmt, ByteCode_ResolveOperand(pCtx, pOperand));
        }
        Ov023_SplitPath(szPath, pCtx->pEvent->szPendingName);
        Utf8_ToUcs2(szPath, wszName);
        request.pTitle = wszName;
        request.apChoices[0] = request.apChoices[1] = request.apChoices[2] = 0;
        request.nMode = 0;
        request.nFlags = 0;
        request.nSelection = pCtx->pEvent->nWord484;
        if (Ov002_TryBeginPanelRequest(&request, 0) != 0) {
            Ov023_SetScriptSlotWord(1, nScreen);
        }
    }
}
