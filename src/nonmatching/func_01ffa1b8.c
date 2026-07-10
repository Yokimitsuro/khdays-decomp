/* NONMATCHING: predicate-vs-branch tie, 4 bytes short. The short (3-instr)
 * flags&4 block gets predicated by mwcc (ldrne/orrne/strne + bxne) where the
 * original branches around it (beq else; ...; b end) and shares one bx lr,
 * costing the extra unconditional branch. Three source forms tried (early
 * return, inverted condition, goto to a shared epilogue); mwcc predicates all.
 * Semantics: with flag bit 2 set, just OR bit 0 into dst[0]; otherwise copy the
 * 3-word vector from src into dst[1..3] and OR 0x18 into dst[0]. */
void func_01ffa1b8(int *dst, int *src, int unused, int flags) {
    if (flags & 4) {
        dst[0] |= 1;
    } else {
        dst[1] = src[0];
        dst[2] = src[1];
        dst[3] = src[2];
        dst[0] |= 0x18;
    }
}
