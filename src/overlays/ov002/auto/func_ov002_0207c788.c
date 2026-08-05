/*
 * func_ov002_0207c788 - packed hi/lo mask-match predicate (ARM, reloc-free).
 *
 * param_1 packs two 16-bit fields: hi (bits 16-31) and lo (bits 0-15). The value passes when:
 *   - hi is the wildcard 0xffff, or it shares at least one bit with the hi mask param_2; AND
 *   - lo is the wildcard 0x3fff, or it shares at least one bit with the lo mask param_3.
 * Returns 1 on a match, 0 otherwise.
 *
 * The two failure exits share one `return 0` via an explicit goto so mwcc emits a single tail
 * (branch, not predicated), matching the ROM; the hi guard is written as one `&&` so the wildcard
 * test and the mask test become the cmp/beq + tst/beq pair.
 */
int func_ov002_0207c788(unsigned int param_1, int param_2, int param_3)
{
    unsigned short hi = (unsigned short)(param_1 >> 16);
    unsigned short lo = (unsigned short)param_1;
    if (hi != 0xffff && (param_2 & hi) == 0) goto ret0;
    if (lo == 0x3fff) return 1;
    if ((lo & param_3) != 0) return 1;
ret0:
    return 0;
}
