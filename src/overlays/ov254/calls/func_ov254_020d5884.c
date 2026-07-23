/* func_ov254_020d5884 -- reset both AI slots and re-arm the reaction.
 * For each of the two slots in the pointer array at *node+0x384, clear the four state bytes at
 * +0xa8/+0xa9/+0xaa/+0xac, then hand the action at self+0x20 on to func_ov254_020d58d4.
 *
 * Two things make this match, and both are about how the zero is spelled:
 *
 * 1. ONE four-long assignment chain, not four statements. mwcc evaluates it right to left, so
 *    the innermost store (+0xa9) is emitted first and takes the plain `int` zero, while the
 *    chain's *value* is `unsigned char` -- that is where the ROM's `and r1, r2, #0xff` comes
 *    from, and the remaining three stores use the masked copy. Four separate `= 0` statements
 *    collapse to a single materialised zero reused everywhere, which is one instruction shorter
 *    than the ROM. The chain also fixes the store ORDER (a9, ac, aa, a8) for free.
 *    The zero itself is the loop counter's initial value (`mov r2, lr` in the preheader).
 *
 * 2. The +0x384 displacement folded INTO the subscript (`[i + 0xe1]`, 0x384/4). Written flat as
 *    `*(int *)(*node + i * 4 + 0x384)` mwcc adds the constant to the base first and puts the
 *    scaled index in the load; the ROM does the opposite -- scaled index into the base, constant
 *    as the load's immediate. Same rule as the loop strength-reduction crack. */
extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov254_020d58d4(int self);

void func_ov254_020d5884(int self) {
    int *node = *(int **)(self + 4);
    int i;

    for (i = 0; i < 2; i++) {
        unsigned char *e = (unsigned char *)((int *)*node)[i + 0xe1];
        e[0xa8] = e[0xaa] = e[0xac] = e[0xa9] = 0;
    }

    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov254_020d58d4);
}
