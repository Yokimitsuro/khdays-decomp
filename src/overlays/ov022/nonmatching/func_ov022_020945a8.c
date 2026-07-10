/* NONMATCHING: dense 64-bit predicate. Every flag test is a 64-bit mask test on
 * the u64 at p+0x464 or *p (paired and/cmp/cmpeq form); written as 32-bit C it
 * comes out ~64B short, and a naive 64-bit rewrite comes out ~28B long because
 * the original FUSES several conditions into single combined tests --
 * `(f464_hi & 0x90) != 0 || (f464_lo & mask) != 0` as one `cmp;cmpeq`, and it
 * builds the conditional low mask (`mask &= ~0x80` when *p's high bit 4 is set)
 * via register arithmetic (`sub;sub;and;and`) rather than a branch. Reproducing
 * that exact mask-combining codegen is an open derivation. Semantics below (the
 * 32-bit view, which is equivalent since the paired high masks are 0) are exact. */
extern int func_02030694(void);

int func_ov022_020945a8(int obj) {
    unsigned int *p = *(unsigned int **)(obj + 0x328);
    unsigned int f119, mask;
    int r;
    if (func_02030694() == 0) return 0;
    f119 = p[0x119];
    r = *(unsigned short *)((char *)p + 0x12) == 0;
    if ((f119 & 0x8000) != 0 || (f119 & 0x100) != 0) r = 1;
    mask = 0x20003690;
    if ((p[1] & 0x10) != 0) mask &= ~0x80;
    if ((p[0x11a] & 0x90) != 0 || (f119 & mask) != 0) r = 1;
    if ((p[1] & 2) != 0 || (*p & 0x108a2904) != 0) r = 1;
    return r;
}
