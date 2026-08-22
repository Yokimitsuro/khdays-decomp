/*
 * Ov002_OpenPanelScreen - build the mission panel screen and hand back the
 * step function that runs it.
 *
 * The context is allocated from the current root heap, wiped, and given the
 * two message containers it reads its text from; the second one is only opened
 * outside the one language variant that does not need it. The four slots the
 * caller passed are copied in whole, and the ones that carry both an id and an
 * icon contribute their three halfwords to the slot class parameters and bump
 * the loaded count.
 *
 * Which resources are used is decided by whether the caller asked for the
 * 256-colour BG2 case: it picks the archive key, whether the boot flag can
 * still suppress one class, and which of the two containers the character data
 * comes from. Outside that case the panel also builds its own classes - the
 * flip gate unless the global is 0x2a, the icon and character classes, the
 * help class from the fields at +0x174, and then the slots, labels and item
 * text on top.
 *
 * A 0xc00 character block is copied out of the loaded sprite set so it can
 * outlive the archive. Both display controls end up with their window bits set
 * to 0xf00, the main one only while the check at 0x02075f84 says so. The two
 * containers and the scratch archive are released on the way out.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *pScreen;
    void *pChar;
    void *pPalette;
} SpriteResSet;

typedef struct {
    int nId;
    int nIcon;
    u16 wUnk08;
    u16 wUnk0a;
    u16 wUnk0c;
    u16 wUnk0e;
} Ov002PanelSlot;

typedef struct {
    int nUnk00;
    int nUnk04;
    char aRest[0x54];
} Ov002PanelParams;                     /* 0x5c */

typedef struct {
    u16 aFields[12];                    /* +0x00 three arrays, one per slot */
    int nUnk18;                         /* +0x18 */
    void *pChar;                        /* +0x1c */
} Ov002SlotClassParams;                 /* 0x20 */

typedef struct {
    u32 nKey;                           /* +0x00 */
    int nUnk04;                         /* +0x04 */
    void *pChar;                        /* +0x08 */
} Ov002CharClassParams;                 /* 0x0c */

typedef struct {
    int nUnk00;                         /* +0x00 */
    u16 wUnk04;                         /* +0x04 */
    int nUnk08;                         /* +0x08 */
    int bUnk0c;                         /* +0x0c */
    char aUnk10[8];                     /* +0x10 */
} Ov002HelpClassParams;                 /* 0x18 */

typedef struct {
    u32 nKey;                           /* +0x00 */
    u8 bUnk04;                          /* +0x04 */
    int bUnk08;                         /* +0x08 */
} Ov002BgClassParams;                   /* 0x0c */

typedef struct {
    int nFlipGate;                      /* +0x000 */
    int hBgClass;                       /* +0x004 */
    int hSlotClass;                     /* +0x008 */
    int hCharClass;                     /* +0x00c */
    int hHelpClass;                     /* +0x010 */
    int hClass0014;                     /* +0x014 */
    int hClass0018;                     /* +0x018 */
    int hClass001c;                     /* +0x01c */
    int hClass0020;                     /* +0x020 */
    char aBind0024[0xc];                /* +0x024 */
    char aBind0030[0xc];                /* +0x030 */
    char pad003c[4];
    int bOwnsScreen;                    /* +0x040 */
    char pad0044[0x14];
    int bMissionClear;                  /* +0x058 */
    int bBg2Is256Colour;                /* +0x05c */
    char pad0060[0x98];
    char aOffsetTween[0x1c];            /* +0x0f8 */
    char aScrollTween[0x1c];            /* +0x114 */
    Ov002PanelSlot aSlots[4];           /* +0x130 */
    char pad0170[4];
    int nUnk0174;                       /* +0x174 */
    int nUnk0178;                       /* +0x178 */
    u16 wUnk017c;                       /* +0x17c */
    char pad017e[6];
    char aUnk0184[8];                   /* +0x184 */
    char pad018c[0xc];
    int nHelpPage;                      /* +0x198 */
    int nArchiveGroup;                  /* +0x19c */
    int nArchiveGroupAlt;               /* +0x1a0 */
    char pad01a4[4];
    int nUnk01a8;                       /* +0x1a8 */
    char pad01ac[1];
    u8 nUnk01ad;                        /* +0x1ad */
    char pad01ae[1];
    u8 nLoadedCount;                    /* +0x1af */
    char pad01b0[0xc];
    int nHelpMode;                      /* +0x1bc */
    char pad01c0[4];
    int aLevels[2];                     /* +0x1c4 */
    int *pLevel;                        /* +0x1cc */
    char pad01d0[4];
    void *pCharCopy;                    /* +0x1d4 */
    char pad01d8[0x44];
    void *hAlloc021c;                   /* +0x21c */
    char pad0220[0x20];
    void *hStepNode;                    /* +0x240 */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;
extern Ov002SlotClassParams data_ov002_0207dbc8;
extern Ov002CharClassParams data_ov002_0207db9c;
extern char data_ov002_0207e880[];
extern char data_ov002_0207e894[];
extern char data_ov002_0207e8b4[];
extern char data_ov002_0207e91c[];
extern char data_ov002_0207e92c[];
extern char data_ov002_0207e940[];
extern char data_ov002_0207e958[];
extern char data_ov002_0207e970[];
extern char data_ov002_0207e9cc[];
extern char data_ov002_0207e9e0[];
extern char data_ov002_0207ea00[];
extern char data_ov002_0207eb2c[];
extern char data_ov002_0207ebb0[];
extern char data_ov002_0207eca0[];
extern u8 data_0204c240;

extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int nSize, int nAlign);
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *func_0201ef9c(unsigned int nKey, int nHeap);
extern void func_020119d4(void *hRes, void **ppOut);
extern void func_0202ff58(void *pField, const void *pTable);
extern int func_02020a9c(void);
extern int func_02023930(const void *pClass, const void *pParams);
extern void *func_02024c94(SpriteResSet *pSet, void *pArc, int a, int b, int c);
extern int func_02024e5c(void);
extern void *func_02024ee8(const void *pName, int nHeap);
extern void func_02024fd4(void *pContainer);
extern void func_02035f84(void *pTween);
extern void *func_ov002_020538c0(void *pStep);
extern void func_ov002_020537bc(int a, int b, int nDuration);
extern void func_ov002_02054d80(void);
extern void func_ov002_02055358(void *pArc, SpriteResSet *pRes);
extern void func_ov002_02055384(int bBg2Is256Colour);
extern void func_ov002_020553ec(int a);
extern int func_ov002_020550d0(Ov002PanelSlot *pSlots, SpriteResSet *pRes);
extern void func_ov002_020557f4(int nMode);
extern void func_ov002_02055984(void);
extern void func_ov002_02055b24(void);
extern void func_ov002_02057434(int a, int b);
extern void func_ov002_0205693c(void);
extern void func_ov002_02061bac(int a);
extern void WM_EndKeySharing_0x02063574(void);
extern int func_ov002_0206e770(int a);
extern int func_ov002_02075f84(void);

