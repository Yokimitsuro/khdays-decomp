/*
 * func_ov008_020681b0 -- x3 (ov008/...). Draw a UTF-16 string with newline handling.
 * Starting pen x = x0. For each code unit: on U+000A advance past it, reset x = x0 and drop the
 * baseline y by 0xb; then draw the (current) glyph via 02030194(ctx, x, y, style, glyph), advance the
 * string, and move the pen right by the returned advance width. Stops at the NUL terminator.
 *
 * The `volatile` read of the leading code unit is a matching device: the retail compiler re-loads
 * *str at the top of every iteration, but mwcc 3.0/139 coalesces it with the loop-condition load
 * from the previous iteration (one ldrh fewer). The volatile forces the redundant reload; behaviour
 * is identical (a plain `*str`).
 */
extern int func_02030194(int *ctx, int x, int y, int style, int glyph);

void func_ov008_020681b0(int *ctx, int x0, int y, int style, unsigned short *str) {
    int x = x0;

    if (*str != 0) {
        do {
            unsigned short c = *(volatile unsigned short *)str;
            if (c == 10) {
                str++;
                x = x0;
                y += 0xb;
            }
            x += func_02030194(ctx, x, y, style, *str);
            str++;
        } while (*str != 0);
    }
}
