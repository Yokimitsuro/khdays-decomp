/* NONMATCHING -- 88/88 B, 7 differing bytes: a register permutation plus one scheduling
 * difference (the ROM computes `row + off` before the call, mwcc after). Head of a 4-member
 * family.
 *
 * SOLVED here -- do NOT rediscover:
 *  - the shared base must be a `char *` (`(char *)self + 0x2000`). As an `int` it is 4 B long,
 *    and without it 8 B long: mwcc then splits 0x63c into `add #0x23c` + `ldr [#0x400]`.
 *  - declaration order matters and was swept: 60 legal permutations, best three give 7 bytes,
 *    the base ordering used here (i, p, base, obj, off) among them; the worst give 15.
 *
 * Ruled out: hoisting the destination `int *dst` above the call (14 bytes, worse).
 *
 * ROUND 2 (2026-07-18), on the twin ov049_020b406c and therefore valid for both:
 * the residue is a pure r7 <-> sb swap -- `p` and the `row + off` temp trade registers.
 * Swept 60 MORE declaration permutations with the loop temp lifted to function scope: all 7.
 * Also ruled out: computing `row + off` into an int before the call, folding +0x130 into it
 * (14, worse), two separate locals, and `do {...} while (1)` with an explicit break.
 * find_insn.py for the 0x1c8 stride returns 33 matched functions but none has this shape
 * (a call inside the loop whose result is stored through a pre-computed address), so the
 * corpus does not answer it either.
 *
 *
 * SCOPE (2026-07-18, round 3): the shape turns out to span FOUR families, not two --
 * ov035_020b4270 (loop count 2), ov039_020b4404 (6), ov047_020b3b40 and ov049_020b406c (10).
 * The same C template lands on exactly 7 bytes in all four, which rules out allocator luck
 * and raises the prize to ~16 functions. See the ov035 park note for the extra forms tried.
 *
 * All measured with tools/bytedist.py. */
extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov047_020b4380;

void func_ov047_020b3b40(int self) {
    int i = 0;
    int p = *(int *)&data_ov047_020b4380 + 0x2d78;
    char *base = (char *)self + 0x2000;
    int obj = *(int *)(base + 0x644);
    int off = 0;

    do {
        int row = *(int *)(obj + 0xc);
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), p);
        i = i + 1;
        *(int *)(row + off + 0x130) = p;
        off = off + 0x1c8;
        p = p + 0x24;
    } while (i < 10);
}
