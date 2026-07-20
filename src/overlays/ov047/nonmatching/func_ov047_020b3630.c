/* EQUIVALENT BUT NOT BYTE-EXACT -- 33 differing bytes.
 *
 * THIRD appearance of the SINGLE-EXIT residue: the ROM branches with `bne <end>` to one
 * shared `pop` (three times here) and mwcc emits a predicated `popne` at each guard.  The
 * other two:
 *   src/overlays/ov048/nonmatching/func_ov048_020b359c.c
 *   src/overlays/ov036/nonmatching/func_ov036_020b35f8.c
 *
 * USEFUL NEGATIVE (2026-07-19): rewriting it in a genuinely nested single-exit form --
 *   `if (a() == 0 && b() == 0) { ...; if (c() == 0) { ...; } }` -- leaves the `popne`s
 *   EXACTLY as they were, same 33 bytes, same three.  So it is not the shape of the control
 *   flow in C: mwcc turns any exit into a predicated epilogue when the epilogue is a single
 *   instruction.
 *
 * ADDED 2026-07-20: an explicit `goto end;` with a label before the closing brace, both with
 * and without a trailing `return;`, is also identical.  mwcc normalises it to the same thing.
 * So the class is now bounded on three separate spellings of the same idea, and the note's
 * conclusion stands: THIS IS NOT ATTACKABLE FROM THE SOURCE'S CONTROL FLOW.
 *
 * The one axis nobody has tried is making the epilogue LONGER than a single instruction, so
 * that predication is not available to mwcc -- but this function has no frame to grow, so it
 * would have to come from somewhere else.
 *
 * Secondary residue (same as in the ov036_020b35f8 park): in the final block the ROM loads
 * `self` into r0 LAST, immediately before the call, and orders r0/r1/r2 differently; mwcc
 * preloads `mov r0, r4` and shifts all three.
 *
 * Family of 4.  ARM mode.  Arity of all six callees verified.
 *
 * NOTE the 64-bit ORs below were already correct here before 2026-07-20, and they are the
 * construct that unblocked three OTHER families that day -- see codegen-cracks.md.  A file
 * that fails on one residue can still be the only place a construct is written down right.
 */
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern int func_02030788(void);
extern void func_ov022_020ad588(int self);

void func_ov047_020b3630(int self) {
    func_ov022_0209145c(*(int *)(self + 0x2000 + 0x644), func_ov022_02083f90());
    func_ov022_02091474(*(int *)(self + 0x2000 + 0x644));
    if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644)) != 0) return;
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x464) |= 0x10000;
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
    func_ov022_020ad588(self);
}
