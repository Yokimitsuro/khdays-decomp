/* Returns the last positive entry of the 5-slot short array at +0xe0, or 0.
 *
 * Two codegen notes:
 *  - The ROM widens the index through `lsl #16 / lsr #15` for the guard read but
 *    uses a plain `lsl #1` for the value read.  That is an `(unsigned short)i * 2`
 *    byte offset in the first case and an `int` element index in the second, so the
 *    two reads must be written with different index expressions even though they hit
 *    the same array.
 *  - `best` must be declared last so that the `mov r3,#0 / mov r2,r3` pair keeps
 *    the ROM's register assignment (best=r3, i=r2).
 */
int func_ov002_0207c6c0(int obj) {
    int v;
    int i;
    int best;
    best = 0;
    i = best;
    do {
        if (*(short *)(obj + (unsigned short)i * 2 + 0xe0) > 0) {
            v = ((short *)obj)[i + 0x70];
            if (best != v) {
                best = v;
            }
        }
        i = i + 1;
    } while (i < 5);
    return best;
}
