/* Draw one 6 x 0x2e cell of the layout in style 1 with no flags. Sibling of
 * Ov002_DrawLayoutRow: same seven-argument call site, wider cell, and the row is
 * passed straight through instead of being indexed out of the table. */
extern void func_ov002_020576d8(int a, int b, int width, int height,
                                int flags, int style, void *row);

void func_ov002_020578c4(int a, int b, void *row) {
    func_ov002_020576d8(a, b, 6, 0x2e, 0, 1, row);
}
