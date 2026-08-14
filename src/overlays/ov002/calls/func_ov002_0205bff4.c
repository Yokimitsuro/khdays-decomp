#pragma opt_common_subs off
#pragma opt_dead_assignments off

typedef unsigned char u8;
typedef unsigned short u16;

typedef enum {
    PANEL_CLASS_PRIMARY = 0,
    PANEL_CLASS_GRID = 1,
    PANEL_CLASS_ITEMS = 2,
    PANEL_CLASS_ENTRIES = 3,
    PANEL_CLASS_NONE = 4,
    PANEL_CLASS_SPECIAL = 5
} Ov002PanelClass;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nCount;
    u16 nLinkOffset;
} NNSFndList;

typedef struct {
    u16 nKey;
    u16 nTag;
    int nState;
} Ov002PanelEntry;

typedef struct {
    u8 bKind;
    u8 bMode;
    u8 bIndex;
    u8 bListIndex;
    u8 bKey;
    u8 pad0005[2];
    u8 bDefaultKind;
    u8 pad0008[4];
    int nField000c;
    u8 pad0010[4];
    u16 wField0014;
    u8 pad0016[0x1c];
    u8 aBitIndex[0x44e];
    NNSFndList lists[3];
    Ov002PanelEntry *pCachedEntry;
} Ov002PanelSession;

typedef struct {
    int nFrom;
    int nTo;
    int nClass;
    int nTagOrder;
    int bSpecialEnabled;
} Ov002PanelMoveState;

extern Ov002PanelSession *volatile data_ov002_0207f620;

extern int func_ov002_0205a3f0(int *pOut, int nCode);
extern int func_ov002_020536bc(int nTag);
extern int func_ov002_0205374c(int nEntry);
extern int func_ov002_02053558(int nId);
extern void func_ov002_020535f0(int nEntry);
extern void func_ov002_0205b7dc(int nMode, int nKind, int nFlag);
extern void func_ov002_0205ae08(int nSlot, int nValue, int nFlag);
extern int func_ov002_0205a638(void);
extern void func_ov002_0205aba4(int a, int b, int c, int d);
extern void func_ov002_0205ab90(int a, int b, int c, int d);
extern Ov002PanelEntry *NNS_FndGetNextListObject(NNSFndList *pList,
                                                 Ov002PanelEntry *pPrev);
extern int func_ov002_0205a7b8(void);
extern int func_ov002_0205a600(int nIndex);
extern void func_ov002_0205afb4(int nIndex, int nSub, int a, int b, int c);
extern Ov002PanelEntry *func_02010154(NNSFndList *pList, u16 nIndex);
extern int func_ov002_0205a714(int a, int nKey);
extern int func_ov002_0205a730(int a, int nKey);
extern int func_ov002_0205a540(int nKey);
extern void func_ov002_0205b0dc(NNSFndList *pList, int nSlot, int nSub, int nIndex,
                                int a, int b, int c, int d);
extern int func_ov002_0206dc10(int nTag);
extern void func_ov002_0205ad5c(int a, int b, int c, u16 nColour, int d);
extern void func_ov002_0205abe0(int a, int b, int c);
extern void func_ov002_02053cd4(int nId);

