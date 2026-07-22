/* Fill the three-word request block at +0x9740 of the ov008 context -- the same block
 * func_ov008_02051198 hands out the address of. Both call sites arm it with (0x1e, 1, 1)
 * right before triggering cue 0x35bd, so the first word is a duration in frames.
 *
 * It RETURNS its first argument, and that is what makes it match: with a void return
 * mwcc frees r0 after the first store and reuses it for the remaining two base pointers,
 * where the original leaves r0 untouched to the very last instruction and reaches for r3
 * and r1 instead. Nothing else about the function explains that -- an unused-looking
 * return value is a real, checkable signal, not decoration. */
extern int data_ov025_020b5744;

int func_ov025_02084f78(int durationFrames, int b, int c) {
    *(int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9740) = durationFrames;
    *(int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9744) = b;
    *(int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9748) = c;
    return durationFrames;
}
