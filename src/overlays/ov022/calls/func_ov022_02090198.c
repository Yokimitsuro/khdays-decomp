/* Tears down the fifteen 4-byte slots starting at `slot`: for each one that still owns a
 * block at +0x18, runs the matching per-slot destructor from data_ov022_020b2ad4 and then
 * releases the block (func_0202a7dc on +8, then the heap free).
 *
 * Two things this was parked on, both real:
 *  - the destructor RECEIVES the block: the ROM's `blx r1` runs with r0 still holding the
 *    value loaded at +0x18, which is only possible if the callback takes it as an argument.
 *    That is also what stops mwcc from colouring the function pointer into r0.
 *  - `i` must be declared BEFORE `tbl` (r6/r4 in the ROM). */
extern void func_0202a7dc(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2ad4;

void func_ov022_02090198(unsigned short *slot) {
    int i;
    int *tbl;
    void (*fn)(int);
    int blk;
    if ((*slot & 1) != 0) {
        tbl = &data_ov022_020b2ad4;
        i = 0;
        do {
            blk = *(int *)((char *)slot + 0x18);
            if (blk != 0) {
                fn = (void (*)(int))*tbl;
                if (fn != 0) {
                    fn(blk);
                }
                func_0202a7dc(*(int *)((char *)slot + 0x18) + 8);
                NNSi_FndFreeFromDefaultHeap(*(int *)((char *)slot + 0x18));
            }
            i = i + 1;
            slot = slot + 2;
            tbl = tbl + 1;
        } while (i < 0xf);
    }
}
