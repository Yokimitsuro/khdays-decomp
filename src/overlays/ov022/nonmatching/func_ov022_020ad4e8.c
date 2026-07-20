/*
 * [nonmatching: predicate-vs-branch -- 140B vs 160B]
 *
 * IMPROVED 2026-07-20: the guard on +0x464 is a 64-BIT AND, not a 32-bit one.  With
 * `*(long long *)(arg0 + 0x464) & 0x20000000` the function is the right SIZE (160) instead
 * of 20 bytes short, and the residue drops to the register/predication difference the note
 * below describes.  The C now carries that fix.
 *
 * Still open, and the note's original diagnosis stands for it: mwcc predicates the abs-delta
 * block (rsbhi/lslhi/lsrhi) and pushes two extra registers where the ROM branches it out of
 * line with a `movle` on the fall-through.  An explicit if/else in either direction is not
 * better (27 lines one way, 4 bytes over the other).
 *
 * Clamps a wrapped 16-bit angle delta toward a limit. mwcc predicates the
 * abs-delta block (rsbhi/lslhi/lsrhi) and the multi-&& guards inline where the
 * original branches them out of line (20B shorter). Equivalent; left uncarved.
 */
unsigned int func_ov022_020ad4e8(int arg0, unsigned int arg1) {
    unsigned int base = *(unsigned int *)(arg0 + 0x488);
    unsigned int d;
    unsigned int ad;
    int lim;
    if ((int)arg1 < 0) return 0xffffffff;
    if (arg1 == base) return base;
    d = arg1 - base & 0xffff;
    ad = d;
    if (0x8000 < d) ad = 0x10000 - d & 0xffff;
    lim = *(int *)(arg0 + 0x4b0);
    if ((int)ad <= lim) return arg1;
    if ((*(unsigned int *)(arg0 + 0x24) & 4) != 0 &&
        (*(long long *)(arg0 + 0x464) & 0x20000000) == 0 && 0x7000 < ad) {
        return arg1;
    }
    if (0x8000 < d) lim = -lim;
    return base + lim & 0xffff;
}
