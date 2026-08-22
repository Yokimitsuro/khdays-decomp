/*
 * Ov002_PaintGroupRow - repaint one of the four group rows: its tile and
 * palette, and the count beside it.
 *
 * Only three group ids paint anything. Group 3 is the keyed one: the tile is
 * the slot the key resolves to, and the palette is the bright one only when
 * the entry behind the slot has a count and both key tests agree. Group 8
 * looks its cell up by the byte its pointer names, walking the fifteen cells,
 * and takes the count from the byte after it. Group 7 is the fixed row - one
 * tile, the dim palette, and no count at all. Anything else leaves the row
 * alone.
 *
 * The count is drawn for the two keyed groups and skipped for the fixed one,
 * which is what the flag carries across the shared tail.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bFirst;
    u8 bSecond;
} Ov002PanelCell;

typedef struct {
    u16 nGroup;                         /* +0x00 */
    u16 pad0002;
    u8 *pKeyRef;                        /* +0x04 */
    u16 *pEntry;                        /* +0x08 */
    u16 nKey;                           /* +0x0c */
    u16 pad000e;
} Ov002PanelGroupSlot;

typedef struct {
    u8 pad0000[0x32];
    Ov002PanelCell aCells[0xf];         /* +0x032 */
    u8 pad0050[0x3f0];
    Ov002PanelGroupSlot aGroups[4];     /* +0x440 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a540(unsigned int nKey);
extern int func_ov002_0205a600(int nCell);
extern int func_ov002_0205a714(int nGroup, int nKey);
extern int func_ov002_0205a730(int nGroup, int nKey);
extern void func_ov002_0205aa3c(int nSlot, int nValue, int nColumn,
                                int bRightAlign, int bShowZero);
extern void func_ov002_0205ad5c(int nSlot, int nColumn, int nTile,
                                int nPalette, int bRightAlign);

void func_ov002_0205b234(int nRow)
{
    Ov002PanelSession *s;
    int nTile;
    int nPalette;
    int nCount;
    Ov002PanelGroupSlot *pGroup;
    int nCell;
    int bDrawCount;

    s = data_ov002_0207f620;
    pGroup = &s->aGroups[nRow];
    bDrawCount = 1;

    switch (pGroup->nGroup) {
    case 8:
        nCell = 0;
        do {
            if (*pGroup->pKeyRef == s->aCells[nCell].bFirst) {
                break;
            }
            nCell++;
        } while (nCell < 0xf);
        nTile = nCell * 0x10 + 0x130;
        if (func_ov002_0205a600(nCell) != 0) {
            nPalette = 0xf;
        } else {
            nPalette = 0xe;
        }
        nCount = pGroup->pKeyRef[1];
        break;
    case 3:
        nTile = func_ov002_0205a540(pGroup->nKey) * 0x10 + 0x250;
        if (pGroup->pEntry == 0) {
            nCount = 0;
        } else {
            nCount = pGroup->pEntry[1];
        }
        if (nCount > 0 && func_ov002_0205a714(0, pGroup->nKey) != 0
            && func_ov002_0205a730(0, pGroup->nKey) != 0) {
            nPalette = 0xf;
        } else {
            nPalette = 0xe;
        }
        break;
    case 7:
        nTile = 0x3d0;
        nPalette = 0xe;
        bDrawCount = 0;
        break;
    default:
        return;
    }

    func_ov002_0205ad5c(nRow + 2, 1, (u16)nTile, (u16)nPalette, 0);
    if (bDrawCount) {
        func_ov002_0205aa3c(nRow + 2, nCount, 1, 0, 1);
    }
}
