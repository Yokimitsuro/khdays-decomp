/*
 * Ov002_PanelSetEntryTag - put an entry in the panel's live list or take it out
 * again, and keep everything that depends on the list in step.
 *
 * A key that no slot recognises is ignored. A key that is not in the live list
 * yet joins it under the first spare node - the spare list is searched for a
 * node that already carries the key, and the head is taken when none does - and
 * the node picks up the slot's own word. A key that is already there just takes
 * the new tag, unless the tag is zero, in which case the entry leaves the list:
 * any group row pointing at it is emptied first, the cursor is pulled back a row
 * if the entry sat above it, and the row count is recomputed.
 *
 * The ring is then rebuilt: the slot ring refreshes its header, the first list
 * closes itself when it has just become empty, and the mode that owns its own
 * rows rebuilds them.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 wKey;                           /* +0x00 */
    u16 wTag;                           /* +0x02 */
    int nSlotWord;                      /* +0x04 */
} Ov002PanelEntry;

typedef struct {
    u16 nGroup;                         /* +0x00 */
    u16 pad0002;
    u8 *pKeyRef;                        /* +0x04 */
    u16 *pEntry;                        /* +0x08 */
    u16 nKey;                           /* +0x0c */
    u16 pad000e;
} Ov002PanelGroupSlot;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002;
    u8 bListIndex;                      /* +0x003 */
    u8 pad0004[0xc];
    int nState;                         /* +0x010 */
    u8 pad0014[0x42c];
    Ov002PanelGroupSlot aGroups[4];     /* +0x440 */
    u8 aFirstList[0xc];                 /* +0x480 */
    u8 aSpareList[0xc];                 /* +0x48c */
    u8 pad0498[0x14];
    u8 bListRowBase;                    /* +0x4ac */
    u8 pad04ad[0xf];
    int aSlotWords[1];                  /* +0x4bc, stride 0xc */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void *NNS_FndGetNextListObject(void *pList, void *pObject);
extern void NNS_FndRemoveListObject(void *pList, void *pObject);
extern void NNS_FndAppendListObject(void *pList, void *pObject);
extern long long func_02020400(int nNum, int nDen);

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a540(unsigned int nKey);
extern Ov002PanelEntry *func_ov002_0205a598(int *pPos, unsigned int nKey);
extern int func_ov002_0205a7b8(void);
extern void func_ov002_0205ae08(int nSource, int nFlag, int bFirst);
extern void func_ov002_0205ba3c(int nRow, unsigned int nGroup, unsigned int nKey);
extern void func_ov002_0205bfa8(void);
extern void func_ov002_0205c9c4(void);
extern void func_ov002_0205cc44(void);
extern void func_ov002_0205d214(int nTarget, int nValue);

void func_ov002_0205de68(unsigned int nKey, unsigned short nTag)
{
    Ov002PanelSession *s;
    Ov002PanelEntry *pEntry;
    Ov002PanelGroupSlot *pGroup;
    int nSlot;
    int nPos;
    int nClass;
    int i;
    int bSecond;
    int bAvailable;

    s = data_ov002_0207f620;
    nPos = 0;
    pEntry = func_ov002_0205a598(&nPos, nKey);
    nSlot = func_ov002_0205a540(nKey);
    if (nSlot < 0) {
        return;
    }

    if (pEntry == 0) {
        if (nTag != 0) {
            pEntry = (Ov002PanelEntry *)NNS_FndGetNextListObject(s->aSpareList,
                                                                 pEntry);
            while (pEntry != 0) {
                if (pEntry->wKey == nKey) {
                    break;
                }
                pEntry = (Ov002PanelEntry *)NNS_FndGetNextListObject(
                    s->aSpareList, pEntry);
            }
            if (pEntry == 0) {
                pEntry = (Ov002PanelEntry *)NNS_FndGetNextListObject(s->aSpareList,
                                                                    0);
            }
            pEntry->wKey = nKey;
            pEntry->nSlotWord = *(int *)((char *)s + nSlot * 0xc + 0x4bc);
            pEntry->wTag = nTag;
            NNS_FndRemoveListObject(s->aSpareList, pEntry);
            NNS_FndAppendListObject(s->aFirstList, pEntry);
            s->bListRowBase = (u8)func_02020400(func_ov002_0205a4a0() + 5, 6);
        }
    } else {
        pEntry->wTag = nTag;
        if (nTag == 0) {
            i = 0;
            pGroup = s->aGroups;
            do {
                if (pGroup->nGroup == 3 && *pGroup->pEntry == nKey) {
                    func_ov002_0205ba3c(i, 7, 0);
                    break;
                }
                i++;
                pGroup++;
            } while (i < 4);
            NNS_FndRemoveListObject(s->aFirstList, pEntry);
            NNS_FndAppendListObject(s->aSpareList, pEntry);
            if (nPos > 0 && nPos <= s->bListIndex) {
                s->bListIndex--;
            }
            s->bListRowBase = (u8)func_02020400(func_ov002_0205a4a0() + 5, 6);
        } else {
            pEntry->wTag = nTag;
        }
    }

    func_ov002_0205cc44();
    func_ov002_0205bfa8();
    nClass = func_ov002_0205a3f0(0, s->bMode);
    switch (nClass) {
    default:
        if (nClass == 4) {
            func_ov002_0205c9c4();
        }
        break;

    case 2:
        if (func_ov002_0205a4a0() == 0 && s->nState != 0) {
            s->nState = 0;
            func_ov002_0205d214(9, -1);
        }
        break;

    case 0:
        if (s->bKind == 2) {
            bSecond = 1;
        } else {
            bSecond = 0;
        }
        if (func_ov002_0205a7b8() != 0) {
            bAvailable = 1;
        } else {
            bAvailable = 0;
        }
        func_ov002_0205ae08(4, bAvailable, bSecond);
        break;
    }
}
