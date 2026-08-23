/*
 * Ov002_PanelAssignRowFromCursor - drop whatever the cursor is pointing at onto
 * one of the four group rows.
 *
 * From the grid the row takes the cell the cursor is on; from the first list it
 * takes the entry's key, and only when that entry still exists. Either way the
 * ring is repainted, the span strip covering it is redrawn, and the confirmation
 * sound plays.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 wKey;                           /* +0x00 */
    u16 wTag;                           /* +0x02 */
} Ov002PanelEntry;

typedef struct {
    u8 pad0000;
    u8 bMode;                           /* +0x001 */
    u8 bIndex;                          /* +0x002 */
    u8 bListIndex;                      /* +0x003 */
    u8 pad0004[0x2d];
    u8 bCursorRow;                      /* +0x031 */
    u8 aCells[0x44e];                   /* +0x032 */
    u8 aFirstList[0xc];                 /* +0x480 */
    u8 pad048c[0x20];
    u8 bListRowBase;                    /* +0x4ac */
    u8 bListRowOffset;                  /* +0x4ad */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_02033b78(int nId, int nKind);
extern Ov002PanelEntry *func_02010154(void *pList, unsigned int nIndex);

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern void func_ov002_0205a924(int nFirst, int nLast, int nGroup, int nKind);
extern void func_ov002_0205ba3c(int nRow, unsigned int nGroup, unsigned int nKey);
extern void func_ov002_0205c624(int nRow);
extern void func_ov002_0205c6f4(int nMode);

void func_ov002_0205e2c4(int nRow)
{
    Ov002PanelSession *s;
    Ov002PanelEntry *pEntry;
    int nPos;

    s = data_ov002_0207f620;
    switch (func_ov002_0205a3f0(&nPos, s->bMode)) {
    case 1:
        func_ov002_0205ba3c(nRow, 8, s->aCells[s->bIndex * 2]);
        func_ov002_0205c624(nPos);
        func_ov002_0205a924(nPos + 1, s->bCursorRow, 7, 0xb);
        func_02033b78(0, 0);
        break;

    case 2:
        pEntry = func_02010154(s->aFirstList, s->bListIndex);
        if (pEntry != 0) {
            func_ov002_0205ba3c(nRow, 3, pEntry->wKey);
            func_ov002_0205c6f4(s->bMode);
            func_ov002_0205a924(nPos + 1, s->bListRowBase + s->bListRowOffset, 7,
                                0xb);
            func_02033b78(0, 0);
        }
        break;
    }
}
