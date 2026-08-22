/*
 * Ov002_DrainLoadQueue - tear both load lists down.
 *
 * The pending list is emptied first, and a node caught mid-load is settled
 * before it is freed: the file system is made to finish what it has in flight,
 * and whatever buffer the load had already produced is released. Then the node
 * leaves the list, its key is released - but only when it really is a heap
 * string, since a key with bit 31 set is an inline archive handle and is merely
 * cleared - and the node itself goes back to the heap.
 *
 * The done list is emptied after it, and those nodes are handed to the disposal
 * routine instead: their loads have already landed, so something else owns what
 * they produced.
 *
 * THUMB. The node is declared before the queue: mwcc colours the two
 * callee-saved pointers in declaration order, and the ROM keeps the node in
 * the lower register.
 */

extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0201ef58(void);                      /* settle the file system */
extern void func_ov002_02052af4(int *pNode, int nFlag);

extern int data_ov002_0207f608;   /* the pending list, done list at +0xc */

void func_ov002_020529cc(void)
{
    int *pNode;
    int *pQueue;
    int *pNext;

    pQueue = *(int **)&data_ov002_0207f608;
    pNode = (int *)NNS_FndGetNextListObject(pQueue, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pQueue, pNode);
        if (pNode[0] == 1) {
            func_0201ef58();
            if (pNode[2] != 0) {
                NNSi_FndFreeFromDefaultHeap((void *)pNode[2]);
            }
        }
        NNS_FndRemoveListObject(pQueue, pNode);
        if ((pNode[1] & 0x80000000) != 0) {
            pNode[1] = 0;
        } else if (pNode[1] != 0) {
            NNSi_FndFreeFromDefaultHeap((void *)pNode[1]);
        }
        if (pNode != 0) {
            NNSi_FndFreeFromDefaultHeap(pNode);
        }
        pNode = pNext;
    }

    pNode = (int *)NNS_FndGetNextListObject(pQueue + 3, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pQueue + 3, pNode);
        func_ov002_02052af4(pNode, 1);
        pNode = pNext;
    }
}
