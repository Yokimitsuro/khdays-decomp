/* func_ov008_02072fe4 -- return the 0-based index stored in a node's 1-based tag byte, ov008.
 * Returns -1 for a null node or an unset (zero) tag; otherwise the tag minus one, kept to
 * 16 bits.
 *
 * The `(char *)0 + x` round-trip is deliberate: it is what makes mwcc emit the ROM's
 * redundant `add r0, r0, #0` between the decrement and the 16-bit zero-extend. Same idiom
 * as func_ov004_0204cecc. */
unsigned int func_ov008_02072fe4(int node) {
    int tag;

    if (node == 0) return 0xffffffff;

    tag = *(unsigned char *)(node + 0xd);
    if (tag == 0) return 0xffffffff;

    tag--;
    tag = (int)((char *)0 + tag);
    return (unsigned int)(tag << 0x10) >> 0x10;
}
