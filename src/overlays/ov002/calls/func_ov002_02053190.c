/*
 * Ov002_AgeDeferredFrees - retire the deferred-free list one frame older.
 *
 * Every node on the list at +0xb0 carries an age byte. Each call ages every
 * node by one, and a node that has been through two frames is taken off the
 * list, has its held block released and cleared, and is itself freed. Two
 * frames is the point of the list: whatever the block was, the hardware may
 * still have been reading it during the frame it was dropped.
 *
 * ARM. Two levers: the age is incremented and tested in one expression, which
 * is what gives the ROM's masked compare against the unmasked value it stores
 * back; and the two walk pointers are declared before the context, which is
 * what colours the three the ROM's way.
 */

extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

extern int data_ov002_0207f60c;

void func_ov002_02053190(void)
{
    int *pNode;
    int *pNext;
    unsigned char *pUi;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    pNode = (int *)NNS_FndGetNextListObject(pUi + 0xb0, 0);
    if (pNode == 0) {
        return;
    }

    do {
        pNext = (int *)NNS_FndGetNextListObject(pUi + 0xb0, pNode);
        if (++*((unsigned char *)pNode + 4) >= 2) {
            NNS_FndRemoveListObject(pUi + 0xb0, pNode);
            if (pNode[0] != 0) {
                NNSi_FndFreeFromDefaultHeap((void *)pNode[0]);
                pNode[0] = 0;
            }
            if (pNode != 0) {
                NNSi_FndFreeFromDefaultHeap(pNode);
            }
        }
        pNode = pNext;
    } while (pNext != 0);
}
