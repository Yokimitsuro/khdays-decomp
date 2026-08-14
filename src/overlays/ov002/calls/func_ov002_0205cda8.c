/* Add a (key, tag) pair to the panel's sub-entry list: take the first blank
 * record, copy the object pointer out of the slot the key resolves to, and
 * splice the record into the list in ascending key order. Fails when the key
 * has no slot, the slot index is out of range or every record is taken. */
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
    void *pObject;
    u8 pad0004[8];
} Ov002PanelSlotRecord;

typedef struct {
    u8 pad0000[0x290];
    Ov002PanelSubEntry aSubEntries[0x12];   /* +0x290 */
    u8 pad0440[0x40];
    NNSFndList lists[3];                    /* +0x480 */
    void *pCachedEntry;                     /* +0x4a4 */
    u8 pad04a8[5];
    u8 bListRowOffset;                      /* +0x4ad */
    u8 pad04ae[0xe];
    Ov002PanelSlotRecord aSlots[1];         /* +0x4bc */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern Ov002PanelSubEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                    Ov002PanelSubEntry *pPrev);
extern void NNS_FndAppendListObject(NNSFndList *pList,
                                    Ov002PanelSubEntry *pObject);
extern void NNS_FndInsertListObject(NNSFndList *pList,
                                    Ov002PanelSubEntry *pBefore,
                                    Ov002PanelSubEntry *pObject);
extern int func_ov002_0205a540(unsigned int nKey);
extern int func_ov002_0205a4ec(void);

int func_ov002_0205cda8(unsigned int nKey, int nTag) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int nSlot = func_ov002_0205a540(nKey);
    Ov002PanelSubEntry *pAt;
    int i;

    for (i = 0; i < 0x12; i++) {
        if (s->aSubEntries[i].nKey == 0) {
            break;
        }
    }

    if (nSlot == -1 || !(nSlot < 0x18 && i < 0x12)) {
        return 0;
    }

    pAt = NNS_FndGetNextListObject(&s->lists[2], 0);
    while (pAt != 0) {
        if (pAt->nKey >= nKey) {
            break;
        }
        pAt = NNS_FndGetNextListObject(&s->lists[2], pAt);
    }

    s->aSubEntries[i].nKey = (u16)nKey;
    s->aSubEntries[i].nTag = (u16)nTag;
    s->aSubEntries[i].pObject = s->aSlots[nSlot].pObject;
    if (pAt != 0) {
        NNS_FndInsertListObject(&s->lists[2], pAt, &s->aSubEntries[i]);
    } else {
        NNS_FndAppendListObject(&s->lists[2], &s->aSubEntries[i]);
    }

    s->bListRowOffset = (u8)((func_ov002_0205a4ec() + 5) / 6);
    return 1;
}
