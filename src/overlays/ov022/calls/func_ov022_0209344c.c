/* Is the block either finished (bit 3) or flushed (bit 2)? The first test goes
 * through a masked temporary compared > 0, which is what the ROM's
 * and/cmp/bgt sequence reports; the second is a plain bit test. */
int func_ov022_0209344c(unsigned char *self) {
    unsigned char flags = *self;
    int finished = flags & 8;

    if (finished > 0 || (flags & 4) != 0) {
        return 1;
    }

    return 0;
}
