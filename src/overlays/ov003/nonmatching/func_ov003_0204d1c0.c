/* Equivalent, readable C. NOT byte-exact: mwcc colors the two loop-carried
 * ints `leading` (r7) and `div` (r6) in the opposite order to the original
 * (mine r6/r7). Confirmed a pure r6<->r7 coloring tie across 8+ source forms
 * (declaration order both ways, for/while, split init) — unsteerable. The asm
 * stub keeps the blob byte-exact.
 *
 * Renders `value` (clamped to 9999) as up to 4 decimal digit tiles starting at
 * dst, palette row 9. Leading zeros are blank; the ones place always prints. */
extern long long func_02020400(unsigned int value, unsigned int divisor);

void func_ov003_0204d1c0(unsigned short *dst, unsigned int value) {
    int leading = 1;
    int zero = 0;
    int div;

    if (value > 9999) {
        value = 9999;
    }
    for (div = 1000; div > 0; div = div / 10) {
        long long q = func_02020400(value, div);
        int d = (char)q;
        if (d != 0) {
            leading = zero;
            *dst = d + 0x34 | 0x9000;
        } else if (leading == 0 || div == 1) {
            *dst = d + 0x34 | 0x9000;
        }
        q = func_02020400(value, div);
        value = (unsigned short)(q >> 0x20);
        dst = dst + 1;
    }
}
