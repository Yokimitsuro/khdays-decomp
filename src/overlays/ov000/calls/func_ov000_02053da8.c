/* Draw a shadowed logo string: every glyph is rendered twice, first as a (+1,+1) shadow
 * in colour 1 and then in the requested colour, advancing x by the width the renderer
 * reports. A newline (0xa) drops y by 0xc and returns x to the left margin.
 *
 * Two things, and each one alone leaves the other wrong:
 *   - the ROM re-reads *str at the top of the loop instead of reusing the value the
 *     entry test already loaded. Nothing aliases the string between the two reads, so
 *     mwcc commons them unless the two reads are spelled with DIFFERENT addressing --
 *     the entry test as a plain dereference, the loop test through a `char *` cast.
 *     Same address, same `ldrh`, and the CSE stops.
 *   - `x = x0` is assigned BEFORE the empty-string guard, which is what puts it above
 *     the predicated early return and makes x0 the first parameter saved. */
extern int func_02030194(void *ctx, int x, int y, int color, int glyph);

void func_ov000_02053da8(void *ctx, int x0, int y, int a3, unsigned short *str) {
    int x = x0;

    if (*str == 0) {
        return;
    }
    do {
        if (*(unsigned short *)((char *)str) == 0xa) {
            str++;
            y += 0xc;
            x = x0;
        }
        func_02030194(ctx, x + 1, y + 1, 1, *str);
        x += func_02030194(ctx, x, y, a3, *str);
        str++;
    } while (*str != 0);
}
