/*
 * Ov002_RecolourGaugeBlock - repaint the gauge's eight-by-eight block of screen
 * entries with the palettes a layout table gives.
 *
 * Only the palette survives from the table: each entry keeps the tile it already
 * names and takes the top four bits of the matching halfword instead. The block
 * starts nine rows down the 32-entry-wide screen and four entries in.
 *
 * When the page still has somewhere to go the sub-display is told about it, and
 * the item is selected once at the end either way.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef unsigned long u32;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

extern u16 *func_ov002_02053bb8(int nItemId);
extern void func_ov002_02053cd4(int nItemId);
extern int func_ov002_02063624(void);
extern int func_ov002_02053558(int nId);
extern void func_ov002_020535a4(int nHandle);

void func_ov002_0206484c(const NNSG2dScreenData *pMap)
{
    u16 *pScreen;
    int nRow;
    int nCol;
    int nBase;
    u16 nPal;
    u16 *pRow;

    pScreen = func_ov002_02053bb8(0x1a);
    for (nRow = 0, nBase = 0; nRow < 8; nRow++) {
        pRow = pScreen + (nRow + 9) * 0x20;
        for (nCol = 0; nCol < 8; nCol++) {
            nPal = (((const u16 *)pMap->rawData)[nBase + nCol] >> 12) & 0xf;
            pRow[4] = (u16)((nPal << 12) | (pRow[4] & 0xfff));
            pRow++;
        }
        nBase += 8;
    }

    if (func_ov002_02063624() >= 0) {
        func_ov002_020535a4(func_ov002_02053558(0x419));
    }
    func_ov002_02053cd4(0x1a);
}
