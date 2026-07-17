/*
 * Apply a mode change to the actor, driving TWO UI bands (x4: ov049/068/086b/103).
 *
 * 0x2e re-inits (020b3f1c); 0x2f/0x30 share an arm that records which of the two the mode is
 * (block+0x118 = (mode == 0x30)) and rebinds the block at self+0x2cfc (020b3b2c). Both no-op
 * when the mode did not change. Mode 0x1b additionally selects the "kind 0" hand-off at the end.
 * The mode is then pushed to two consecutive UI bands (stride 0x164 for the view, 0x54 for the
 * state) -- translated (020519b0 -> 02052024) at/above 0x2e, straight (020521a4) below. Finally
 * either 020a384c hands the mode down (the normal path), or -- for 0x1b -- 020a46f8 + 020a3c78
 * run the hand-off and the mode cache at +0x6bc is written directly.
 *
 * Four things this one taught, on top of the ov034/ov046 template:
 *  - ARITY: 020a46f8 takes TWO arguments, not zero. Ghidra prints `func_0x020a46f8()` because
 *    the ROM sets r0/r1 ABOVE the branch -- they are shared with 020a384c on the other arm, so
 *    they do not look like this call's setup. The tree already had the real signature.
 *  - `loop = 2` inside the loop is NOT dead code, and that is why the ROM hoists `mov fp, #2`
 *    out of the loop: the 2 is used twice per iteration (assigned to `loop` AND passed as arg4),
 *    and because this is a LOOP, mwcc cannot prove `mode < 0x2e` is invariant, so the value
 *    reaches the next iteration's 020521a4 call. Written as a bare literal argument instead, the
 *    hoist disappears.
 *  - BOTH branches are written with the `>= 0x2e` / `!= -1` arm FIRST (ROM `blt`/`beq`); the
 *    obvious reading of each is inverted.
 *  - `i` must be DECLARED BEFORE `loop` and `ret`, which is the one place in this family where
 *    declaration order drives allocation: the ROM's r4/r5/r6 = i/loop/ret. Declared last, i lands
 *    in r6 and the whole callee-saved set rotates.
 */
extern void func_ov087_020b8dfc(int self);
extern void func_ov087_020b8a0c(int self, char *p);
extern void func_ov022_020a384c(int self, int mode);
extern void func_ov022_020a46f8(int self, int mode);
extern void func_ov022_020a3c78(int a, int b, int c, int d);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov087_020b8608(int self, int mode) {
    int p = self + 0x2cfc;
    int kind = -1;
    int arg = 0;
    int i;
    int loop;
    int ret;
    int pb;
    int pa;

    switch (mode) {
    case 0x2e:
        if (mode != *(int *)(self + 0x6bc)) { func_ov087_020b8dfc(self); }
        break;
    case 0x2f:
    case 0x30:
        *(int *)(p + 0x118) = (mode == 0x30);
        if (mode != *(int *)(self + 0x6bc)) { func_ov087_020b8a0c(self, (char *)p); }
        break;
    }
    if (mode == 0x1b) { kind = 0; arg = 0; }
    loop = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { loop = 1; }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    pb = self + 0x2c54;
    pa = self + 0xda8;
    for (i = 0; i < 2; i++) {
        if (mode >= 0x2e) {
            loop = 2;
            func_ov002_02052024((void *)pa, pb, mode + 1, loop, ret);
        } else {
            func_ov002_020521a4((void *)pa, pb, mode, loop);
        }
        pb += 0x54;
        pa += 0x164;
    }
    if (kind != -1) {
        func_ov022_020a46f8(self, mode);
        func_ov022_020a3c78(self, self + 0x2c2c, kind, arg);
        *(int *)(self + 0x6bc) = mode;
        return;
    }
    func_ov022_020a384c(self, mode);
}
