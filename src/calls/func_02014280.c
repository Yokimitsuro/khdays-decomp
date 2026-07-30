/*
 * Text_DrawLine - draw one line of glyphs and report the start of the next line.
 *
 * Iterates the string with the font's getNext iterator (font[1]), blitting each
 * glyph via func_02014024 and advancing the pen by (opts + glyphAdvance) along the
 * glyph-advance direction dir=(dx,dy). Stops at NUL (end of string) or newline
 * (0x0a, end of line). Through pNext it reports the cursor at the start of the next
 * line: the position just past the newline, or 0 when the whole string is consumed.
 *
 * Called per line by the layout loop Text_DrawAlignedLines (func_02014334). dir is a
 * 2-byte by-value struct {s8 dx, dy}. ctx[0]=owner, ctx[1]=font, ctx[2]=char spacing.
 */

typedef struct { signed char dx, dy; } TextDir;

extern int func_02014024(int a, int *font, int x, int y, int p5, int ch);

void func_02014280(int *ctx, int x, int y, int p5, int s, int *pNext, TextDir dir)
{
    int opts = ctx[2];
    int *font = (int *)ctx[1];
    int c = s;
    int (*getNext)(int *) = (int (*)(int *))font[1];
    int ch = getNext(&c);

    if (ch != 0) {
        do {
            int adv, w;
            if (ch == 10) break;
            adv = func_02014024(ctx[0], font, x, y, p5, ch);
            w = opts + adv;
            x += w * dir.dx;
            y += w * dir.dy;
            ch = getNext(&c);
        } while (ch != 0);
    }
    if (pNext != 0)
        *pNext = (ch == 10) ? c : 0;
}
