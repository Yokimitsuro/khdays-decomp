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

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

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
extern char gOv002UiBtlMainPath[];
extern char gOv002UiBtlMainPath_2[];
extern char gOv002TextFontEu08Path[];
extern char gOv002TextFontEu10Path[];
extern char gOv002UiBtlSu200Path[];
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
extern void *Archive_LoadFile(unsigned int nKey, int nHeap);
extern void GetResourceSubBlock_CHAR2(void *hRes, void **ppOut);
extern int InstantiateClass(const void *pClass, const void *pParams);
extern void *Msg_OpenContainerAndReadHeader(const void *pName, int nHeap);
extern void Tween_Clear(void *pTween);
extern void *Ov002_CreateStepNode(void *pStep);
extern void Ov002_StartBlendFade(int a, int b, int nDuration);
extern void Ov002_RunScrollHooks(void);
extern void Ov002_UploadBgResourceAndFree(void *pArc, SpriteResSet *pRes);
extern void Ov002_SetupBackgroundLayers(int bBg2Is256Colour);
extern void Ov002_SetPanelBgLayers(int a);
/* Defined with two more parameters, nPalDst and i, which it writes before reading: nothing is
 * passed there (Ov002_LoadPanelSlots's header says why they are parameters). */
extern int Ov002_LoadPanelSlots(Ov002PanelSlot *pSlots, SpriteResSet *pRes);
extern void Ov002_SetPanelMode(int nMode);
extern void Ov002_BuildPanelLabels(void);
extern void Ov002_BuildTextItem(void);
extern void Ov002_SetBrightness(int a, int b);
extern void Ov002_StepPanelScreen(void);
extern void Ov002_SuspendOrRestorePanel(int a);
extern void func_ov002_02063574(void);
extern int Ov002_IsMissionClearFinished(int a);
extern int Ov002_HasObjectState(void);

