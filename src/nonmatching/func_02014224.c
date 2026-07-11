/* NONMATCHING — register-permutation tie (every instruction matches the original
 * in opcode, operand shape, shift and order; only the register NUMBERS differ).
 *
 * The full body is byte-shape identical: same push set, same early-out, the same
 * `orr Rv, tile, shifted, lsr #16` per-cell value, `strh Rv, [walk], #2`, and the
 * two nested down-counting loops. mwcc simply colors the working set differently
 * than the ROM: the ROM keeps `shifted` (pal<<0x1c) in ip and the per-cell value in
 * lr with the outer/inner counters in r6/r5; every mwcc build we have swaps those
 * (shifted->r4, value->ip, counters r5/r6). All bytes past the register fields agree.
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds x {-O4,p / -O4,s / -O4 /
 * -O3,p / -O2} x 4 source spellings (named value temp, signed vs unsigned `shifted`,
 * (pal&0xf)<<12 vs (pal<<28)>>16, decl-order permutations) — none reproduces the
 * ROM's coloring. The blob keeps the build byte-exact; this records the intended C.
 *
 * Fill a rows x cols tilemap region at dst (row stride `stride` halfwords) with an
 * incrementing tile index, OR'd with the palette bank (pal & 0xf) << 12. `tile` is a
 * 32-bit counter truncated only by the halfword store (the ROM never masks it to 16
 * bits mid-loop), which is why it is typed int rather than unsigned short here. */
void func_02014224(unsigned short *dst, int cols, int rows, int stride,
                   int tile, int pal) {
    unsigned int shifted = (unsigned int)(pal << 0x1c);
    int y = 0;
    if (rows > 0) {
        do {
            int x = 0;
            unsigned short *p = dst;
            if (cols > 0) {
                do {
                    *p = (unsigned short)(tile | (shifted >> 16));
                    x++;
                    tile++;
                    p++;
                } while (x < cols);
            }
            y++;
            dst += stride;
        } while (y < rows);
    }
}
