/* EQUIVALENT BUT NOT BYTE-EXACT -- 8 bytes, 2026-07-18.
 *
 * IDENTICAL residue to src/overlays/ov033/nonmatching/func_ov033_020b350c.c -- read that note.
 * The two functions differ only in the pool symbol and one constant (0xca vs 0xd7), and both
 * land on the same two swapped instructions: the ROM builds the r3 argument before loading the
 * pool address into r0, mwcc always loads the pool first.
 *
 * Confirmed by compiling the ov033 form with the two constants substituted: 8 bytes, same place.
 * So the residue tracks the SHAPE, not this instance -- and the prize is now 8 functions
 * (two 4-member families). The corpus search that found 0 precedents in ~12,900 matched
 * functions is written up in the ov033 note; do not redo it per-instance. */

extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(int a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov041_020b4c9c;

void func_ov041_020b3698(int self) {
    char *blk = (char *)(self + 0x2f8 + 0x2000);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(self + 9), 1);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)&data_ov041_020b4c9c,
                                                *(unsigned char *)(self + 9), 0,
                                                *(int *)(self + 0x20) + 4);
    func_ov022_020b1cec(self + 0xda0, 0xd7);
    *(unsigned char *)(blk + 0x334) |= 9;
}
