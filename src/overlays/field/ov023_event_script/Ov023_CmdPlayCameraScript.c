/* Ov023_CmdPlayCameraScript -- Ov023_CmdPlayCameraScript: script command that starts the current
 * camera (+0x488 of the event block, a 0x104-byte block from +0x30) on a camera animation.
 * The camera's player (+0x3c) is stopped (0202e3c4); with operand 1 clear the whole camera is
 * wiped and its target mode (+0xf8) set to 1, else only the player's 0x58 bytes are.  The
 * camera text "ev/ecam.p2" is opened (02024ee8 heap 0xd), its line (operand 0) bound to the
 * player with the packed descriptor (0202e358) and the container closed (02024fd4); the
 * player is rewound (0202e5cc 0) and given operand 2 (0202e618).  The camera then tracks no
 * actor (+0xfc = 0x40), has unit zoom (+0xec = 0x1000) and remembers whether it was kept
 * (+0x100).  Returns 1. */

#include "nitro/types.h"
#include "game/archive.h"

typedef struct Ov023Camera {
    u8   pad_000[0x3c];
    u8   player[0x58];        /* 0x3c: the camera animation player */
    u8   pad_094[0xec - 0x94];
    int  nZoom;               /* 0xec */
    u8   pad_0f0[8];
    int  nTargetMode;         /* 0xf8 */
    int  nTargetActor;        /* 0xfc */
    int  bKept;               /* 0x100 */
} Ov023Camera;                /* 0x104 */

typedef struct Ov023EventBlock {
    u8   pad_000[0x30];
    Ov023Camera aCamera[4];   /* 0x030 */
    u8   pad_440[0x488 - 0x440];
    int  nCamera;             /* 0x488 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int   ScriptVm_ReadOperandInt(Ov023ScriptCtx *pCtx, void *pOperand);  /* ScriptVm_ReadOperandInt */
extern void  CamAnim_Release(void *pPlayer);                          /* CameraPlayer_Stop */
extern void  MI_CpuFill8(void *pDst, u32 nValue, u32 nSize);
extern void *Msg_OpenContainerAndReadHeader(const char *pszName, int nHeap);         /* open a text container */
extern void  CamAnim_Start(void *pPlayer, u32 nDescriptor);         /* CameraPlayer_Bind */
extern void  ZeroHalfThenFree(void *pContainer);                       /* close a text container */
extern void  Obj_SetIndirectWord(void *pPlayer, int nFrame);              /* CameraPlayer_Seek */
extern void  Obj_SetWord54(void *pPlayer, int nArg);                /* CameraPlayer_SetArg */
extern char  gOv023EvEcamPath[];                                 /* "ev/ecam.p2" */

int Ov023_CmdPlayCameraScript(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    int nLine;
    int nArg;
    int bKeep;
    int nCamera;
    void *pText;

    bKeep = ScriptVm_ReadOperandInt(pCtx, pOperand + 8) != 0;
    nLine = ScriptVm_ReadOperandInt(pCtx, pOperand);
    nArg = ScriptVm_ReadOperandInt(pCtx, pOperand + 0x10);
    nCamera = pCtx->pEvent->nCamera;
    CamAnim_Release(pCtx->pEvent->aCamera[nCamera].player);
    if (!bKeep) {
        MI_CpuFill8(&pCtx->pEvent->aCamera[nCamera], 0, 0x104);
        pCtx->pEvent->aCamera[nCamera].nTargetMode = 1;
    } else {
        MI_CpuFill8(pCtx->pEvent->aCamera[nCamera].player, 0, 0x58);
    }
    pText = Msg_OpenContainerAndReadHeader(gOv023EvEcamPath, 0xd);
    CamAnim_Start(pCtx->pEvent->aCamera[nCamera].player,
                  ARCHIVE_HANDLE(pText, nLine & (0xfffffc >> 15)));
    ZeroHalfThenFree(pText);
    Obj_SetIndirectWord(pCtx->pEvent->aCamera[nCamera].player, 0);
    Obj_SetWord54(pCtx->pEvent->aCamera[nCamera].player, nArg);
    pCtx->pEvent->aCamera[nCamera].nTargetActor = 0x40;
    pCtx->pEvent->aCamera[nCamera].nZoom = 0x1000;
    pCtx->pEvent->aCamera[nCamera].bKept = bKeep;
    return 1;
}
