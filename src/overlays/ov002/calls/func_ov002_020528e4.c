/*
 * Ov002_PumpPendingLoads - advance the head of the pending-load list one step.
 *
 * The nodes are the 0x20-byte entries appended by func_ov002_02052a6c: state at
 * +0x00, the key or file name at +0x04, the load's buffer at +0x08, and a
 * completion callback at +0x10 with its argument at +0x0c. Only the head is
 * touched per call, so the queue drains strictly in order.
 *
 * A fresh node waits until the file system's request queue is completely idle -
 * that is what asking about id zero means - and only then starts its own load,
 * moving to state 1. A loading node waits until no request is left carrying its
 * buffer, which is how the load reports itself finished; then it goes to state
 * 2, migrates from the pending list to the done list that follows it in the
 * same object, and fires its callback.
 *
 * ARM. Two things shape the code: the state test is a switch, which is what
 * gives the ROM's dispatch - compare against zero, compare against one, return
 * - rather than a fall-through chain; and the state store is emitted before the
 * list move.
 */

extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNS_FndAppendListObject(void *pList, void *pObj);
extern int func_0201eea8(int nId);   /* Obj_IsIdFree in Ghidra */
extern int func_0201ebdc(char *pName, int nKind);

extern int data_ov002_0207f608;   /* the pending list, done list at +0xc */

void func_ov002_020528e4(void)
{
    int *pList;
    int *pNode;

    pList = *(int **)&data_ov002_0207f608;
    pNode = (int *)NNS_FndGetNextListObject(pList, 0);
    if (pNode == 0) {
        return;
    }

    switch (pNode[0]) {
    case 0:
        if (func_0201eea8(0) == 0) {
            return;
        }
        pNode[2] = func_0201ebdc((char *)pNode[1], 0xe);
        pNode[0] = 1;
        break;

    case 1:
        if (func_0201eea8(pNode[2]) == 0) {
            return;
        }
        pNode[0] = 2;
        NNS_FndRemoveListObject(pList, pNode);
        NNS_FndAppendListObject(pList + 3, pNode);
        if (pNode[4] != 0) {
            ((void (*)(int *, int))pNode[4])(pNode, pNode[3]);
        }
        break;
    }
}
