/*
 * Collect the node's status bits into a mask and OR it into the HUD word at +0x1e4.
 *
 * Bit 0 from the 64-bit field at +0x464's bit 5, bit 1 from its bit 30, bit 5 from *node's
 * bit 19 OR a positive counter at +0x4b4, bit 2 from either of two more bits of +0x464, and
 * bit 3 from the ordinary 32-bit word at +0x24.  Nothing is written when the mask is empty.
 *
 * The park read this as a predicate-versus-branch structural tie: "the bit-flag OR-accumulator
 * (5 guarded r|=K) is predicated inline by mwcc (112B) where the original branches each guard
 * out of line (184B)".  The 72-byte gap was not branching -- it was that four of the five
 * guards are 64-BIT mask tests on the field at +0x464 and on *node, each of which costs an
 * extra load, `and #0` and `cmpeq`.
 *
 * NOTE THE FIFTH GUARD IS NOT.  The test on +0x24 is a plain 32-bit `tst`, and converting it
 * too puts the function 16 bytes OVER.  The signature has to be read per-test: only the pairs
 * where the ROM emits an `and rX, rY, #0` alongside the real mask are 64-bit fields.
 *
 * Last two bytes: the accumulator is declared BEFORE the 64-bit local, or it and the field's
 * low word swap registers.
 */
void func_ov022_0209a1ac(unsigned int *arg0) {
    unsigned int r = 0;
    long long v = *(long long *)&arg0[0x119];

    if ((v & 0x20) != 0) {
        r = r | 1;
    }
    if ((v & 0x40000000) != 0) {
        r = r | 2;
    }
    if ((*(long long *)arg0 & 0x80000) != 0 || 0 < (int)arg0[0x12d]) {
        r = r | 0x20;
    }
    if ((v & 0x8000000) != 0 || (v & 0x10000000) != 0) {
        r = r | 4;
    }
    if ((arg0[9] & 4) != 0) {
        r = r | 8;
    }
    if (r != 0) {
        *(unsigned int *)(arg0[0x13b] + 0x1e4) = *(unsigned int *)(arg0[0x13b] + 0x1e4) | r;
    }
}
