/* NONMATCHING: +4B. ROM emits a redundant add r0,r0,#0 between the -1 and the 16-bit
 * zero-extend (lsl#0x10;lsr#0x10); no C form reproduces the filler op. Tag decrement accessor. */
/* func_ov008_02072fe4 -- return the 0-based value of a node's 1-based tag byte, ov008.
 * Given a node pointer, returns (byte[+0xd] - 1) truncated to 16 bits when the tag is set,
 * or -1 for a null node or an unset (zero) tag. */
unsigned int func_ov008_02072fe4(int node) {
    if (node == 0) {
        return 0xffffffff;
    }
    if (*(unsigned char *)(node + 0xd) != 0) {
        return *(unsigned char *)(node + 0xd) - 1 & 0xffff;
    }
    return 0xffffffff;
}
