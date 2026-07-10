/*
 * [nonmatching: call-result register-coloring tie — 36B, structurally byte-identical]
 *
 * Calls func_ov002_02050cf4 four times over the root heap at stride 0x30, then
 * clears data_ov022_020b2e74.
 *
 * The original colors the NNSi_FndGetCurrentRootHeap() result (the walking base)
 * into r5 and the loop counter into r4 (`adds r5,r0,#0; movs r4,#0`); mwcc
 * 3.0/139 parks the call result in r4 (the lowest free callee-saved reg, moved
 * straight from r0) and the counter in r5 — the opposite pairing. Identical
 * instruction sequence, only r4<->r5 swap. Neither declaration order, signedness
 * (int/unsigned), nor loop form (do-while / for) steers the call result onto r5,
 * so this is left uncarved (byte-exact in the blob). The sibling 020831dc, whose
 * walking base comes from a deref (not a call), matches with this same shape.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02050cf4(int arg0);
extern int data_ov022_020b2e74;

void func_ov022_0208694c(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    int i = 0;
    do {
        func_ov002_02050cf4(h);
        i = i + 1;
        h = h + 0x30;
    } while (i < 4);
    *(int *)&data_ov022_020b2e74 = 0;
}
