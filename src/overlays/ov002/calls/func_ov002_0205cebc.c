/* Drop the (key, tag) pair from the panel's second entry list and refresh the
 * row offset the cursor stepper reads. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nKey;
    u16 nTag;
    int nState;
} Ov002PanelEntry;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u8 pad0000[0x480];
    NNSFndList lists[3];            /* +0x480 */
    Ov002PanelEntry *pCachedEntry;  /* +0x4a4 */
    u8 pad04a8[5];
    u8 bListRowOffset;              /* +0x4ad */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern Ov002PanelEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                 Ov002PanelEntry *pPrev);
extern void NNS_FndRemoveListObject(NNSFndList *pList, Ov002PanelEntry *pObject);
extern int func_ov002_0205a4ec(void);

void func_ov002_0205cebc(int nKey, int nTag) {
    Ov002PanelSession *s = data_ov002_0207f620;
    Ov002PanelEntry *pEntry;

    pEntry = NNS_FndGetNextListObject(&s->lists[2], 0);
    while (pEntry != 0) {
        if (pEntry->nKey == nKey && pEntry->nTag == nTag) {
            pEntry->nKey = 0;
            NNS_FndRemoveListObject(&s->lists[2], pEntry);
            s->pCachedEntry = 0;
            break;
        }
        pEntry = NNS_FndGetNextListObject(&s->lists[2], pEntry);
    }

    s->bListRowOffset = (u8)((func_ov002_0205a4ec() + 5) / 6);
}
