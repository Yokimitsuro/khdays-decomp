/*
 * Ov002_DestroyUiContext - tear the overlay's UI context down.
 *
 * Turns the hardware blending off first, then gives back everything the
 * constructor took: the six map buffers, and every node on the list at +0x98
 * along with the six blocks each of those holds. The script runner at +0xdc is
 * shut down through its own four entry points, and the global slot is cleared
 * so nothing can reach the object afterwards.
 *
 * THUMB. Three levers, all about keeping mwcc from adding work: each block is
 * loaded into a temporary and tested there rather than loaded twice, both
 * loops initialise their counter before their walk pointer, and the
 * declaration order is what colours the eight locals the ROM's way.
 */

typedef volatile unsigned short vu16;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void func_ov002_02053260(void);
extern void func_ov002_02053220(void);
extern void func_ov002_02054714(void *pRunner);
extern void func_ov002_020545e4(void *pRunner, int nFlag);
extern void func_ov002_020547b8(void *pRunner);
extern void func_ov002_02054458(void *pRunner);

extern int data_ov002_0207f60c;

void func_ov002_020533dc(void)
{
    int *pNode;
    unsigned char *pUi;
    unsigned char *pSlot;
    int i;
    int *pEntry;
    int j;
    void *pBlock;
    int *pNext;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    *(vu16 *)0x04000050 = 0;

    pSlot = pUi;
    for (i = 0; i < 6; i++) {
        pBlock = *(void **)(pSlot + 0x58);
        if (pBlock != 0) {
            NNSi_FndFreeFromDefaultHeap(pBlock);
        }
        pSlot = pSlot + 4;
    }

    pNode = (int *)NNS_FndGetNextListObject(pUi + 0x98, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pUi + 0x98, pNode);
        for (j = 0, pEntry = pNode; j < 6; j++) {
            pBlock = (void *)pEntry[1];
            if (pBlock != 0) {
                NNSi_FndFreeFromDefaultHeap(pBlock);
            }
            pEntry = pEntry + 1;
        }
        if (pNode != 0) {
            NNSi_FndFreeFromDefaultHeap(pNode);
        }
        pNode = pNext;
    }

    func_ov002_02053260();
    func_ov002_02053220();
    func_ov002_02054714(pUi + 0xdc);
    func_ov002_020545e4(pUi + 0xdc, 0);
    func_ov002_020547b8(pUi + 0xdc);
    func_ov002_02054458(pUi + 0xdc);
    *(int *)&data_ov002_0207f60c = 0;
}
