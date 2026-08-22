/*
 * Ov002_WriteMapRow - put a row of map data where the destination wants it.
 *
 * Three ways to land, tried in order. If the destination id is a tracked slot
 * and the item resource table has a buffer for it, the row is copied there. If
 * not, the slot's own buffer in the context takes it. Either way the slot is
 * marked dirty so the flush pushes it out. Only when neither buffer exists does
 * the row go straight to the graphics queue.
 *
 * Careful: the fallback indexes the context with the slot even when there is no
 * slot, so a -1 walks back into the word at +0x54. That word is the item
 * resource table's head and holds -1, which is not null, so the copy is
 * attempted against it. That is what the original does; the callers evidently
 * never reach it with an untracked id.
 *
 * ARM. Always returns 1.
 */

extern int func_ov002_02052d2c(int nDest);
extern void GFXi_EnqueueCommand(int nDest, int nOffset, void *pRow,
                                unsigned int nBytes);
extern void MI_CpuCopy8(void *pSrc, void *pDst, unsigned int nSize);

extern int data_ov002_0207f60c;

int func_ov002_02053c18(int nDest, int nOffset, void *pRow, unsigned int nBytes)
{
    unsigned char *pUi;
    int nSlot;
    int nTarget;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    nSlot = func_ov002_02052d2c(nDest);

    if (nSlot == -1
        || (nTarget = *(int *)(*(int *)(pUi + 0x94) + nSlot * 4 + 4)) == 0) {
        nTarget = ((int *)(pUi + 0x58))[nSlot];
        if (nTarget == 0) {
            GFXi_EnqueueCommand(nDest, nOffset, pRow, nBytes);
        } else {
            MI_CpuCopy8(pRow, (void *)(nTarget + nOffset), nBytes);
            pUi[0x52] = pUi[0x52] | 1 << nSlot;
        }
    } else {
        MI_CpuCopy8(pRow, (void *)(nTarget + nOffset), nBytes);
        pUi[0x52] = pUi[0x52] | 1 << nSlot;
    }
    return 1;
}
