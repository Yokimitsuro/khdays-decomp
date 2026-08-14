typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x;
    int y;
} CtxPair;

typedef struct {
    u8 bKind;
    u8 bMode;
    u8 bIndex;
    u8 bListIndex;
    u8 bKey;
    u8 pad0005[0x3];
    CtxPair aPairs[4];
    int nPageIndex;
    u8 pad0028[0x484];
} Ctx;

extern Ctx *g_ctx;

extern int classify(int *pOut, int nMode);
extern void call3(int a, int b, int c);
extern void call4(int a, int b, int c, int d);
extern void call5(int a, int b, int c, int d, int e);
extern void call8(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int call0(void);
extern u16 *lookup(void *p, u16 n);
extern int slot(int n);
extern int tagof(int n);

void repro2(int nFrom, int nTo) {
    int nColumn;
    int nTag;
    Ctx *s = g_ctx;
    int nClass = classify(&nColumn, s->bMode);

    call3(s->bMode, nTo, 0);

    switch (nClass) {
    case 0:
        switch (nFrom) {
        case 0: {
            int i;

            i = 0;
            s->aPairs[s->nPageIndex].y = 0x24000;
            {
                Ctx *c2 = g_ctx;

                if (c2->bKind != 0 && c2->nPageIndex < 3) {
                    c2->aPairs[c2->nPageIndex].y += 0x8000;
                }
            }
            break;
        }
        case 1: {
            int nValue = call0();

            call4(4, 0, 0, 0);
            call3(nFrom + 2, nValue, 0);
            break;
        }
        }
        break;

    case 1: {
        int nOffset = nColumn * 6;

        call5(nFrom + nOffset, nFrom, 1, slot(nFrom + nOffset), 0);
        nClass = nColumn * 6 + nTo;
        call5(nClass, nTo, 1, slot(nClass), 1);
        s->bIndex = (u8)nClass;
        break;
    }

    case 2: {
        int nOld = nFrom + nColumn * 6;
        int nNew = nTo + nColumn * 6;
        u16 *pEntry;
        int bFlag;
        int nSlot;

        pEntry = lookup(s, (u16)nOld);
        bFlag = 0;
        if (tagof(*pEntry) != 0 && slot(*pEntry) != 0) {
            bFlag = 1;
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = slot(*pEntry);
        }
        call8(s, nSlot, nFrom, nOld, 1, bFlag, 0, 0);

        pEntry = lookup(s, (u16)nNew);
        bFlag = 0;
        if (tagof(*pEntry) != 0 && slot(*pEntry) != 0) {
            bFlag = 1;
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = slot(*pEntry);
        }
        call8(s, nSlot, nTo, nNew, 1, bFlag, 1, 0);
        s->bListIndex = (u8)(nColumn * 6 + nTo);
        break;
    }

    case 3: {
        int nOld = nFrom + nColumn * 6;
        u16 *pEntry;
        int nSlot;

        nClass = nTo + nColumn * 6;

        pEntry = lookup(s, (u16)nOld);
        nTag = 0;
        if (pEntry != 0) {
            nTag = tagof(pEntry[1] & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = slot(*pEntry);
        }
        call8(s, nSlot, nFrom, nOld, 1, 1, 0, nTag);

        pEntry = lookup(s, (u16)nClass);
        if (pEntry != 0) {
            nTag = tagof(pEntry[1] & 0xff);
        }
        if (pEntry == 0) {
            nSlot = -1;
        } else {
            nSlot = slot(*pEntry);
        }
        call8(s, nSlot, nTo, nClass, 1, 1, 1, nTag);
        s->bKey = (u8)nClass;
        break;
    }
    }

    s->bKind = (u8)nTo;
    call3(s->bMode, nTo, 0);
}
