/* func_ov023_02086964 -- Ov023_CmdActorSpeak: two-phase script command that puts the event's
 * text block (+0x28 of the event block) on an actor.  Operand 3 is the actor; a negative value
 * marks the second phase (-99 standing for actor 0), which only detaches the text again
 * (0202ba44) and finishes with 1.  In the first phase, once the block's handle (+0xc) is ready
 * (0201eea8), the block is attached to the actor (0202b984) and, when operand 2 asks for it,
 * the actor's sub-panel released (02089604); operand 3's value is then negated for the second
 * phase, the command re-queued (020219b4) and 0 returned. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[2];
    int  nValue;              /* 0x04 */
} Ov023Operand;               /* 0x08 */

typedef struct Ov023TextBlock {
    u8   pad_00[0xc];
    int  nHandle;             /* 0x0c */
} Ov023TextBlock;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023EventBlock {
    u8   pad_000[0x28];
    Ov023TextBlock *pText;    /* 0x028 */
    u8   pad_02c[0x440 - 0x2c];
    Ov023Actor *pActors;      /* 0x440 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern void  func_0202ba44(u16 nEntity);                            /* Entity_DetachText */
extern int   func_0201eea8(int nHandle);                            /* the handle is ready */
extern void  func_0202b984(u16 nEntity, Ov023TextBlock *pText, int nA, int nB); /* Entity_AttachText */
extern void  func_ov023_02089604(Ov023Actor *pActor);               /* Ov023_ReleaseActorPanel */
extern void  func_020219b4(Ov023ScriptCtx *pCtx, Ov023Operand *pCmd); /* ScriptVm_RequeueCommand */

int func_ov023_02086964(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    int nActor;
    int bRelease;

    nActor = func_02021980(pCtx, pOperand + 3);
    if (nActor < 0) {
        if (nActor == -99) {
            nActor = 0;
        }
        func_0202ba44((u16)-nActor);
        return 1;
    }
    if (func_0201eea8(pCtx->pEvent->pText->nHandle) != 0) {
        bRelease = func_02021980(pCtx, pOperand + 2) != 0;
        func_0202b984((u16)nActor, pCtx->pEvent->pText, 0, 0);
        if (bRelease) {
            func_ov023_02089604(&pCtx->pEvent->pActors[nActor]);
        }
        if (nActor == 0) {
            pOperand[3].nValue = -99;
        } else {
            pOperand[3].nValue = -nActor;
        }
    }
    func_020219b4(pCtx, pOperand);
    return 0;
}
