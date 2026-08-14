/* Draw a two-digit counter into the HUD tile map of item resource 0x0b.
 *
 * The field is three tile columns wide starting at column 9, offset by
 * nColumn, on the two tile rows at nSlot*2+12. Each digit is one tile wide and
 * two tall: the left position takes its glyph from base 0x201 and the right
 * from 0x20b, and the bottom halves sit 0x20 tiles further into the map. A
 * single-digit value is drawn in the left position, a value of zero or less
 * draws '0' when bShowZero is set and blank tile 0x11f when it is not.
 *
 * bRightAlign shifts the pair one column right and leaves column 9 alone;
 * clearing it moves the pair left and blanks the trailing column instead, so
 * the field occupies the same three columns either way.
 *
 * The column base is folded into nCol rather than into nColumn: mwcc only keeps
 * the sum on this side of the resource call when the selected constant is the
 * one being mutated, and otherwise sinks it past the call and spends an extra
 * callee-saved register on it.
 */
typedef unsigned short u16;

extern int func_ov002_02053bb8(int nItemId);
extern void func_ov002_02053cd4(int nItemId);
extern void func_ov002_0205aa14(int pDst, u16 nTopLeft, u16 nTopRight,
                                u16 nBottomLeft, u16 nBottomRight);

void func_ov002_0205aa3c(int nSlot, int nValue, int nColumn, int bRightAlign,
                         int bShowZero) {
    int nTens;
    int nOnes;
    int nCol;
    int pDst;

    nTens = nValue / 10;
    nOnes = nValue % 10;
    nCol = bRightAlign ? 10 : 9;
    nCol += nColumn;
    pDst = func_ov002_02053bb8(0xb) + (nCol + (nSlot * 2 + 0xc) * 0x20) * 2;

    if (nValue > 0) {
        if (nTens == 0) {
            if (nOnes > 0) {
                func_ov002_0205aa14(pDst, nOnes + 0x201, 0, nOnes + 0x221, 0);
            }
        } else {
            func_ov002_0205aa14(pDst, nTens + 0x201, nOnes + 0x20b,
                                nTens + 0x221, nOnes + 0x22b);
        }
    } else if (bShowZero) {
        func_ov002_0205aa14(pDst, 0x201, 0, 0x221, 0);
    } else {
        func_ov002_0205aa14(pDst, 0x11f, 0, 0x13f, 0);
    }

    if (bRightAlign == 0) {
        *(u16 *)(pDst + 4) = 0;
        *(u16 *)(pDst + 0x44) = 0;
    }
    func_ov002_02053cd4(0xb);
}
