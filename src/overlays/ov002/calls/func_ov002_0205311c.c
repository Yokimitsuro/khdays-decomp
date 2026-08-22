/*
 * Ov002_FlushDirtyMaps - hand every dirtied map buffer to the graphics queue.
 *
 * The mask at +0x52 has one bit per map slot, set by the map writer whenever it
 * copies rows into that slot's buffer. This walks the six slots and enqueues a
 * 0x800-byte transfer for each dirtied one, from the slot's buffer to the
 * destination the table names, then clears the mask.
 *
 * A mask of 0xff means every slot at once, which is not a real set of slots but
 * a "nothing to do" marker: the walk is skipped and only the clear happens.
 *
 * ARM. Two levers: the slot's buffer is reached as an array index rather
 * than by adding the offset into the pointer, which is what keeps the ROM's
 * base-plus-scaled-index load instead of a second induction variable; and the
 * destination table is walked with its own pointer, declared between the
 * counter and the context, which is what colours the three the ROM's way.
 */

extern void GFXi_EnqueueCommand(int nDest, int nOffset, int nSource,
                                int nBytes);

extern int data_ov002_0207f60c;
extern unsigned char data_ov002_0207db68[];

void func_ov002_0205311c(void)
{
    int i;
    unsigned char *pTable;
    unsigned char *pUi;

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    if (pUi[0x52] != 0xff) {
        pTable = data_ov002_0207db68;
        for (i = 0; i < 6; i++) {
            if ((pUi[0x52] & 1 << i) != 0) {
                GFXi_EnqueueCommand(*pTable, 0, ((int *)(pUi + 0x58))[i], 0x800);
            }
            pTable++;
        }
    }
    pUi[0x52] = 0;
}
