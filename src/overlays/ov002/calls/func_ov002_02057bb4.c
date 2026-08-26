/*
 * Ov002_DrawGaugeSpan - paint one run of gauge cells into a bar's tile data.
 *
 * The bar is 4bpp tile data laid out as 8 by 8 tiles, so a pixel column picks a
 * tile, a byte inside that tile's row, and one of the two nibbles in that byte.
 * Cells are counted from the right-hand end of the bar: the run starts at the
 * padded width and walks back, and a column that falls off the left edge is
 * clamped to zero rather than wrapping.
 *
 * Each cell takes its palette index from the setup's shade ramp, read from the
 * far end so that a shorter run uses the darker entries, and paints that index
 * down the requested number of tile rows, stepping a row at a time.
 *
 * The statement order inside the loop is the original's and is load-bearing. The
 * shade ramp is taken from the setup and its entry read before the column is
 * clamped and before the address is composed, which is what places the pointer
 * load between the two halves of the address arithmetic; and the run's back-count
 * and the setup pointer are both lifted out of the loop while the ramp field
 * itself is re-read every pass. Written any other way the code is the same
 * instruction for instruction and only the scratch registers move.
 *
 * ARM.
 */

typedef struct {
    int nLeftInset;
    int nRowWidth;
    int nBarHeight;
    int nTopRow;
    unsigned char *pShadeRamp;
    int nField0014;
    void *pDrawCell;
} Ov002GaugeSetup;

extern Ov002GaugeSetup data_ov002_0207e98c[2];

void func_ov002_02057bb4(unsigned char *pTiles, int nFirstCell, int nCellCount,
                         int nRowCount, int nBarWidth, int nLeftInset, int nTopRow)
{
    int i;
    int nPadded;
    int x;
    int jRow;
    unsigned char *pRamp;
    unsigned char *p;
    unsigned char nShade;
    int nFrom;
    Ov002GaugeSetup *pSetup;

    pSetup = data_ov002_0207e98c;
    nPadded = (nLeftInset + nBarWidth + 7) / 8;
    nFrom = 7 - nCellCount;
    for (i = 0; i < nCellCount; i++) {
        pRamp = pSetup->pShadeRamp;
        x = nPadded * 8 - (nFirstCell + i + nLeftInset + 1);
        nShade = pRamp[nFrom + i];
        if (x < 0) {
            x = 0;
        }
        p = pTiles + ((x / 8) * 32 + nTopRow * 4 + (x % 8) / 2);
        if ((x & 1) != 0) {
            for (jRow = 0; jRow < nRowCount; jRow++) {
                *p = (unsigned char)((*p & 0xf) | (nShade << 4));
                p += 4;
            }
        } else {
            for (jRow = 0; jRow < nRowCount; jRow++) {
                *p = (unsigned char)((*p & 0xf0) | nShade);
                p += 4;
            }
        }
    }
}
