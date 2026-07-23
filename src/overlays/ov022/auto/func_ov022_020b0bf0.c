/* func_ov022_020b0bf0 -- is arg1 inside the actor's active window?
 * The window is the [lo, hi) pair at +0x10/+0x14 of the descriptor reached through
 * obj+0x470; a `hi` of -0x1000 means "no upper bound" and is promoted to INT_MAX.
 *
 * Both bounds are read into locals BEFORE the -0x1000 test (the ROM loads them back to back),
 * and the test is a nested `if` with a single exit: an early `return r` makes mwcc emit a
 * redundant `movgt r0,#0` before the predicated return, because it does not track that the
 * result register already holds the initialiser. The two constants coming out as
 * `sub rN, r0, #imm` off the zero in the result register is mwcc's own doing once `r` is
 * initialised at the top -- it needs no coaxing. */
int func_ov022_020b0bf0(int arg0, int arg1) {
    int r = 0;
    int base = *(int *)(*(int *)(arg0 + 0x470) + 0x14);
    int hi = *(int *)(base + 0x14);
    int lo = *(int *)(base + 0x10);

    if (hi == -0x1000) hi = 0x7fffffff;
    if (lo <= arg1) {
        if (arg1 < hi) r = 1;
    }
    return r;
}
