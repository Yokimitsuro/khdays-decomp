/* Build the value pair for a list-class panel widget.
 *
 * Fetches the entry at index nIndex+2 of pList, reads its tag, then reads the
 * tag of the entry that follows it in the session's first list, and hands both
 * plus nKind to the same formatter the cell-array path feeds from two adjacent
 * cells. A non-zero bSuppress skips the lookup entirely, so the formatter sees
 * a zero pair; the panel repaint passes 1 there for its third list class.
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
    u8 pad0000[0x480];
    NNSFndList lists[3];    /* +0x480 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern Ov002PanelEntry *func_02010154(NNSFndList *pList, u16 nIndex);
extern Ov002PanelEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                 Ov002PanelEntry *pObject);
extern int func_ov002_0205b728(int nFirst, int nSecond, int nKind);

int func_ov002_0205b778(NNSFndList *pList, int nIndex, int nKind,
                        int bSuppress) {
    int nFirst = 0;
    int nSecond = 0;

    if (bSuppress == 0) {
        Ov002PanelEntry *pEntry = func_02010154(pList, nIndex + 2);

        if (pEntry != 0) {
            Ov002PanelSession *s = data_ov002_0207f620;

            nFirst = pEntry->nTag;
            pEntry = NNS_FndGetNextListObject(&s->lists[0], pEntry);
            if (pEntry != 0) {
                nSecond = pEntry->nTag;
            }
        }
    }
    return func_ov002_0205b728(nFirst, nSecond, nKind);
}
