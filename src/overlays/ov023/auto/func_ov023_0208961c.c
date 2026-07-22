/* func_ov023_0208961c -- build a DMA/geometry descriptor word for the object.
 * Layout: bit 31 always set, the object's +0x1a24 pointer biased by 0x8000 and 4-byte aligned in
 * bits 9..29, and the caller's index in the low 5 bits.
 *
 * The two masks are ONE constant in the ROM: 0xfffffc is pooled and the low-bit mask is derived
 * from it as `>> 15`. Spelled as a literal 0x1f, mwcc emits `movs r0,#0x1f` and the function is
 * 6 bytes off; bound to a local and shifted, it matches. Same for 0x8000/0x80000000, which the
 * ROM builds with two shifts of a single `movs #2`. */
unsigned int func_ov023_0208961c(int obj, unsigned int n) {
    unsigned int mask = 0xfffffc;
    return ((((*(int *)(obj + 0x1a24) + 0x8000) & mask) << 7) | 0x80000000) | (n & (mask >> 15));
}