int func_ov002_0205633c(Ov002PanelParams *pParams)
{
    Ov002PanelContext *ctx;
    void *pArc;
    void *pExtra;
    int i;
    u16 *pOut;
    Ov002PanelContext *pWalk;
    volatile u32 *pOfs;
    int nClassArg;
    int bLangVariant;
    Ov002SlotClassParams sSlots;
    Ov002CharClassParams sChar;
    SpriteResSet sRes;
    Ov002BgClassParams sBg;
    Ov002HelpClassParams sHelp;

    sSlots = data_ov002_0207dbc8;
    sChar = data_ov002_0207db9c;
    pExtra = 0;
    ctx = (Ov002PanelContext *)NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f614 = ctx;
    MI_CpuFill8(ctx, 0, 0x2c4);
    ctx->nArchiveGroup = (int)func_02024ee8(data_ov002_0207e91c, 0xe);
    bLangVariant = func_02024e5c() == 1;
    if (bLangVariant == 0) {
        ctx->nArchiveGroupAlt = (int)func_02024ee8(data_ov002_0207e92c, 0xe);
    }
    ctx->nUnk01ad = 4;
    ctx->bOwnsScreen = 1;
    ctx->nUnk01a8 = 1;
    ctx->hAlloc021c = NNS_FndAllocFromDefaultExpHeapEx(0x200, 4);
    ctx->nHelpMode = -1;
    ctx->nHelpPage = 9;
    ctx->bMissionClear = func_ov002_0206e770(0);
    ctx->bBg2Is256Colour = pParams->nUnk04 == -1;
    ctx->pLevel = ctx->aLevels;
    func_ov002_02055384(ctx->bBg2Is256Colour);
    func_ov002_02057434(0, -0x10);
    func_ov002_020557f4(0);
    MI_CpuCopy8(pParams, ctx->aSlots, 0x5c);

    i = 0;
    pOut = sSlots.aFields;
    pWalk = ctx;
    do {
        pOut[0] = 0;
        pOut[4] = 0;
        pOut[8] = 0;
        if (pWalk->aSlots[0].nId != -1 && pWalk->aSlots[0].nIcon != -1) {
            pOut[0] = pWalk->aSlots[0].wUnk08;
            pOut[4] = pWalk->aSlots[0].wUnk0a;
            pOut[8] = pWalk->aSlots[0].wUnk0c;
            ctx->nLoadedCount++;
        }
        i++;
        pOut++;
        pWalk = (Ov002PanelContext *)((char *)pWalk + 0x10);
    } while (i < 4);

    func_0202ff58(ctx->aBind0024, data_ov002_0207e940);
    func_0202ff58(ctx->aBind0030, data_ov002_0207e958);
    func_02035f84(ctx->aOffsetTween);
    func_02035f84(ctx->aScrollTween);

    if (ctx->bBg2Is256Colour != 0) {
        sBg.bUnk04 = 0;
        nClassArg = -1;
        sBg.nKey = 0x80000003 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7;
        sBg.bUnk08 = (data_0204c240 & 4) == 0;
    } else {
        sBg.bUnk04 = 0;
        nClassArg = 0;
        sBg.nKey = 0x80000000 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7;
        sBg.bUnk08 = 1;
    }
    ctx->hClass0020 = func_02023930(data_ov002_0207e8b4, 0);
    ctx->hBgClass = func_02023930(data_ov002_0207e894, &sBg);
    ctx->hClass0014 = func_02023930(data_ov002_0207e880, 0);
    ctx->hClass0018 = func_02023930(data_ov002_0207eb2c, (const void *)nClassArg);
    func_ov002_020553ec(1);
    pOfs = (volatile u32 *)0x04000014;
    pOfs[0] = 0;
    pOfs[2] = 0;

    if (ctx->bBg2Is256Colour != 0) {
        pArc = func_0201ef9c(
            0x80000002 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7, 0xe);
        bLangVariant = func_02024e5c() == 1;
        if (bLangVariant != 0) {
            func_02024c94(&sRes, pArc, 0, 0, 0);
        } else {
            func_02024c94(&sRes, pArc, 0, -1, 0);
            pExtra = func_0201ef9c((u32)data_ov002_0207e970, 0xe);
            func_020119d4(pExtra, &sRes.pChar);
        }
    } else {
        pArc = func_0201ef9c(
            0x80000004 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7, 0xe);
        bLangVariant = func_02024e5c() == 1;
        if (bLangVariant != 0) {
            func_02024c94(&sRes, pArc, 0, 0, 0);
        } else {
            func_02024c94(&sRes, pArc, 0, -1, 0);
            pExtra = func_0201ef9c(
                0x80000000 | ((ctx->nArchiveGroupAlt + 0x8000) & 0xfffffc) << 7,
                0xe);
            func_020119d4(pExtra, &sRes.pChar);
        }
    }

    ctx->pCharCopy = NNS_FndAllocFromDefaultExpHeapEx(0xc00, 4);
    MI_CpuCopy8(*(void **)((char *)sRes.pChar + 0x14), ctx->pCharCopy, 0xc00);

    if (ctx->bBg2Is256Colour == 0) {
        if (func_02020a9c() != 0x2a) {
            ctx->nFlipGate = func_02023930(data_ov002_0207eca0, 0);
        }
        sSlots.pChar = ctx->pCharCopy;
        ctx->hSlotClass = func_02023930(data_ov002_0207e9cc, &sSlots);
        sChar.pChar = *(void **)((char *)sRes.pChar + 0x14);
        bLangVariant = func_02024e5c() == 1;
        if (bLangVariant != 0) {
            sChar.nKey =
                0x80000005 | ((ctx->nArchiveGroup + 0x8000) & 0xfffffc) << 7;
        } else {
            sChar.nKey =
                0x80000001 | ((ctx->nArchiveGroupAlt + 0x8000) & 0xfffffc) << 7;
        }
        ctx->hCharClass = func_02023930(data_ov002_0207e9e0, &sChar);
        if (func_02020a9c() != 0x2a) {
            ctx->hClass001c = func_02023930(data_ov002_0207ebb0, 0);
            func_ov002_02061bac(1);
        }
        sHelp.wUnk04 = ctx->wUnk017c;
        sHelp.nUnk00 = ctx->nUnk0178;
        sHelp.nUnk08 = ctx->nUnk0174;
        sHelp.bUnk0c = ctx->aSlots[0].nIcon == 1;
        MI_CpuCopy8(ctx->aUnk0184, sHelp.aUnk10, 8);
        ctx->hHelpClass = func_02023930(data_ov002_0207ea00, &sHelp);
        if (func_ov002_020550d0(ctx->aSlots, &sRes) > 1) {
            WM_EndKeySharing_0x02063574();
        }
        func_ov002_02055984();
        func_ov002_02055b24();
    }

    func_ov002_02055358(pArc, &sRes);
    func_ov002_020537bc(0, 0x10, 300);
    ctx->hStepNode = func_ov002_020538c0((void *)func_ov002_02054d80);
    if (func_ov002_02075f84() == 0) {
        *(volatile u32 *)0x04000000 =
            (*(volatile u32 *)0x04000000 & 0xffffe0ff) | 0xf00;
    }
    *(volatile u32 *)0x04001000 =
        (*(volatile u32 *)0x04001000 & 0xffffe0ff) | 0xf00;
    if (ctx->nArchiveGroupAlt != 0) {
        func_02024fd4((void *)ctx->nArchiveGroupAlt);
        ctx->nArchiveGroupAlt = 0;
    }
    func_02024fd4((void *)ctx->nArchiveGroup);
    ctx->nArchiveGroup = 0;
    if (pExtra != 0) {
        NNSi_FndFreeFromDefaultHeap(pExtra);
    }
    return (int)func_ov002_0205693c;
}
