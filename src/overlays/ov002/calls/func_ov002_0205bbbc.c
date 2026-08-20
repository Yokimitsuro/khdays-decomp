/* Rebuilds the panel's six slot descriptors for whatever the classifier makes of
 * nRaw, and hands nRaw back unchanged.
 *
 * The classifier turns the raw code into a kind and a page, and each kind fills
 * the slots its own way. Kind 0 is the fixed three-entry header, whose middle and
 * last slots become availability flags. Kinds 1 to 3 are paged lists - columns,
 * the first list and the second list - and each re-classifies from its own stored
 * index when the page and the mode are both zero, clamps the remaining count to
 * six, fills that many slots and pads the rest with 7. Kind 4 copies the four
 * group ids. Kind 5 reads the cached sub-entry and marks it available or not.
 *
 * Four shapes here are load-bearing rather than style. The classifier scratch is
 * a single int, because the ROM reserves only four bytes of stack. Kind 5 is
 * listed BEFORE kind 4, which is the order the ROM emits them. Every slot loop is
 * a for, not a hand-guarded do-while, so the guard tests the count just stored.
 * The page index handed to the list walk is narrowed to 16 bits. And kind 5's two
 * failure paths converge on one assignment, which is why they are written as a
 * single && rather than an if/else-if/else chain.
 *
 * data_ov002_0207e9f4 and data_ov002_0207e9f4_default are the SAME address under
 * two names, and that is required, not cosmetic: the ROM's literal pool holds the
 * table address in two separate entries, and mwcc emits two only for two distinct
 * symbols. With one name the second read reuses the register already holding the
 * base and the second entry never exists. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 nKey;                       /* +0x00 */
    u16 nTag;                       /* +0x02 */
    void *pObject;                  /* +0x04 */
    u8 pad0008[16];
} Ov002PanelSubEntry;

typedef struct {
    u16 nGroup;                     /* +0x00 */
    u8 pad0002[14];
} Ov002PanelGroupSlot;

typedef struct {
    u8 bKind;                       /* +0x000 */
    u8 bMode;                       /* +0x001 */
    u8 bIndex;                      /* +0x002 */
    u8 bListIndex;                  /* +0x003 */
    u8 bKey;                        /* +0x004 */
    u8 pad0005[15];
    u16 wPrimaryRow;                /* +0x014 */
    u16 wField0016;
    u8 bSlotCount;                  /* +0x018 */
    u8 pad0019;
    u16 aSlots[11];                 /* +0x01a */
    u8 bColumns;                    /* +0x030 */
    u8 pad0031[0x40f];
    Ov002PanelGroupSlot aGroups[4];  /* +0x440 */
    u8 lists[3][12];                /* +0x480 */
    Ov002PanelSubEntry *pCachedEntry;   /* +0x4a4 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;
extern u16 data_ov002_0207e9f4[];
extern u16 data_ov002_0207e9f4_default[];

extern int func_ov002_0205a3f0(int *pOut, int nCode);
extern int func_ov002_0205a638(void);
extern int func_ov002_0205a7b8(void);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a714(int a, int nKey);
extern int func_02010154(void *pList, int nIndex);
extern void *NNS_FndGetNextListObject(void *pList, void *pObject);

int func_ov002_0205bbbc(int nRaw) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass;
    int nKind;
    int nCount;
    void *pObj;
    int i;

    nKind = func_ov002_0205a3f0(&nClass, nRaw);
    switch (nKind) {
    case 0:
        s->bSlotCount = 3;
        s->aSlots[0] = data_ov002_0207e9f4[s->wPrimaryRow];
        s->aSlots[2] = data_ov002_0207e9f4_default[4];
        s->aSlots[1] = (u16)(func_ov002_0205a638() != 0 ? 1 : 7);
        s->aSlots[2] = (u16)(func_ov002_0205a7b8() != 0 ? 2 : 7);
        break;

    case 1:
        if (nClass == 0 && s->bMode == 0) {
            nRaw = s->bIndex / 6 + 1;
            func_ov002_0205a3f0(&nClass, nRaw);
            s->bKind = (u8)(s->bIndex % 6);
        }
        nCount = s->bColumns - nClass * 6;
        if (nCount > 6) {
            nCount = 6;
        }
        s->bSlotCount = (u8)nCount;
        for (i = 0; i < s->bSlotCount; i++) {
            s->aSlots[i] = 8;
        }
        for (; i < 6; i++) {
            s->aSlots[i] = 7;
        }
        break;

    case 2:
        if (nClass == 0 && s->bMode == 0) {
            nRaw = s->bListIndex / 6 + 4;
            func_ov002_0205a3f0(&nClass, nRaw);
            s->bKind = (u8)(s->bListIndex % 6);
        }
        nCount = func_ov002_0205a4a0() - nClass * 6;
        if (nCount > 6) {
            nCount = 6;
        }
        s->bSlotCount = (u8)nCount;
        pObj = (void *)func_02010154(&s->lists[0], (u16)(nClass * 6));
        for (i = 0; i < s->bSlotCount; i++) {
            if (pObj == 0) {
                break;
            }
            s->aSlots[i] = 3;
            pObj = NNS_FndGetNextListObject(&s->lists[0], pObj);
        }
        for (; i < 6; i++) {
            s->aSlots[i] = 7;
        }
        break;

    case 3:
        if (nClass == 0 && s->bMode == 0) {
            nRaw = s->bKey / 6 + 6;
            func_ov002_0205a3f0(&nClass, nRaw);
            s->bKind = (u8)(s->bKey % 6);
        }
        nCount = func_ov002_0205a4ec() - nClass * 6;
        if (nCount > 6) {
            nCount = 6;
        }
        s->bSlotCount = (u8)nCount;
        pObj = (void *)func_02010154(&s->lists[2], (u16)(nClass * 6));
        for (i = 0; i < s->bSlotCount; i++) {
            if (pObj == 0) {
                break;
            }
            s->aSlots[i] = 4;
            pObj = NNS_FndGetNextListObject(&s->lists[2], pObj);
        }
        for (; i < 6; i++) {
            s->aSlots[i] = 7;
        }
        break;


    case 5:
        if (s->pCachedEntry == 0) {
            break;
        }
        if (s->pCachedEntry->pObject != 0
                && func_ov002_0205a714(0, s->pCachedEntry->nKey) != 0) {
            nCount = 0xc;
        } else {
            nCount = 7;
        }
        s->aSlots[0] = (u16)nCount;
        s->aSlots[1] = 0xd;
        break;

    case 4:
        s->bSlotCount = 4;
        for (i = 0; i < s->bSlotCount; i++) {
            s->aSlots[i] = s->aGroups[i].nGroup;
        }
        break;
    }

    return nRaw;
}
