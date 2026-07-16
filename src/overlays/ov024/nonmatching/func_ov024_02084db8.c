/* NONMATCHING: 60/60 bytes, 4 words -- all downstream of one canonicalisation. The ROM emits
 * `ands r0,r4,r0` (keeping the result, though nothing reads it) where mwcc 3.0/139 emits `tst
 * r4,r0`; the three following words differ only in register numbering carried from that choice.
 * Materialising the AND into a variable first does not change it -- same family as ov024
 * 02083414's branch-sense canonicalisation.
 *
 * func_ov024_02084db8 -- MobiClip player: tick both stream slots and latch "all done".
 * Runs func_ov024_02084c24 on the slot at +8 and the one at +0xc of the stream block; when
 * BOTH report ready the completion flag at +0xe4 of the player block is set. */
extern unsigned int func_ov024_02084c24(int *slot);
extern int data_ov024_02093a2c;
extern int data_ov024_0209ba48;

void func_ov024_02084db8(void) {
    unsigned int lo;
    unsigned int hi;

    lo = func_ov024_02084c24(*(int **)((char *)&data_ov024_02093a2c + 8));
    hi = func_ov024_02084c24(*(int **)((char *)&data_ov024_02093a2c + 0xc));
    lo = lo & hi;
    if (lo != 0) {
        *(int *)((char *)&data_ov024_0209ba48 + 0xe4) = 1;
    }
}
