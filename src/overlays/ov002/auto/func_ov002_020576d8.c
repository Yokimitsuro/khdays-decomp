/* Write a run of 4bpp pixels into a tiled character buffer, right aligned.
 *
 * The starting column is the width plus padding rounded up to a whole
 * eight-pixel tile, minus the right margin, clamped at zero. From it the
 * destination byte is the tile at column over eight, 0x20 bytes each, plus half
 * the column within the tile since two pixels share a byte, plus four bytes per
 * row. Successive pixels step four bytes, the stride of one pixel row inside a
 * tile. Whether the column is odd decides which nibble each source byte lands
 * in, so the two loops differ only in the mask and the shift.
 *
 * The address is written as an integer sum with the buffer cast in as the last
 * addend and the tile term first. As ordinary pointer arithmetic mwcc folds the
 * base in early and loses a callee-saved register; only this permutation gives
 * both the final add and the frame.
 */
typedef unsigned char u8;

void func_ov002_020576d8(u8 *pDst, int nRight, int nCount, int nWidth,
                         int nPad, int nRow, const u8 *pSrc) {
    int nAligned = ((nPad + nWidth + 7) / 8) * 8;
    int nStart = nAligned - (nRight + nPad + 1);
    int i;
    u8 *p;

    if (nStart < 0) {
        nStart = 0;
    }
    p = (u8 *)((nStart / 8) * 0x20 + nRow * 4 + (nStart % 8) / 2 + (int)pDst);

    i = 0;
    if ((nStart & 1) != 0) {
        if (nCount <= 0) {
            return;
        }
        do {
            *p = (u8)((*p & 0xf) | (pSrc[i] << 4));
            i++;
            p += 4;
        } while (i < nCount);
        return;
    }
    if (nCount <= 0) {
        return;
    }
    do {
        *p = (u8)((*p & 0xf0) | pSrc[i]);
        i++;
        p += 4;
    } while (i < nCount);
}
