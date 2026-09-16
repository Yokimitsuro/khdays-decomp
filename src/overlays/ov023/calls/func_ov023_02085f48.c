/* func_ov023_02085f48 -- Ov023_CmdPlayCameraScript: script command that starts the current
 * camera (+0x488 of the event block, a 0x104-byte block from +0x30) on a camera animation.
 * The camera's player (+0x3c) is stopped (0202e3c4); with operand 1 clear the whole camera is
 * wiped and its target mode (+0xf8) set to 1, else only the player's 0x58 bytes are.  The
 * camera text "ev/ecam.p2" is opened (02024ee8 heap 0xd), its line (operand 0) bound to the
 * player with the packed descriptor (0202e358) and the container closed (02024fd4); the
 * player is rewound (0202e5cc 0) and given operand 2 (0202e618).  The camera then tracks no
 * actor (+0xfc = 0x40), has unit zoom (+0xec = 0x1000) and remembers whether it was kept
 * (+0x100).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned int   u32;

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

extern int   func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);  /* ScriptVm_ReadOperandInt */
extern void  func_0202e3c4(void *pPlayer);                          /* CameraPlayer_Stop */
extern void  MI_CpuFill8(void *pDst, u32 nValue, u32 nSize);
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open a text container */
extern void  func_0202e358(void *pPlayer, u32 nDescriptor);         /* CameraPlayer_Bind */
extern void  func_02024fd4(void *pContainer);                       /* close a text container */
extern void  func_0202e5cc(void *pPlayer, int nFrame);              /* CameraPlayer_Seek */
extern void  func_0202e618(void *pPlayer, int nArg);                /* CameraPlayer_SetArg */
extern char  data_ov023_0208a610[];                                 /* "ev/ecam.p2" */

int func_ov023_02085f48(Ov023ScriptCtx *pCtx, u8 *pOperand)
{
    int nLine;
    int nArg;
    int bKeep;
    int nCamera;
    void *pText;

    bKeep = func_02021980(pCtx, pOperand + 8) != 0;
    nLine = func_02021980(pCtx, pOperand);
    nArg = func_02021980(pCtx, pOperand + 0x10);
    nCamera = pCtx->pEvent->nCamera;
    func_0202e3c4(pCtx->pEvent->aCamera[nCamera].player);
    if (!bKeep) {
        MI_CpuFill8(&pCtx->pEvent->aCamera[nCamera], 0, 0x104);
        pCtx->pEvent->aCamera[nCamera].nTargetMode = 1;
    } else {
        MI_CpuFill8(pCtx->pEvent->aCamera[nCamera].player, 0, 0x58);
    }
    pText = func_02024ee8(data_ov023_0208a610, 0xd);
    func_0202e358(pCtx->pEvent->aCamera[nCamera].player,
                  ((((u32)pText + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (nLine & (0xfffffc >> 15)));
    func_02024fd4(pText);
    func_0202e5cc(pCtx->pEvent->aCamera[nCamera].player, 0);
    func_0202e618(pCtx->pEvent->aCamera[nCamera].player, nArg);
    pCtx->pEvent->aCamera[nCamera].nTargetActor = 0x40;
    pCtx->pEvent->aCamera[nCamera].nZoom = 0x1000;
    pCtx->pEvent->aCamera[nCamera].bKept = bKeep;
    return 1;
}
