/* func_ov023_02084d98 -- Ov023_CmdResetStage: script command that tears the event's stage down
 * for a scene change.  Operand 0 is the change kind.  The current camera's target mode (+0xf8
 * of camera +0x488 of the event block) is cleared to -1.  Unless bit 1 of the global mode
 * (02020a9c) is set: kind 0 turns the LCD on (POWCNT bit 15), 1 turns it off, both with
 * texture bank 7 and sprite mode 3 / 1 (02010e80), kind 3 uses bank 0xf with mode 4 / 1; the
 * sprite layer is reset (0201133c), the screens handed back (Ov023_Teardown 02084d64), the
 * ov002 side reset (0206da28), the actors reset (02083bd4), pending entity work drained
 * (0202c4b0 while 0202c57c), the entity manager reset (0202b788 / 0202b73c / 0202c440), the
 * scene's sub-object rebuilt (0208402c), game fields 0x2480 := 0 and 0x248f := 1 (020235e8),
 * in a host session (bit 2 of data_0204c240) 02023574 run, and for kind 2 the resource 0x2da
 * requested (0203355c).  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;

static volatile u16 *const REG_POWCNT = (volatile u16 *)0x04000304;

typedef struct Ov023Camera {
    u8   pad_000[0xf8];
    int  nTargetMode;         /* 0xf8 */
    int  nTargetActor;        /* 0xfc */
    int  nField100;           /* 0x100 */
} Ov023Camera;                /* 0x104 */

typedef struct Ov023EventBlock {
    u8   pad_000[0x30];
    Ov023Camera aCamera[2];   /* 0x030 */
    Ov023Camera aCameraAlt[2]; /* 0x238 */
    u8   pad_440[0x488 - 0x440];
    int  nCamera;             /* 0x488 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int   func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);  /* ScriptVm_ReadOperandInt */
extern int   func_02020a9c(void);                                   /* the global mode halfword */
extern void  GX_SetBankForTex(int nBank);
extern void  func_02010e80(int nA, int nB);
extern void  func_0201133c(void);
extern void  func_ov023_02084d64(void);                             /* Ov023_Teardown */
extern void  func_ov002_0206da28(void);
extern void  func_ov023_02083bd4(void);                             /* Ov023_ResetActors */
extern int   func_0202c57c(void);                                   /* entity work pending */
extern void  func_0202c4b0(void);                                   /* run one entity work item */
extern void  func_0202b788(void);                                   /* EntityManager_ReleaseViews */
extern void  func_0202b73c(void);                                   /* EntityManager_ResetSingleton */
extern void  func_0202c440(void);
extern void  func_ov023_0208402c(void);                             /* Ov023_RebuildSubObject */
extern void  func_020235e8(int nField, int nBits, int nValue);      /* GameState_SetField */
extern void  func_02023574(void);
extern void  func_0203355c(int nId);                                /* Res_RequestIdPair */
extern u8    data_0204c240;                                         /* session bits */

int func_ov023_02084d98(Ov023ScriptCtx *pCtx, void *pOperand)
{
    int nKind;

    nKind = func_02021980(pCtx, pOperand);
    pCtx->pEvent->aCamera[pCtx->pEvent->nCamera].nTargetMode = -1;
    if (!(func_02020a9c() & 2)) {
        switch (nKind) {
        case 0:
            *REG_POWCNT |= 0x8000;
            GX_SetBankForTex(7);
            func_02010e80(3, 1);
            break;
        case 1:
            *REG_POWCNT &= 0xffff7fff;
            GX_SetBankForTex(7);
            func_02010e80(3, 1);
            break;
        case 3:
            GX_SetBankForTex(0xf);
            func_02010e80(4, 1);
            break;
        }
        func_0201133c();
        func_ov023_02084d64();
        func_ov002_0206da28();
        func_ov023_02083bd4();
        while (func_0202c57c() != 0) {
            func_0202c4b0();
        }
        func_0202b788();
        func_0202b73c();
        func_0202c440();
        func_ov023_0208402c();
        func_020235e8(0x2480, 1, 0);
        func_020235e8(0x248f, 1, 1);
        if (data_0204c240 & 4) {
            func_02023574();
        }
        if (nKind == 2) {
            func_0203355c(0x2da);
        }
    }
    return 1;
}
