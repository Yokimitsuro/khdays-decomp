/* Equivalent, readable C. NOT byte-exact: size matches exactly but mwcc colors
 * the four loop-local ints in a different r5-r8 permutation than the original
 * (orig palsh=r5,zero=r6,div=r7,leading=r8; mine rotated). A pure coloring tie,
 * same class as the sibling func_ov003_0204d1c0 — confirmed unsteerable across
 * declaration order, for/while, and combined/split init. The asm stub keeps the
 * blob byte-exact.
 *
 * Sibling of func_ov003_0204d1c0: renders `value` (clamped to 999) as up to 3
 * decimal digit tiles from dst, with a caller-supplied palette (low nibble of
 * `pal` -> tile palette bits 12-15). Leading zeros blank; ones place always
 * prints. */
extern long long func_02020400(unsigned int value, unsigned int divisor);

void func_ov003_0204d264(unsigned short *dst, unsigned int value, int pal) {
    int palsh = pal << 0x1c;
    int leading = 1;
    int zero = 0;
    int div;

    if (value > 999) {
        value = 999;
    }
    for (div = 100; div > 0; div = div / 10) {
        long long q = func_02020400(value, div);
        int d = (char)q;
        if (d != 0) {
            leading = zero;
            *dst = (d + 0x34) | ((unsigned int)palsh >> 16);
        } else if (leading == 0 || div == 1) {
            *dst = (d + 0x34) | ((unsigned int)palsh >> 16);
        }
        q = func_02020400(value, div);
        value = (unsigned short)(q >> 0x20);
        dst = dst + 1;
    }
}
