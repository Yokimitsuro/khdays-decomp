/*
 * Ov002_PushMapSnapshot - set the current maps aside under a key.
 *
 * Takes a fresh 0x40-byte node, stamps the caller's key into it, and for each
 * of the first three map slots copies the slot's buffer into a new one of its
 * own, remembers the slot's enable flag, clears the live buffer and marks the
 * slot dirty so the flush pushes the cleared map out. The node goes on the
 * front of the list at +0x98, so the most recent snapshot is found first.
 *
 * ARM. Both arrays are reached by index rather than by adding the offset into
 * the pointer, which keeps the ROM's base-plus-scaled-index adds instead of a
 * pair of induction variables, and the counter is declared before the node.
 */

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int nSize, int nAlign);
extern void MIi_CpuCopy16(void *pSrc, void *pDst, unsigned int nSize);
extern void MIi_CpuClear16(int nValue, void *pDst, unsigned int nSize);
extern void NNS_FndPrependListObject(void *pList, void *pObj);

extern int data_ov002_0207f60c;

void func_ov002_02053938(int nKey)
{
    unsigned char *pUi;
    int i;
    unsigned char *pNode;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    pNode = (unsigned char *)NNSi_FndAllocFromDefaultExpHeap(0x40);
    MI_CpuFill8(pNode, 0, 0x40);
    *(int *)pNode = nKey;

    for (i = 0; i <= 2; i++) {
        ((int *)(pNode + 0x1c))[i] = ((int *)(pUi + 0x70))[i];
        ((int *)(pNode + 4))[i] =
            (int)NNS_FndAllocFromDefaultExpHeapEx(0x800, 2);
        MIi_CpuCopy16(((void **)(pUi + 0x58))[i],
                      ((void **)(pNode + 4))[i], 0x800);
        MIi_CpuClear16(0, ((void **)(pUi + 0x58))[i], 0x800);
        pUi[0x52] = pUi[0x52] | 1 << i;
    }

    NNS_FndPrependListObject(pUi + 0x98, pNode);
}