void func_ov002_0205bff4(int nFrom, int nTo) {
    int nColumn;
    int nTag;
    Ov002PanelSession *s;
    Ov002PanelMoveState state;

    state.nTo = nTo;
    state.nFrom = nFrom;

#define nClass state.nClass
#define nFrom state.nFrom
#define nTo state.nTo

    s = data_ov002_0207f620;
    nClass = func_ov002_0205a3f0(&nColumn, s->bMode);
    state.nTagOrder = 0;

    if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
        func_ov002_020535f0(func_ov002_02053558(0x79));
    }
    func_ov002_0205b7dc(s->bMode, nTo, 0);

    switch (nClass) {
    case 0:
        switch (nFrom) {
        case 0:
            func_ov002_0205ae08(s->wField0014, s->nField000c, 0);
            break;
        case 1: {
            int nValue = func_ov002_0205a638();

            func_ov002_0205aba4(4, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
        }
        case 2: {
            int nValue;
            Ov002PanelEntry *pObject = NNS_FndGetNextListObject(&s->lists[0], 0);

            if (pObject == 0) {
                pObject = NNS_FndGetNextListObject(&s->lists[2], 0);
            }
            if (pObject != 0 && func_ov002_0205a7b8() != 0) {
                nValue = 1;
            } else {
                nValue = 0;
            }
            func_ov002_0205ab90(5, 0, 0, 0);
            func_ov002_0205ae08(nFrom + 2, nValue, 0);
            break;
        }
        }

        switch (nTo) {
        case 0:
            func_ov002_0205ae08(s->wField0014, s->nField000c, 1);
            break;
        case 1:
            if (s->aBitIndex[0] == 0xff) {
                func_ov002_0205ae08(3, 0, 1);
            } else {
                func_ov002_0205ae08(3, 1, 1);
            }
            break;
        case 2:
            func_ov002_0205ae08(4, 1, 1);
            break;
        }
        break;

    case 1: {
        int nOffset = nColumn * 6;
        int nIndex;

        func_ov002_0205afb4(nFrom + nOffset, nFrom, 1,
                            func_ov002_0205a600(nFrom + nOffset), 0);
        nIndex = nColumn * 6 + nTo;
        func_ov002_0205afb4(nIndex, nTo, 1, func_ov002_0205a600(nIndex), 1);
        s->bIndex = (u8)nIndex;
        break;
    }

    case 2: {
        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
        int bFlag;
        Ov002PanelEntry *pEntry;
        int nSlot;

        pEntry = func_02010154(&s->lists[0], (u16)nOld);
        bFlag = 0;
        if (func_ov002_0205a714(0, pEntry->nKey) != 0 &&
            func_ov002_0205a730(0, pEntry->nKey) != 0) {
            bFlag = 1;
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(pEntry->nKey);
        }
        func_ov002_0205b0dc(&s->lists[0], nSlot, nFrom, nOld, 1, bFlag, 0, 0);

        {
        Ov002PanelEntry *pNewEntry;
        int bNewFlag;

        pNewEntry = 0;
        pNewEntry = func_02010154(&s->lists[0], (u16)nNew);
        bNewFlag = 0;
        if (func_ov002_0205a714(0, pNewEntry->nKey) != 0 &&
            func_ov002_0205a730(0, pNewEntry->nKey) != 0) {
            bNewFlag = 1;
        }
        if (pNewEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(pNewEntry->nKey);
        }
        func_ov002_0205b0dc(&s->lists[0], nSlot, nTo, nNew, 1, bNewFlag, 1, 0);
        }
        s->bListIndex = (u8)(nColumn * 6 + nTo);
        break;
    }

    case 3: {
        int nOld;
        Ov002PanelEntry *pEntry;
        int nSlot;

        nOld = 0;
        nOld = nFrom + nColumn * 6;
        nClass = nTo + nColumn * 6;

        pEntry = func_02010154(&s->lists[2], (u16)nOld);
        nTag = 0;
        if (pEntry != 0) {
            nTag = func_ov002_0206dc10(pEntry->nTag & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(pEntry->nKey);
        }
        func_ov002_0205b0dc(&s->lists[2], nSlot, nFrom, nOld, 1, 1, 0,
                            nTag);

        pEntry = func_02010154(&s->lists[2], (u16)nClass);
        if (pEntry != 0) {
            nTag = func_ov002_0206dc10(pEntry->nTag & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = func_ov002_0205a540(pEntry->nKey);
        }
        func_ov002_0205b0dc(&s->lists[2], nSlot, nTo, nClass, 1, 1, 1,
                            nTag);
        s->bKey = (u8)nClass;
        s->pCachedEntry = pEntry;
        break;
    }

    case 4:
        break;

    case 5: {
        u16 nKey = s->pCachedEntry->nKey;

        state.bSpecialEnabled = 0;

        if (s->pCachedEntry->nState != 0 &&
            func_ov002_0205a714(0, nKey) != 0 &&
            func_ov002_0205a730(0, nKey) != 0) {
            state.bSpecialEnabled = 1;
        }
        if (nTo == 0) {
            func_ov002_0205ad5c(4, 0, 0x3e0,
                                (u16)(state.bSpecialEnabled != 0 ? 0xf : 0xe), 1);
            func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, 0);
            func_ov002_0205abe0(4, 0, 0);
            func_ov002_0205abe0(5, 1, 0);
            s->bDefaultKind = 0;
        } else {
            func_ov002_0205ad5c(4, 0, 0x3e0,
                                (u16)(state.bSpecialEnabled != 0 ? 0xf : 0xe), 0);
            func_ov002_0205ad5c(5, 0, 0x3f0, 0xf, 1);
            func_ov002_0205abe0(4, 1, 0);
            func_ov002_0205abe0(5, 0, 0);
            s->bDefaultKind = 1;
        }
        break;
    }
    }

    s->bKind = (u8)nTo;
    func_ov002_0205b7dc(s->bMode, nTo, 0);
    func_ov002_02053cd4(9);
    func_ov002_02053cd4(0xb);

#undef nClass
#undef nTo
#undef nFrom
}

