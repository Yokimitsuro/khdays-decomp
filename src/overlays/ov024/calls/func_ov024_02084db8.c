/* MobiClip player: tick both stream slots and latch "all done". Runs func_ov024_02084c24 on the
 * slot at +8 and the one at +0xc of the stream block; when BOTH report ready, the completion
 * flag at +0xe4 of the player block is set.
 *
 * It RETURNS the AND, and that is what makes it match: the original emits `ands r0,r4,r0` and
 * leaves the result in r0 all the way to the pop, which a void function has no reason to do --
 * mwcc writes `tst r4,r0` and the three following words differ only in the register numbering
 * carried from that choice. Same signal as func_ov008_02051168: if the original never clobbers
 * r0 after computing something, the something is the return value. */
extern unsigned int func_ov024_02084c24(int *slot);
extern int data_ov024_02093a2c[];
extern int data_ov024_0209ba48[];

unsigned int func_ov024_02084db8(void) {
    unsigned int lo;
    unsigned int hi;

    lo = func_ov024_02084c24((int *)data_ov024_02093a2c[2]);
    hi = func_ov024_02084c24((int *)data_ov024_02093a2c[3]);
    lo = lo & hi;
    if (lo != 0) {
        data_ov024_0209ba48[0x39] = 1;
    }
    return lo;
}
