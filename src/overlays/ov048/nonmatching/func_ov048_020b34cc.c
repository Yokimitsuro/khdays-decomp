/*
 * func_ov048_020b34cc -- UNFINISHED. 208/208 bytes, 52/52 instructions.
 * x4 family (ov067_020b5ccc / ov086_020b83ac / ov103_020baa6c) -> worth 4.
 * A three-way callee-saved rotation and nothing else.
 *
 * WHAT IT DOES: switch the actor's animation set. The requested mode is an absolute id;
 * `mode - 0x2e` selects the handler. Modes 0x2e/0x2f re-init only if the mode actually
 * changed (+0x6bc caches the last one); 0x32/0x33 rebuild the shared channel block at
 * *data_ov048_020b4b80 + 0x2c2c, setting its flag word to 1 only for 0x33, and then report
 * mode 0x2f upward while remembering the REAL mode in +0x6bc. Modes 0x30/0x31 fall through
 * to the plain hand-off.
 *
 * SOLVED, keep it: `kind = mode - 0x2e` must be a LOCAL computed once. The ROM keeps it in
 * r2 from the head all the way to the 020b3bfc call, so it does double duty as the switch
 * selector AND that call's third argument. Spelling `mode - 0x2e` twice re-emits the `sub`
 * and costs 4 bytes.
 *
 * THE DIFF: which callee-saved register each of three values gets.
 *      ROM:   p=r4  id=r5   mode=r6  self=r7
 *      mine:  p=r4  mode=r5 self=r6  id=r7
 * Everything else -- opcodes, operands, the jump table, both predicated stores, all four
 * calls -- is identical.
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 208/208.
 *  2. Arity: 020b3a28 1 · 020b3e68 2 · 020b3bfc 4 (r2=kind and r3=p4 are both already live,
 *     which is why the ROM sets neither) · 020b3e7c 2 · ov022_020a384c 2. All match the
 *     ROM's register setup. param_3 is a real parameter but unused -- r2 is clobbered at
 *     +0x010.
 *  3. No constant is in the wrong register.
 *  4. Diff read back: 52 vs 52, three registers rotated.
 *
 * RULED OUT: 4 declaration arrangements (p/id/kind in every meaningful order, plus all
 * three as plain statements) -- ALL give byte-IDENTICAL output.
 *
 * ★ That negative is worth more than this function. It is the THIRD case today where
 * declaration order provably does not drive register allocation (with ov038_020b4234's
 * callee-saved permutation and ov000_02057dc4's spill slots). codegen-cracks.md's
 * decl-order entry is real -- it cracked TickTagTrackerNodes and others -- but it does not
 * reach a rotation among values that are ALL live across the whole function. Do not spend
 * another session re-permuting declarations on this class; the lever, if there is one, is
 * something that changes how many values are live or for how long.
 */
extern int data_ov048_020b4b80;

extern void func_ov048_020b3a28(int self);
extern void func_ov048_020b3e68(int self, int p);
extern void func_ov048_020b3bfc(int self, unsigned int *p, int kind, int d);
extern void func_ov048_020b3e7c(int self, int p);
extern void func_ov022_020a384c(int self, int mode);

void func_ov048_020b34cc(int self, int mode, int p3, int p4) {
    unsigned int *p = (unsigned int *)(data_ov048_020b4b80 + 0x2c2c);
    int id = -1;
    int kind = mode - 0x2e;

    switch (kind) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov048_020b3a28(self);
        }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov048_020b3e68(self, (int)p);
        }
        break;
    case 4:
    case 5:
        if (*(int *)(self + 0x6bc) != mode) {
            *p = 0;
            if (mode == 0x33) {
                *p = 1;
            }
            func_ov048_020b3bfc(self, p, kind, p4);
            func_ov048_020b3e7c(self, (int)p);
        }
        id = mode;
        mode = 0x2f;
        break;
    }
    func_ov022_020a384c(self, mode);
    if (id >= 0) {
        *(int *)(self + 0x6bc) = id;
    }
}
