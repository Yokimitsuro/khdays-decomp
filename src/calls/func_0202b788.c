/* Tear down the block held by data_0204c208 and drop the pointer.
 *
 * The trailing scratch buffer is released first, then every one of the 64
 * fixed entries that is active (bit 2 of its flag byte) but not already
 * finished (bit 6) is handed to SNDi_ProcessEntry by index.  The `count`
 * registered entries are then released one by one: func_0202b064 winds the
 * entry's own record down and the heap block it owns is freed.  The count is
 * re-read every iteration because func_0202b064 can lower it.  Finally the
 * whole block goes back to the heap.  Returns 1 even when nothing was
 * allocated.
 *
 * Layout is pinned by func_0202b820, which registers entry `index` by writing
 * its record at +4+index*8 and its block at +0x44+index*4, and by the entry
 * array itself: 0xc4 + 64 * 0x184 == 0x61c4, exactly where `buffer` sits.
 *
 * The second loop has to be written as ARRAY INDEXING, not as two hand-walked
 * pointers: mwcc's strength reduction is what produces the ROM's running
 * record and block pointers, and writing those pointers out by hand colours
 * the loop counter into r4 instead of r6.  THUMB.
 */

#pragma thumb on

typedef struct Manager {
    unsigned int count;               /* 0x0000 */
    unsigned short records[8][4];     /* 0x0004 */
    void *blocks[8];                  /* 0x0044 */
    char field_64[0x60];              /* 0x0064 */
    char entries[64][0x184];          /* 0x00c4 */
    void *buffer;                     /* 0x61c4 */
} Manager;

extern Manager *data_0204c208;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern int SNDi_ProcessEntry(int nIndex);
extern void func_0202b064(unsigned short *pRecord);

int func_0202b788(void)
{
    Manager *mgr;
    int i;
    char *entry;
    unsigned int j;

    mgr = data_0204c208;
    if (mgr != 0) {
        if (mgr->buffer != 0) {
            NNSi_FndFreeFromDefaultHeap(mgr->buffer);
            mgr->buffer = 0;
        }

        entry = (char *)mgr;
        i = 0;
        entry += 0xc4;
        do {
            unsigned char flags = *(unsigned char *)(entry + 8);
            if ((flags & 4) != 0 && (flags & 0x40) == 0) {
                SNDi_ProcessEntry((unsigned short)i);
            }
            i++;
            entry += 0x184;
        } while (i < 0x40);

        for (j = 0; j < mgr->count; j++) {
            func_0202b064(mgr->records[j]);
            NNSi_FndFreeFromDefaultHeap(mgr->blocks[j]);
        }

        NNSi_FndFreeFromDefaultHeap(mgr);
        data_0204c208 = 0;
    }
    return 1;
}
