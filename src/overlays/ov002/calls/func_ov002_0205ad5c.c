/* Write the 8x2 tile label of one panel slot into item resource 0x09.
 *
 * The tile row is 0x18 - (6 - nSlot)*2, so slots count upwards from the bottom
 * of the block; that row and the one below it are first cleared over eleven
 * tiles. The label then writes eight consecutive glyphs from nTile on the upper
 * row and the next eight, from nTile+8, on the lower one. Each map entry is the
 * glyph OR'd with the palette shifted into its top nibble.
 *
 * Columns start at nColumn plus an indent of 2 when bRightAlign is set and 1
 * when it is not -- the same one-column shift the rest of the panel row applies.
 *
 * Three codegen notes. The glyph counters are int, not u16: the ROM increments
 * them unmasked, and narrowing them costs six lsl/lsr instructions. The column
 * is associated as nColumn + (nIndent + i), because the left-associated form
 * lets mwcc hoist nColumn + nIndent out of the loop, which the ROM does not do.
 * And nRow must be declared after pRes: the declaration order of the locals is
 * what puts the resource pointer above the row in the callee-saved range.
 */
typedef unsigned short u16;

extern int func_ov002_02053bb8(int nItemId);
extern void MIi_CpuClear16(int nValue, int pDest, int nSize);

void func_ov002_0205ad5c(int nSlot, int nColumn, int nTile, int nPalette,
                         int bRightAlign) {
    int pRes;
    int i;
    int nRow;
    int nIndent;
    int nLower;

    pRes = func_ov002_02053bb8(9);
    nRow = 0x18 - (6 - nSlot) * 2;
    nIndent = bRightAlign ? 2 : 1;

    MIi_CpuClear16(0, pRes + nRow * 0x40, 0x16);
    MIi_CpuClear16(0, pRes + (nRow + 1) * 0x40, 0x16);

    nLower = nTile + 8;
    for (i = 0; i < 8; i++) {
        int nCol = nColumn + (nIndent + i);

        *(u16 *)(pRes + (nCol + nRow * 0x20) * 2) = nTile | (nPalette << 12);
        *(u16 *)(pRes + (nCol + (nRow + 1) * 0x20) * 2) =
            nLower | (nPalette << 12);
        nTile++;
        nLower++;
    }
}
