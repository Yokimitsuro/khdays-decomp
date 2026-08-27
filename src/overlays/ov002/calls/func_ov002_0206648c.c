/*
 * Draws one line on the canvas between two panel-relative points.
 *
 * The thick pen carries a five by five brush, copied out of the overlay's own
 * table into a local buffer the mark blitter can take; the thin pen passes no
 * brush at all, which the blitter reads as a single solid pixel.
 *
 * The longer axis is stepped one pixel at a time and the other is interpolated
 * from it, so a shallow line walks x and a steep one walks y. The interpolation
 * is a call to the shared divide rather than an inline division.
 *
 * Four things here are load-bearing rather than style.
 *
 * Both endpoint choices are written with the greater-or-equal case first. That
 * is what makes the less-than arm the predicated one and the other the fall
 * through, matching the original in both branches.
 *
 * The null brush pointer is assigned before the brush is copied, not after.
 *
 * The divide's numerator lands in a variable of its own inside the loop rather
 * than being written out as the call's argument. Left as an argument it costs
 * the whole prologue's register assignment, the second y coordinate's register
 * among them, and both of the spill-slot pairings.
 *
 * The loop's start, bound and base are declared after the index and the
 * numerator. Declared before them the two branches colour their registers the
 * same way as each other, where the original mirrors them.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002ThickMask {
    u8 aMask[25];
} Ov002ThickMask;

extern const Ov002ThickMask data_ov002_0207e444;
extern long long func_02020400(int num, int den);
extern void func_ov002_0206638c(int hCanvas, u16 nX, u16 nY, int nWidth,
                                int nHeight, u8 nPen, const u8 *pMask);

void func_ov002_0206648c(int hCanvas, u16 nX1, u16 nY1, u16 nX2, u16 nY2,
                         u8 nPen, int nWidth)
{
    Ov002ThickMask mask;
    const u8 *pMask;
    u16 nDx;
    u16 nDy;
    u16 i;
    int nNum;
    u16 nFrom;
    u16 nTo;
    u16 nBase;

    pMask = 0;
    mask = data_ov002_0207e444;
    if (nWidth == 5) {
        pMask = mask.aMask;
    }

    nDx = (u16)(nX1 >= nX2 ? nX1 - nX2 : nX2 - nX1);
    nDy = (u16)(nY1 >= nY2 ? nY1 - nY2 : nY2 - nY1);

    if (nDx > nDy) {
        if (nX1 >= nX2) {
            nFrom = nX2;
            nTo = nX1;
            nBase = nY2;
        } else {
            nFrom = nX1;
            nTo = nX2;
            nBase = nY1;
        }
        for (i = nFrom; i <= nTo; i++) {
            nNum = (i - nFrom) * (nY2 - nY1);
            func_ov002_0206638c(hCanvas, i,
                                (u16)(nBase + (int)func_02020400(
                                          nNum, nX2 - nX1)),
                                nWidth, nWidth, nPen, pMask);
        }
    } else {
        if (nY1 >= nY2) {
            nFrom = nY2;
            nTo = nY1;
            nBase = nX2;
        } else {
            nFrom = nY1;
            nTo = nY2;
            nBase = nX1;
        }
        for (i = nFrom; i <= nTo; i++) {
            nNum = (i - nFrom) * (nX2 - nX1);
            func_ov002_0206638c(hCanvas,
                                (u16)(nBase + (int)func_02020400(
                                          nNum, nY2 - nY1)),
                                i, nWidth, nWidth, nPen, pMask);
        }
    }
}
