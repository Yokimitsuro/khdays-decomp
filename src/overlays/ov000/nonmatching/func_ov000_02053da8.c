/* NONMATCHING: 1-instr CSE tie - retail re-reads *str at the loop top; our mwcc reuses
 * the pre-loop value. Logic byte-exact. For the PC port. */
/* func_ov000_02053da8 -- draw a shadowed logo text string, ov000. Renders each glyph of
 * the UTF-16 string twice (a +1/+1 shadow in color 1, then the glyph in color a3),
 * advancing x by the glyph width; a newline (0xa) drops y by 0xc and returns x to x0. */
extern int func_02030194(void *ctx, int x, int y, int color, int glyph);
void func_ov000_02053da8(void *ctx, int x0, int y, int a3, unsigned short *str) {
    if (*str == 0) {
        return;
    }
    int x = x0;
    do {
        if (*str == 0xa) {
            str++;
            y += 0xc;
            x = x0;
        }
        func_02030194(ctx, x + 1, y + 1, 1, *str);
        x += func_02030194(ctx, x, y, a3, *str);
        str++;
    } while (*str != 0);
}
