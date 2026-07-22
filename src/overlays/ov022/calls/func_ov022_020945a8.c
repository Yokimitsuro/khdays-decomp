/* func_ov022_020945a8 -- should this battle actor be suppressed this frame?
 * Answers 1 when any of a set of status bits is up: the actor has no hit-window left
 * (+0x12 == 0), or its 64-bit status word at +0x464 carries 0x8000 or 0x100, or it carries any
 * bit of a variable mask, or the object's own 64-bit flag word carries 0x2_108a2904. The mask
 * (0x90_20003690) drops bit 0x80 while the object's flag bit 36 is up.
 *
 * Parked as an "open derivation": written with 32-bit C it came out ~64 B short and a naive
 * 64-bit rewrite ~28 B long, and the note attributed the ROM's `cmp;cmpeq` pairs and its
 * `sub;sub;and;and` mask arithmetic to hand-fused conditions. They are neither hand-fused nor
 * hard: every one of them is what mwcc emits for an ORDINARY `unsigned long long` test --
 * the paired compare IS a 64-bit `!= 0`, and `mask &= ~0x80ULL` really does become
 * "materialise -1 and -0x81 from a zero, then AND both halves".
 *
 * Two things were load-bearing once the types were right:
 *  - the object's own flag word must be read INLINE at both uses (`*p & ...`), not bound to a
 *    local. As a local, mwcc merges the two halves into one `ldm r4,{r1,r4}`; the ROM keeps two
 *    `ldr`s, and that is the whole 4-byte gap. (It cannot merge the +0x464 pair, which is why
 *    only this one shows the difference.)
 *  - `int r` must be declared BEFORE the pointer, which colours r->r4 and p->r5 as the ROM does.
 */
extern int func_02030694(void);

int func_ov022_020945a8(int obj) {
    int r = 0;
    unsigned long long *p = *(unsigned long long **)(obj + 0x328);
    unsigned long long a, mask;

    if (func_02030694() == 0) {
        return r;
    }
    if (*(unsigned short *)((char *)p + 0x12) == 0) {
        r = 1;
    }
    a = *(unsigned long long *)((char *)p + 0x464);
    if ((a & 0x8000ULL) != 0 || (a & 0x100ULL) != 0) {
        r = 1;
    }
    mask = 0x9020003690ULL;
    if ((*p & 0x1000000000ULL) != 0) {
        mask &= ~0x80ULL;
    }
    if ((a & mask) != 0) {
        r = 1;
    }
    if ((*p & 0x2108a2904ULL) != 0) {
        r = 1;
    }
    return r;
}
