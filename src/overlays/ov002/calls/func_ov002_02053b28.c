/*
 * Ov002_FillMapRows - write a block of rows into a map from a fixed source.
 *
 * The block is clipped to the 32-tile map on both axes, the destination is
 * prepared, and then one row per line is handed to the map writer, all of them
 * reading from the same place in the UI context. The context pointer is fetched
 * again on every row rather than kept, which is what the ROM does.
 *
 * ARM. The two extents are shorts, so both clips truncate. The pragma is
 * what keeps the destination offset recomputed from the row each time -
 * without it mwcc turns it into an induction variable stepping by 0x40, and
 * the register colouring shifts with it.
 */

#pragma opt_strength_reduction off

extern void func_ov002_02053bb8(int nDest);
extern void func_ov002_02053c18(int nDest, int nOffset, unsigned char *pRow,
                                int nBytes);

extern int data_ov002_0207f60c;

void func_ov002_02053b28(int nDest, int nX, int nY, short nWidth, short nHeight)
{
    int i;

    if (nX + nWidth > 0x20) {
        nWidth = 0x20 - nX;
    }
    if (nY + nHeight > 0x20) {
        nHeight = 0x20 - nY;
    }

    func_ov002_02053bb8(nDest);

    for (i = 0; i < nHeight; i++) {
        func_ov002_02053c18(nDest, (nX + nY * 0x20) * 2,
                            *(unsigned char **)&data_ov002_0207f60c + 0x12,
                            nWidth * 2);
        nY++;
    }
}