int Ov002_OpenPanelScreen(Ov002PanelParams *pParams)
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
    ctx->nArchiveGroup = (int)Msg_OpenContainerAndReadHeader(gOv002UiBtlMainPath, 0xe);
    bLangVariant = GetLanguage() == 1;
    if (bLangVariant == 0) {
        ctx->nArchiveGroupAlt = (int)Msg_OpenContainerAndReadHeader(gOv002UiBtlMainPath_2, 0xe);
    }
    ctx->nUnk01ad = 4;
    ctx->bOwnsScreen = 1;
    ctx->nUnk01a8 = 1;
    ctx->hAlloc021c = NNS_FndAllocFromDefaultExpHeapEx(0x200, 4);
    ctx->nHelpMode = -1;
    ctx->nHelpPage = 9;
    ctx->bMissionClear = Ov002_IsMissionClearFinished(0);
    ctx->bBg2Is256Colour = pParams->nUnk04 == -1;
    ctx->pLevel = ctx->aLevels;
    Ov002_SetupBackgroundLayers(ctx->bBg2Is256Colour);
    Ov002_SetBrightness(0, -0x10);
    Ov002_SetPanelMode(0);
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

    Resource_BindByName(ctx->aBind0024, gOv002TextFontEu08Path);
    Resource_BindByName(ctx->aBind0030, gOv002TextFontEu10Path);
    Tween_Clear(ctx->aOffsetTween);
    Tween_Clear(ctx->aScrollTween);

    if (ctx->bBg2Is256Colour != 0) {
        sBg.bUnk04 = 0;
        nClassArg = -1;
        sBg.nKey = ARCHIVE_HANDLE(ctx->nArchiveGroup, 3);
        sBg.bUnk08 = (data_0204c240 & 4) == 0;
    } else {
        sBg.bUnk04 = 0;
        nClassArg = 0;
        sBg.nKey = ARCHIVE_HANDLE(ctx->nArchiveGroup, 0);
        sBg.bUnk08 = 1;
    }
    ctx->hClass0020 = InstantiateClass(data_ov002_0207e8b4, 0);
    ctx->hBgClass = InstantiateClass(data_ov002_0207e894, &sBg);
    ctx->hClass0014 = InstantiateClass(data_ov002_0207e880, 0);
    ctx->hClass0018 = InstantiateClass(data_ov002_0207eb2c, (const void *)nClassArg);
    Ov002_SetPanelBgLayers(1);
    pOfs = (volatile u32 *)0x04000014;
    pOfs[0] = 0;
    pOfs[2] = 0;

    if (ctx->bBg2Is256Colour != 0) {
        pArc = Archive_LoadFile(
            ARCHIVE_HANDLE(ctx->nArchiveGroup, 2), 0xe);
        bLangVariant = GetLanguage() == 1;
        if (bLangVariant != 0) {
            Res_LoadSpriteSet(&sRes, pArc, 0, 0, 0);
        } else {
            Res_LoadSpriteSet(&sRes, pArc, 0, -1, 0);
            pExtra = Archive_LoadFile((u32)gOv002UiBtlSu200Path, 0xe);
            GetResourceSubBlock_CHAR2(pExtra, &sRes.pChar);
        }
    } else {
        pArc = Archive_LoadFile(
            ARCHIVE_HANDLE(ctx->nArchiveGroup, 4), 0xe);
        bLangVariant = GetLanguage() == 1;
        if (bLangVariant != 0) {
            Res_LoadSpriteSet(&sRes, pArc, 0, 0, 0);
        } else {
            Res_LoadSpriteSet(&sRes, pArc, 0, -1, 0);
            pExtra = Archive_LoadFile(
                ARCHIVE_HANDLE(ctx->nArchiveGroupAlt, 0),
                0xe);
            GetResourceSubBlock_CHAR2(pExtra, &sRes.pChar);
        }
    }

    ctx->pCharCopy = NNS_FndAllocFromDefaultExpHeapEx(0xc00, 4);
    MI_CpuCopy8(*(void **)((char *)sRes.pChar + 0x14), ctx->pCharCopy, 0xc00);

    if (ctx->bBg2Is256Colour == 0) {
        if (LoadGlobalU16At0() != 0x2a) {
            ctx->nFlipGate = InstantiateClass(data_ov002_0207eca0, 0);
        }
        sSlots.pChar = ctx->pCharCopy;
        ctx->hSlotClass = InstantiateClass(data_ov002_0207e9cc, &sSlots);
        sChar.pChar = *(void **)((char *)sRes.pChar + 0x14);
        bLangVariant = GetLanguage() == 1;
        if (bLangVariant != 0) {
            sChar.nKey =
                ARCHIVE_HANDLE(ctx->nArchiveGroup, 5);
        } else {
            sChar.nKey =
                ARCHIVE_HANDLE(ctx->nArchiveGroupAlt, 1);
        }
        ctx->hCharClass = InstantiateClass(data_ov002_0207e9e0, &sChar);
        if (LoadGlobalU16At0() != 0x2a) {
            ctx->hClass001c = InstantiateClass(data_ov002_0207ebb0, 0);
            Ov002_SuspendOrRestorePanel(1);
        }
        sHelp.wUnk04 = ctx->wUnk017c;
        sHelp.nUnk00 = ctx->nUnk0178;
        sHelp.nUnk08 = ctx->nUnk0174;
        sHelp.bUnk0c = ctx->aSlots[0].nIcon == 1;
        MI_CpuCopy8(ctx->aUnk0184, sHelp.aUnk10, 8);
        ctx->hHelpClass = InstantiateClass(data_ov002_0207ea00, &sHelp);
        if (Ov002_LoadPanelSlots(ctx->aSlots, &sRes) > 1) {
            func_ov002_02063574();
        }
        Ov002_BuildPanelLabels();
        Ov002_BuildTextItem();
    }

    Ov002_UploadBgResourceAndFree(pArc, &sRes);
    Ov002_StartBlendFade(0, 0x10, 300);
    ctx->hStepNode = Ov002_CreateStepNode((void *)Ov002_RunScrollHooks);
    if (Ov002_HasObjectState() == 0) {
        *(volatile u32 *)0x04000000 =
            (*(volatile u32 *)0x04000000 & 0xffffe0ff) | 0xf00;
    }
    *(volatile u32 *)0x04001000 =
        (*(volatile u32 *)0x04001000 & 0xffffe0ff) | 0xf00;
    if (ctx->nArchiveGroupAlt != 0) {
        ZeroHalfThenFree((void *)ctx->nArchiveGroupAlt);
        ctx->nArchiveGroupAlt = 0;
    }
    ZeroHalfThenFree((void *)ctx->nArchiveGroup);
    ctx->nArchiveGroup = 0;
    if (pExtra != 0) {
        NNSi_FndFreeFromDefaultHeap(pExtra);
    }
    return (int)Ov002_StepPanelScreen;
}
