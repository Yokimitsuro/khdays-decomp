/* func_ov025_02094688 -- Ov008_ScrollMenuRowsTo: keep nRow inside the visible
 * window of a scrolled menu.  A row outside [0, nTotal) answers -1.  A row past the
 * window's end scrolls so it becomes the last visible row, a row before it so it
 * becomes the first; either way the row origin handed to Ov008_LayoutMenuRows2 is
 * the new first row's share of the track (nTrackEnd - ctx->nTrackBase, over the
 * nTotal - nVisible scrollable rows).  A row already inside keeps the current
 * origin (ctx->nRowOrigin - 0x18).  Returns the (new) first visible row.  The
 * track span is a named local in the first arm (a bare product puts the span in
 * the multiplier slot); the layout helper takes two arguments.
 */
typedef unsigned char u8;

typedef struct Ov008LayoutCtx2 {
    u8  pad_0000[0x2f8];
    int nTrackBase;           /* 0x2f8 */
    int nRowOrigin;           /* 0x2fc: row origin (layout sets it from origin + 0x18) */
} Ov008LayoutCtx2;

extern int func_02020400(int nNum, int nDen);                          /* _s32_div_f */
extern void func_ov025_020917e4(Ov008LayoutCtx2 *pCtx, int nOrigin);   /* Ov008_LayoutMenuRows2 */

int func_ov025_02094688(Ov008LayoutCtx2 *pCtx, int nRow, int nFirst, int nTotal, int nTrackEnd, int nVisible)
{
    int nOrigin = pCtx->nRowOrigin - 0x18;
    int nDiff;

    if (nRow < 0 || nTotal <= nRow) {
        return -1;
    }
    if (nRow >= nFirst + nVisible) {
        nDiff = nTrackEnd - pCtx->nTrackBase;
        nFirst = nRow - (nVisible - 1);
        nOrigin = func_02020400(nDiff * nFirst, nTotal - nVisible);
    } else if (nRow < nFirst) {
        nOrigin = func_02020400(nRow * (nTrackEnd - pCtx->nTrackBase), nTotal - nVisible);
        nFirst = nRow;
    }
    func_ov025_020917e4(pCtx, nOrigin);
    return nFirst;
}
