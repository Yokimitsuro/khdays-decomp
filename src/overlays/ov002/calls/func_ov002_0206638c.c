/*
 * Blits an expanded byte-per-pixel mask onto the canvas.
 *
 * The point given is the centre of the mark, so every pixel is placed relative
 * to it by half the mask's own width and height. A null mask stands for a solid
 * block, and each pixel's own coverage is combined with the pen colour before it
 * is plotted.
 *
 * Five things here are load-bearing rather than style.
 *
 * The inner loop carries its own width guard on top of the test in its header.
 * The two branches land on the same flags with only the row's y computation
 * between them, which is exactly what the original does; without the guard the
 * function is one instruction short.
 *
 * Both plotted coordinates are their own variables. The row's y is worked out
 * once per row before the inner loop and the column's x once per pixel inside
 * it; written out at the call instead, the mask test is scheduled ahead of the
 * coordinate and the whole loop body reorders.
 *
 * The two half extents are worked out once at the top, the width before the
 * height. Left inside the coordinate expressions they are still hoisted, but
 * they land after the height guard rather than before it.
 *
 * The column counter is zeroed before the width guard rather than in the loop
 * header.
 *
 * The two coordinates are halfword parameters. A wider type reorders the
 * prologue's spills even though the allocation is otherwise identical.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern void func_ov002_020662d4(int hCanvas, u16 nX, u16 nY, u8 nColour);

void func_ov002_0206638c(int hCanvas, u16 nX, u16 nY, int nWidth, int nHeight,
              u8 nPen, const u8 *pMask)
{
    u16 nRow;
    u16 nCol;
    u8 nValue;
    u16 nPlotY;
    u16 nPlotX;
    u16 nHalfW;
    u16 nHalfH;

    nHalfW = (u16)(nWidth / 2);
    nHalfH = (u16)(nHeight / 2);
    for (nRow = 0; nRow < nHeight; nRow++) {
        nCol = 0;
        if (nWidth > 0) {
            nPlotY = (u16)(nRow + nY - nHalfH);
            for (; nCol < nWidth; nCol++) {
                nPlotX = (u16)(nCol + nX - nHalfW);
                if (pMask == 0) {
                    nValue = 0xff;
                } else {
                    nValue = pMask[nRow * nWidth + nCol];
                }
                func_ov002_020662d4(hCanvas, nPlotX, nPlotY,
                         (u8)(nPen & nValue));
            }
        }
    }
}
