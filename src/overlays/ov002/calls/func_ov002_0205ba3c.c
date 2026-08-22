/*
 * Ov002_PanelAssignGroupRow - put a group and key on one of the panel rows,
 * taking it off whichever row already held it.
 *
 * Both rows are wiped and parked on group 7, the empty one, before anything
 * else, and the saved copy in the game state is parked with them. Only then is
 * the row filled in, and only if the request resolves: group 3 needs a list
 * entry with a non-zero count, and group 8 needs one of the live cells to carry
 * the key. Anything else - or a request that resolves to nothing - leaves the
 * row empty, which is why the wipe comes first.
 *
 * The game state keeps its own halfword pair per row so the assignment
 * survives the panel being torn down.
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
    u16 nKey;                           /* +0x00 */
    u16 wCount;                         /* +0x02 */
} Ov002PanelSubEntry;

typedef struct {
    u16 nGroup;                         /* +0x00 */
    u16 pad0002;
    u8 *pKeyRef;                        /* +0x04 */
    u16 *pEntry;                        /* +0x08 */
    u16 nKey;                           /* +0x0c */
    u16 pad000e;
} Ov002PanelGroupSlot;

typedef struct {
    u8 pad0000[0x30];
    u8 bColumns;                        /* +0x030 */
    u8 pad0031;
    Ov002PanelCell aCells[0xf];         /* +0x032 */
    u8 pad0050[0x3f0];
    Ov002PanelGroupSlot aGroups[4];     /* +0x440 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;
extern int data_0204be18;

extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern Ov002PanelSubEntry *func_ov002_0205a598(int nGroup, unsigned int nKey);
extern int func_ov002_0205af40(unsigned int nGroup, unsigned int nKey);

void func_ov002_0205ba3c(int nRow, unsigned int nGroup, unsigned int nKey)
{
    Ov002PanelSession *s;
    Ov002PanelGroupSlot *pGroup;
    Ov002PanelSubEntry *pEntry;
    int nOther;
    int i;

    s = data_ov002_0207f620;
    pGroup = &s->aGroups[nRow];
    nOther = func_ov002_0205af40(nGroup, nKey);
    if (nOther >= 0) {
        MI_CpuFill8(&s->aGroups[nOther], 0, 0x10);
        s->aGroups[nOther].nGroup = 7;
        *(u16 *)(data_0204be18 + nOther * 4 + 0xfd0) = 7;
        *(u16 *)(data_0204be18 + nOther * 4 + 0xfd2) = 0;
    }
    MI_CpuFill8(pGroup, 0, 0x10);
    pGroup->nGroup = 7;

    switch (nGroup) {
    case 8:
        for (i = 0; i < s->bColumns; i++) {
            if (nKey == s->aCells[i].bFirst) {
                pGroup->pKeyRef = &s->aCells[i].bFirst;
                pGroup->nGroup = (u16)nGroup;
                *(u16 *)(data_0204be18 + nRow * 4 + 0xfd0) = (u16)nGroup;
                *(u16 *)(data_0204be18 + nRow * 4 + 0xfd2) = nKey;
                return;
            }
        }
        break;
    case 3:
        pEntry = func_ov002_0205a598(0, nKey);
        if (pEntry != 0 && pEntry->wCount != 0) {
            pGroup->nGroup = (u16)nGroup;
            pGroup->nKey = (u16)nKey;
            pGroup->pEntry = (u16 *)pEntry;
            *(u16 *)(data_0204be18 + nRow * 4 + 0xfd0) = (u16)nGroup;
            *(u16 *)(data_0204be18 + nRow * 4 + 0xfd2) = (u16)nKey;
        }
        break;
    }
}
