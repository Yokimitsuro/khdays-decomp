typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad00[4];
    char *pContext;                 /* +0x04 */
} Ov002SceneRef;

extern Ov002SceneRef data_ov002_0207fa20;

/* A scene command as it reaches the router: what to do, who to do it to, and
 * one argument.  Target kind 0xff with the wildcard id is the broadcast form. */
typedef struct {
    u8  bOp;                        /* +0x00 */
    u8  bTargetKind;                /* +0x01 */
    u16 wTargetId;                  /* +0x02 */
    u16 wArg;                       /* +0x04 */
} Ov002SceneCommand;

extern void func_ov002_020765ac(int nKind);
extern void func_ov002_02077f64(int nId, Ov002SceneCommand *pCmd, void *pParam);
extern int func_ov002_02076a80(int pList, int nId);
extern void func_ov002_02076bbc(int pNode, Ov002SceneCommand *pCmd, void *pParam);

/* Route a scene command to whatever it is addressed to.
 *
 * Target kind 0xff paired with the wildcard id 0xffff is the broadcast form,
 * and only operation 1 has anything to broadcast.  Kind 0x1f has a router of
 * its own.  Every other kind names one of the node lists the context keeps
 * from +0x17c on, and the command's id picks the node out of it; a command
 * addressed to a node that is not there is dropped.
 */
void func_ov002_0207605c(Ov002SceneCommand *pCmd, void *pParam)
{
    int pNode;

    if (pCmd->bTargetKind == 0xff && pCmd->wTargetId == 0xffff) {
        if (pCmd->bOp == 1) {
            func_ov002_020765ac(pCmd->wArg);
        }
        return;
    }

    if (pCmd->bTargetKind == 0x1f) {
        func_ov002_02077f64(pCmd->wTargetId, pCmd, pParam);
        return;
    }

    pNode = func_ov002_02076a80(
        *(int *)(data_ov002_0207fa20.pContext + pCmd->bTargetKind * 4 + 0x17c),
        pCmd->wTargetId);
    if (pNode != 0) {
        func_ov002_02076bbc(pNode, pCmd, pParam);
    }
}
