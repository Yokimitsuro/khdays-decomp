/* Build the overlay's entry table from the message database.
 *
 * The block names some ids up front; the rest of the fixed range 2..11 is
 * appended in order, skipping anything already named. The resulting count sizes
 * one allocation of fixed-width entries, each of which takes the record's text,
 * its own id, and one word from the record.
 *
 * The only caller forwards its own argument, but this routine does not consume
 * it: the root-pointer load overwrites r0 before any use.
 */

/* Codegen notes, all measured. Both counted loops are guarded by comparing the
 * int counter against the byte field rather than testing the field against
 * zero: mwcc knows a u8 cannot be negative and folds `field > 0` into an
 * equality branch where the ROM has a signed one. The running total is a short,
 * which is what emits the lsls/asrs pair after each increment. The first and
 * second loops need distinct walkers, while the same int counter is reused by
 * the first, outer, and final loops. The four statements ending the first loop
 * are ordered walker, counter, total, source, which puts the sign-extend in the
 * ROM's slot.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 aText[0x20];                    /* +0x00 */
    short nId;                          /* +0x40 */
    short nValue;                       /* +0x42 */
} Ov002EntryRow;

typedef struct {
    Ov002EntryRow *pRows;               /* +0x00 */
    u8 pad0004;
    u8 nCount;                          /* +0x05 */
    u8 nNamed;                          /* +0x06 */
    u8 pad0007;
    short aNamed[1];                    /* +0x08 */
} Ov002EntryTable;

typedef struct {
    char pad0000[0x8d14];
    Ov002EntryTable keyEntryTable;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void MI_CpuFill8(void *pOut, int nValue, unsigned int nSize);
extern void func_02034150(int nSlot, int nFont);
extern void func_020342e8(int *pOut, int nSlot, int nKey, int nFont);
extern int func_02034258(int nSlot);
extern void func_020343cc(int *pRecord);
extern void func_020200e4(u16 *pOut, const u16 *pIn);

int func_ov002_0206cf88(void)
{
    short aIds[120];
    int nRecord;
    int i;
    int j;
    short nCount;
    int bFound;
    Ov002EntryTable *pSrc;
    short *pRead;
    short *pWalk;
    short *pFill;
    int nOffset;
    short *pAppend;
    Ov002EntryTable *pTable;

    nCount = 0;
    pTable = &data_ov002_0207fa00->keyEntryTable;
    i = 0;
    if (i < pTable->nNamed) {
        pSrc = pTable;
        pFill = aIds;
        do {
            *pFill = pSrc->aNamed[0];
            pFill++;
            i++;
            nCount++;
            pSrc = (Ov002EntryTable *)((char *)pSrc + 2);
        } while (i < pTable->nNamed);
    }

    pAppend = aIds + nCount;
    i = 2;
    do {
        bFound = 0;
        j = 0;
        if (j < nCount) {
            pWalk = aIds;
            do {
                if (i == *pWalk) {
                    bFound = 1;
                    break;
                }
                j++;
                pWalk++;
            } while (j < nCount);
        }
        if (bFound == 0) {
            *pAppend = (short)i;
            pAppend++;
            nCount++;
        }
        i++;
    } while (i <= 0xb);

    pTable->nCount = (u8)nCount;
    pTable->pRows = (Ov002EntryRow *)
        NNSi_FndAllocFromDefaultExpHeap(pTable->nCount * 0x44);
    MI_CpuFill8(pTable->pRows, 0, pTable->nCount * 0x44);
    nRecord = 0;
    func_02034150(0x15, 2);

    i = 0;
    if (i < pTable->nCount) {
        pRead = aIds;
        nOffset = 0;
        do {
            func_020342e8(&nRecord, 0x15, *pRead, 2);
            func_020200e4((u16 *)((char *)pTable->pRows + nOffset),
                          *(u16 **)(nRecord + 0xc));
            *(short *)((char *)pTable->pRows + nOffset + 0x42) =
                (short)*(int *)(nRecord + 0x1c);
            *(short *)((char *)pTable->pRows + nOffset + 0x40) = *pRead;
            func_020343cc(&nRecord);
            i++;
            pRead++;
            nOffset += 0x44;
        } while (i < pTable->nCount);
    }
    return func_02034258(0x15);
}
