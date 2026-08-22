/*
 * Ov002_CancelQueuedLoads - drop everything the load queue has not started.
 *
 * The same walk as the full teardown, but gentler: a node that is already
 * loading is left exactly where it is, because its buffer is in flight and
 * cannot be taken back, and the return value drops to zero to say the queue did
 * not come out empty. Every other pending node leaves the list, releases its key
 * - unless bit 31 tags it as an inline archive handle, which is only cleared -
 * and goes back to the heap.
 *
 * The done list is emptied unconditionally afterwards, through the same
 * disposal routine the teardown uses.
 *
 * THUMB. Returns non-zero when nothing was left behind.
 *
 * The skip branch advances the walk itself before continuing. That looks
 * redundant next to the advance at the bottom of the loop, but it is what the
 * ROM does: expressed as a for-loop increment, or as a bare continue, mwcc
 * shares one copy of the advance and the function comes out four bytes short.
 */

extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov002_02052af4(int *pNode, int nFlag);

extern int data_ov002_0207f608;   /* the pending list, done list at +0xc */

int func_ov002_02052b44(void)
{
    int *pNode;
    int *pQueue;
    int *pNext;
    int bDrained;

    bDrained = 1;
    pQueue = *(int **)&data_ov002_0207f608;
    pNode = (int *)NNS_FndGetNextListObject(pQueue, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pQueue, pNode);
        if (pNode[0] == 1) {
            pNode = pNext;
            bDrained = 0;
            continue;
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
    return bDrained;
}
