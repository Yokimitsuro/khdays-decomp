/*
 * Ov002_PopMapSnapshot - put the newest set-aside maps back.
 *
 * Does nothing when nothing was set aside. Otherwise, if the item resource
 * table was pointing into the snapshot it takes it back to the context's own
 * +0x54 first, then for each of the three slots the snapshot actually holds it
 * restores the enable flag, copies the saved map back over the live buffer,
 * releases the saved copy and marks the slot dirty. The node then leaves the
 * list and is freed.
 *
 * ARM. The arrays are reached by index rather than by adding the offset into
 * the pointer, which keeps the ROM's base-plus-scaled-index adds, and the
 * counter is declared first so the three locals take the ROM's registers.
 */

extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void MIi_CpuCopy16(void *pSrc, void *pDst, unsigned int nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);

extern int data_ov002_0207f60c;

void func_ov002_02053a64(void)
{
    int i;
    unsigned char *pNode;
    unsigned char *pUi;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    pNode = (unsigned char *)NNS_FndGetNextListObject(pUi + 0x98, 0);
    if (pNode == 0) {
        return;
    }

    if (*(int *)(pUi + 0x94) == (int)pNode) {
        *(int *)(pUi + 0x94) = (int)(pUi + 0x54);
    }

    for (i = 0; i <= 2; i++) {
        if (((void **)(pNode + 4))[i] != 0) {
            ((int *)(pUi + 0x70))[i] = ((int *)(pNode + 0x1c))[i];
            MIi_CpuCopy16(((void **)(pNode + 4))[i],
                          ((void **)(pUi + 0x58))[i], 0x800);
            if (((void **)(pNode + 4))[i] != 0) {
                NNSi_FndFreeFromDefaultHeap(((void **)(pNode + 4))[i]);
                ((void **)(pNode + 4))[i] = 0;
            }
            pUi[0x52] = pUi[0x52] | 1 << i;
        }
    }

    NNS_FndRemoveListObject(pUi + 0x98, pNode);
    if (pNode != 0) {
        NNSi_FndFreeFromDefaultHeap(pNode);
    }
}
