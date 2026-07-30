/*
 * Text_DrawAlignedLines - lay out and draw a multi-line string.
 *
 * Walks the string one line at a time along the glyph-advance direction
 * `dir` = (dx, dy) (a packed pair of signed bytes), stepping to the next
 * line by `step` (= line spacing + font line height) along the perpendicular
 * (-dy, dx). For each line it applies horizontal alignment inside the box of
 * `width`: flag 0x800 right-aligns (offset = width - lineWidth), flag 0x400
 * centres ((width+1)/2 - (lineWidth+1)/2); the per-line width comes from
 * Text_MeasureLineWidth (func_02013768). Each line is emitted by func_02014280,
 * which also advances the string cursor to the start of the next line.
 *
 * Called by the text anchor func_0201449c after it resolves block alignment.
 * `dir` is passed by value as a 2-byte struct (the caller's CONCAT of a garbage
 * high half over the low 16 bits confirms the by-value 2-byte parameter).
 */

typedef struct { signed char dx, dy; } TextDir;

extern int  func_02013768(int font, int opts, int s, int *outNext);
extern void func_02014280(int *ctx, int x, int y, int p5, int s, int *pNext, TextDir dir);

void func_02014334(int *ctx, int x, int y, int width, int p5,
                   unsigned int flags, int str, TextDir dir)
{
    int step = ctx[3] + *(signed char *)(*(int *)ctx[1] + 1);
    int stepx = step * -dir.dy;
    int stepy = step * dir.dx;
    int px, py;
    int ox, oy;
    int s = str;

    if (str != 0) {
        ox = 0;
        oy = 0;
        do {
            px = x + ox;
            py = y + oy;
            if (flags & 0x800) {
                int w = func_02013768(ctx[1], ctx[2], s, 0);
                w = width - w;
                px += w * dir.dx;
                py += w * dir.dy;
            } else if (flags & 0x400) {
                int w = func_02013768(ctx[1], ctx[2], s, 0);
                w = (width + 1) / 2 - (w + 1) / 2;
                px += w * dir.dx;
                py += w * dir.dy;
            }
            func_02014280(ctx, px, py, p5, s, &s, dir);
            ox += stepx;
            oy += stepy;
        } while (s != 0);
    }
}
