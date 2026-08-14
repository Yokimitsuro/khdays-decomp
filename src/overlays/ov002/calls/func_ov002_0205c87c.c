/* Repaint one group of six rows backed by the second tracked list.
 *
 * Unlike the sibling list group there is no classifier: the list is entered
 * directly at ordinal nGroup*6, and rows are always drawn enabled. What varies
 * per row is the alt flag, which comes from the module ownership query on the
 * low byte of the entry's tag -- so this group's palette follows ownership
 * rather than a filter. Slots the list cannot fill are repainted as empty rows,
 * and the header widget tag is fixed rather than chosen from the panel state.
 *
 * The row ordinal is written as nGroup*6 + i and left for mwcc to strength
 * reduce. The ROM increments it, so carrying an explicit counter in the source
 * lands the value in the wrong register -- which is the opposite of what the
 * plain group repaint needs, where the ROM recomputes and the base has to be
 * hoisted by hand. Read the ROM: an incremented register means write the affine
 * expression, a recomputed one means hoist the base.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u16 nKey;               /* +0x00 */
    u16 nTag;               /* +0x02 */
} Ov002PanelEntry;

typedef struct {
    u8 bKind;                   /* +0x00 */
    u8 pad0001[0x47f];
    NNSFndList lists[3];        /* +0x480 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0206dc10(int nKey);
extern int func_ov002_0205a540(int nKey);
extern void func_ov002_0205b0dc(NNSFndList *pList, int nIndex, int nSlot,
                                int nEntry, int nColumn, int bEnabled,
                                int bRightAlign, int bAlt);
extern int func_ov002_02053558(int nTag);
extern void func_ov002_02053578(int nHandle, short nValue, short nKind);
extern void func_ov002_020535a4(int nHandle);
extern void func_ov002_02053cd4(int nItemId);
extern Ov002PanelEntry *func_02010154(NNSFndList *pList, u16 nIndex);
extern Ov002PanelEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                 Ov002PanelEntry *pObject);

void func_ov002_0205c87c(int nGroup) {
    int i;
    Ov002PanelEntry *pEntry;
    int nHandle;
    Ov002PanelSession *s;

    s = data_ov002_0207f620;
    i = 0;
    pEntry = func_02010154(&s->lists[2], nGroup * 6);

    if (pEntry != 0) {
        do {
            int bAlt;
            int bRight;
            int nIndex;

            bAlt = func_ov002_0206dc10(pEntry->nTag & 0xff);
            bRight = s->bKind == i;
            nIndex = func_ov002_0205a540(pEntry->nKey);

            func_ov002_0205b0dc(&s->lists[2], nIndex, i, nGroup * 6 + i, 1, 1,
                                bRight, bAlt);
            i++;
            pEntry = NNS_FndGetNextListObject(&s->lists[2], pEntry);
        } while (i < 6 && pEntry != 0);
    }

    for (; i < 6; i++) {
        func_ov002_0205b0dc(&s->lists[2], -1, i, 0, 1, 0, s->bKind == i, 0);
    }

    nHandle = func_ov002_02053558(0x64);
    func_ov002_02053578(nHandle, 1, 0xa);
    func_ov002_020535a4(nHandle);
    func_ov002_02053cd4(0xb);
}
