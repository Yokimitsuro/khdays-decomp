/* Find the entry with this key in the panel's first list, and hand back its
 * position through the optional out-parameter. Returns null when the key is not
 * on the list; the position then counts the whole list. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nKey;
    u16 nTag;
    void *pObject;
    u8 pad0008[0x10];
} Ov002PanelSubEntry;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u8 pad0000[0x480];
    NNSFndList lists[3];        /* +0x480 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern Ov002PanelSubEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                    Ov002PanelSubEntry *pPrev);

Ov002PanelSubEntry *func_ov002_0205a598(int *pnIndex, int nKey) {
    Ov002PanelSubEntry *pEntry;
    int nIndex = 0;

    pEntry = NNS_FndGetNextListObject(&data_ov002_0207f620->lists[0], 0);
    while (pEntry != 0) {
        if (pEntry->nKey == nKey) {
            break;
        }
        nIndex++;
        pEntry = NNS_FndGetNextListObject(&data_ov002_0207f620->lists[0], pEntry);
    }

    if (pnIndex != 0) {
        *pnIndex = nIndex;
    }
    return pEntry;
}
