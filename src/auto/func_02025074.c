/* func_02025074 -- read the sign bit of a tile-map entry for a packed coordinate.
 * Selects the 0x1ff8000 map row from bits 7.. of the packed coordinate, reads that row's
 * 16-bit header at +2, and indexes the row by (header + 1) / 2 words plus the coordinate's
 * low 5 bits, returning bit 31 of the word found.
 *
 * The 0xfffffc mask is ONE local: the ROM loads it once and derives the 0x1f masks from it
 * with `r1, lsr #15`, which is what a shared variable gives for free.
 *
 * The two index terms are deliberately spelled differently and both spellings are load-bearing:
 *  - the header term keeps the explicit `(x << 0x11) >> 0xf` -- it is a 15-bit truncation
 *    followed by *4, and `(unsigned short)x * 4` comes out as a 16-bit one;
 *  - the coordinate term goes through an `unsigned short` local, because written as the same
 *    shift pair mwcc folds the mask into the shift (`p << 23 >> 21`) and drops an instruction.
 * The `(e + 1) / 2` is a SIGNED divide -- the ROM's `add r0,r0,r0,lsr#31 ; asr r0,r0,#1`. */
unsigned int func_02025074(unsigned int param_1) {
    unsigned int mask = 0xfffffc;
    unsigned int base = (param_1 >> 7 & mask) + 0x1ff8000;
    unsigned short lo = param_1 & (mask >> 15);
    int e = *(unsigned short *)(base + 2) & (mask >> 15);

    return *(unsigned int *)(base + ((unsigned int)(((e + 1) / 2) << 0x11) >> 0xf)
                                  + lo * 4 + 0x10) & 0x80000000;
}
