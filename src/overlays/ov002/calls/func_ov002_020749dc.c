/* The 0x50 byte task record this command builds on the stack. */
typedef struct Ov002TaskNode {
    int nHandle;                        /* +0x00 */
    unsigned char bMode;                /* +0x04 */
    unsigned char bPad;                 /* +0x05 */
    unsigned short nCount;              /* +0x06 */
    short aLow[16];                     /* +0x08 */
    short aHigh[16];                    /* +0x28 */
    unsigned short wTail;               /* +0x48 */
    unsigned char bTail;                /* +0x4a */
    unsigned char bPad2;                /* +0x4b */
    int nExtra;                         /* +0x4c */
} Ov002TaskNode;

extern int func_02021980(int pCtx, unsigned short *pOperand);
extern void func_ov002_0206af88(int bFlag, int nSlot, int nKind,
                                Ov002TaskNode *pNode);

/* Script command: build a task node from the command's operands and submit it.
 *
 * The first five operands give a flag, the slot, the node handle, how many
 * pairs follow and a mode byte. Each of the next operands carries two shorts
 * packed in its second word, which are split into the node's low and high
 * arrays. Three more operands close the record, and the node goes in with kind
 * three, gated on the first operand being zero.
 */
int func_ov002_020749dc(int pCtx, unsigned short *pArgs)
{
    Ov002TaskNode node;
    int nFlag;
    int nSlot;
    int nHandle;
    int nCount;
    int nMode;
    int i;
    int k;
    unsigned short *pOp;

    k = 0;
    nFlag = func_02021980(pCtx, pArgs);
    nSlot = func_02021980(pCtx, pArgs + 4);
    nHandle = func_02021980(pCtx, pArgs + 8);
    nCount = func_02021980(pCtx, pArgs + 0xc);
    k += 5;
    nMode = func_02021980(pCtx, pArgs + 0x10);
    node.nHandle = nHandle;

    i = 0;
    if (nCount > 0) {
        pOp = pArgs + k * 4;
        do {
            node.aLow[i] = (short)*(int *)(pOp + 2);
            node.aHigh[i] = (short)((unsigned int)*(int *)(pOp + 2) >> 16);
            pOp += 4;
            k++;
            i++;
        } while (i < nCount);
    }

    node.bMode = (unsigned char)nMode;
    node.nCount = (unsigned short)nCount;
    node.bTail = (unsigned char)func_02021980(pCtx, pArgs + k * 4);
    node.wTail = (unsigned short)func_02021980(pCtx, pArgs + (k + 1) * 4);
    node.nExtra = func_02021980(pCtx, pArgs + (k + 2) * 4);

    func_ov002_0206af88(nFlag == 0, nSlot, 3, &node);
    return 1;
}
