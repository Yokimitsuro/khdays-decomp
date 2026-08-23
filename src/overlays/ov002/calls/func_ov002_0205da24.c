/*
 * Ov002_PanelResolveGroupRow - work out what a group row would do if it were
 * chosen, and remember where it points.
 *
 * The answer is the group the row ends up acting as. A keyed row (group 3)
 * keeps its group only while the entry behind it still has a count and passes
 * both key tests, and then it resolves to group 0xb and records the list
 * position of its key; anything else buzzes and falls back to the empty group.
 * A cell row (group 8) walks the fifteen cells for its key, records the cell it
 * lands on, and buzzes back to empty when that cell is not live. The empty row
 * itself just buzzes.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nKey;                           /* +0x00 */
    u16 wCount;                         /* +0x02 */
} Ov002PanelSubEntry;

typedef struct {
    u16 nGroup;                         /* +0x00 */
    u16 pad0002;
    u8 *pKeyRef;                        /* +0x04 */
    Ov002PanelSubEntry *pEntry;         /* +0x08 */
    u16 nKey;                           /* +0x0c */
    u16 pad000e;
} Ov002PanelGroupSlot;

typedef struct {
    u8 pad0000[5];
    u8 bCellIndex;                      /* +0x005 */
    u8 bListIndex;                      /* +0x006 */
    u8 pad0007[0x2b];
    u8 aCells[0x40e];                   /* +0x032 */
    Ov002PanelGroupSlot aGroups[4];     /* +0x440 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_02033b24(int nId, int nKind);

extern int func_ov002_0205a598(int *pOut, unsigned int nKey);
extern int func_ov002_0205a600(int nCell);
extern int func_ov002_0205a714(int nGroup, unsigned int nKey);
extern int func_ov002_0205a730(int nGroup, unsigned int nKey);

int func_ov002_0205da24(int nRow)
{
    Ov002PanelSession *s;
    Ov002PanelSession *pWalk;
    Ov002PanelGroupSlot *pGroup;
    Ov002PanelSubEntry *pEntry;
    int nGroup;
    int nCell;

    s = data_ov002_0207f620;
    pGroup = &s->aGroups[nRow];
    nGroup = pGroup->nGroup;
    switch (nGroup) {
    default:
        if (nGroup == 8 && pGroup->pKeyRef != 0) {
            nCell = 0;
            pWalk = s;
            do {
                if (*pGroup->pKeyRef == pWalk->aCells[0]) {
                    s->bCellIndex = (u8)nCell;
                    break;
                }
                nCell++;
                pWalk = (Ov002PanelSession *)((char *)pWalk + 2);
            } while (nCell < 0xf);
            if (func_ov002_0205a600(nCell) == 0) {
                nGroup = 7;
                func_02033b24(0, 4);
            }
        }
        break;

    case 3:
        pEntry = pGroup->pEntry;
        if (pEntry == 0 || pEntry->wCount == 0) {
            nGroup = 7;
            func_02033b24(0, 4);
        } else if (func_ov002_0205a714(0, pEntry->nKey) != 0
                   && func_ov002_0205a730(0, pGroup->pEntry->nKey) != 0) {
            func_ov002_0205a598(&nCell, pGroup->nKey);
            nGroup = 0xb;
            s->bListIndex = (u8)nCell;
        } else {
            nGroup = 7;
            func_02033b24(0, 4);
        }
        break;

    case 7:
        func_02033b24(0, 4);
        break;
    }
    return nGroup;
}
