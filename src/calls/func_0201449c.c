/* func_0201449c = Text_AlignAnchor (ARM).
 * Measures the text block, then shifts the anchor (x,y) by the horizontal
 * alignment (flags 0x10 center / 0x20 far, using the block width) and the
 * vertical alignment (flags 2 center / 4 far, using the block height), both
 * projected along the text advance direction off={dx,dy}. Forwards the shifted
 * anchor and the block width to Text_DrawAlignedLines.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - The vertical-far term is written `t = -work.h; x += t*-off.dy; y += t*off.dx`
 *    (reusing t). Reusing a variable stops mwcc folding `-h * -dy -> h*dy`, so it
 *    emits the two separate negations the ROM has.
 *  - The horizontal pass reads its width through a SECOND, distinct struct type
 *    (TextDimsAlias) copied from the measured dims. Using a distinct type stops
 *    mwcc from scalar-replacing and double-spilling the vertical/final working
 *    copy; combined with the declaration order (work, dims, hview) it reproduces
 *    the ROM's stack layout exactly: dead copy at sp+0x10, dims out-param at
 *    sp+0x18, live working copy at sp+0x20, with dims.w kept in a register across
 *    the horizontal block.
 */
typedef struct { signed char dx, dy; } AxisOffset;
typedef struct { int w, h; } TextDims;
typedef struct { int w, h; } TextDimsAlias;

extern void func_0201386c(TextDims *out, int *font, int opts, int spacing, int str);
extern void func_02014334(int *ctx, int x, int y, int w, int mode, int flags, int p6, AxisOffset off);

void func_0201449c(int *ctx, int x, int y, int mode, int flags, int p6, AxisOffset off)
{
    TextDims work;
    TextDims dims;
    TextDimsAlias hview;
    int t;

    func_0201386c(&dims, (int *)ctx[1], ctx[2], ctx[3], p6);
    hview = *(TextDimsAlias *)&dims;
    work = dims;
    if (flags & 0x10)      { t = -(hview.w + 1) / 2; x = t * off.dx + x; y = t * off.dy + y; }
    else if (flags & 0x20) {                         x = -hview.w * off.dx + x; y = -hview.w * off.dy + y; }
    if (flags & 2)         { t = -(work.h + 1) / 2;  x = t * -off.dy + x; y = t * off.dx + y; }
    else if (flags & 4)    { t = -work.h;            x = t * -off.dy + x; y = t * off.dx + y; }
    func_02014334(ctx, x, y, work.w, mode, flags, p6, off);
}
