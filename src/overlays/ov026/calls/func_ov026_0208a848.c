/* func_ov026_0208a848 -- Ov008_ShopCreate: build the shop scene context on
 * the current root heap (0xc608 bytes, zeroed, kept in data_ov026_02091368).
 * The ready word (+0xc5f0) is set, the "story past 0x46" word (+0xc5f4)
 * taken from GameState field 0 (9 bits), and the shop kind (+0xc, u16)
 * chosen from global short 0204c1ec (0/1 -> 1, 2 -> 3, 3 -> 0, 4 -> 4,
 * 5 -> 2).  The display, panels, surfaces, list cells, preview model and
 * column cells are set up, the +0x8 block freed, the card transfer unbound,
 * resource pair 0x181 requested and its sound played, the parameter table
 * created and the preview reset.  In an active session the session word
 * (+0xc5f8) is set and widget 10 of the shop entry manager (+0x2ab0) shown
 * and released; widget 0x3f is released.  The input header (+0xc0fc) is
 * initialised with limits 10 x 3 (+0xc5dc), the first word cleared and the
 * record at +0xc5fc set up with the handlers 0208b838 / 0208b870.  Returns
 * the tick function 02087cac.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define CONTEXT_SIZE   0xc608
#define STORY_BITS     9
#define STORY_THRESHOLD 0x47
#define RESOURCE_PAIR  0x181
#define WIDGET_SESSION 10
#define WIDGET_CURSOR  0x3f

typedef struct Ov008HandlerPair {
    void (*pFirst)(void);
    void (*pSecond)(void);
} Ov008HandlerPair;

typedef struct Ov008HeaderLimits {
    u16 nColumns;
    u16 nRows;
} Ov008HeaderLimits;

typedef struct Ov008PanelContext {
    int   nFirst;                     /* 0x0000 */
    u8    pad_0004[4];
    void *pBlock;                     /* 0x0008 */
    u16   nShopKind;                  /* 0x000c */
    u8    pad_000e[0x2ab0 - 0xe];
    u8    entries[0xc0fc - 0x2ab0];   /* 0x2ab0: shop entry manager */
    u8    inputHeader[0xc5dc - 0xc0fc]; /* 0xc0fc */
    Ov008HeaderLimits limits;         /* 0xc5dc */
    u8    pad_c5e0[0xc5f0 - 0xc5e0];
    int   bReady;                     /* 0xc5f0 */
    int   bStoryPast;                 /* 0xc5f4 */
    int   bSession;                   /* 0xc5f8 */
    u8    record[0xc];                /* 0xc5fc */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern u32   func_020235d0(int nField, int nBits);                        /* GameState_GetField */
extern int   func_02024e5c(void);                                         /* LoadGlobalShort_0204c1ec */
extern void  func_ov026_02084de0(void);                                   /* Ov008_SetupShopDisplay */
extern void  func_ov026_0208532c(void);
extern void  func_ov026_020855c4(void);
extern void  func_ov026_02085884(void);                                   /* Ov008_InitShopSurfaces */
extern void  func_ov026_02087134(void);                                   /* Ov008_CreateListCells */
extern void  func_ov026_02084fdc(void);                                   /* Ov008_ResetPreviewModel */
extern void  func_ov026_02085fc8(void);                                   /* Ov008_InitColumnCells */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  func_02033500(int nArg);                                     /* FSi_BindCardTransfer */
extern void  func_0203355c(int nPair);                                    /* Res_RequestIdPair */
extern void  func_02033b24(int nPair, int nArg);                          /* PlaySoundChecked */
extern void  func_ov026_0208d22c(void);                                   /* Ov008_CreateParamTable */
extern void  func_02024d68(void);
extern void  func_ov026_02085a7c(void);
extern int   func_02030640(void);                                         /* Session_Exists */
extern int   func_02030670(void);                                         /* Session_IsActive */
extern void *func_ov026_0208427c(void *pManager, int nId);                /* FindEntryById */
extern void  func_ov026_020843e8(void *pManager, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov026_0208444c(void *pManager, void *pEntry);           /* Ov008_ReleaseTwoSlots */
extern int   func_02036298(void *pHeader, Ov008HeaderLimits *pLimits);    /* Header_InitWithLimits */
extern void  func_ov026_02090e74(void *pRecord, Ov008HandlerPair *pHandlers); /* Ov008_InitWithDefaultHandlers */
extern void  func_ov026_0208e6e8(void);
extern void  func_ov026_0208e720(void);
extern void  func_ov026_0208ab5c(void);                                   /* shop tick */

void *func_ov026_0208a848(void)
{
    Ov008PanelContext *ctx;
    void *pEntries;
    Ov008HandlerPair handlers;

    ctx = NNSi_FndGetCurrentRootHeap();
    data_ov026_02091368 = ctx;
    pEntries = ctx->entries;
    MI_CpuFill8(ctx, 0, CONTEXT_SIZE);
    ctx->bReady = 1;
    ctx->bStoryPast = func_020235d0(0, STORY_BITS) >= STORY_THRESHOLD;
    switch (func_02024e5c()) {
    case 1:
        ctx->nShopKind = 1;
        break;
    case 2:
        ctx->nShopKind = 3;
        break;
    case 3:
        ctx->nShopKind = 0;
        break;
    case 4:
        ctx->nShopKind = 4;
        break;
    case 5:
        ctx->nShopKind = 2;
        break;
    default:
        ctx->nShopKind = 1;
        break;
    }
    func_ov026_02084de0();
    func_ov026_0208532c();
    func_ov026_020855c4();
    func_ov026_02085884();
    func_ov026_02087134();
    func_ov026_02084fdc();
    func_ov026_02085fc8();
    if (ctx->pBlock != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pBlock);
        ctx->pBlock = 0;
    }
    func_02033500(0);
    func_0203355c(RESOURCE_PAIR);
    func_02033b24(RESOURCE_PAIR, 0);
    func_ov026_0208d22c();
    func_02024d68();
    func_ov026_02085a7c();
    if (func_02030640() != 0 && func_02030670() != 0) {
        ctx->bSession = 1;
        func_ov026_020843e8(pEntries, func_ov026_0208427c(pEntries, WIDGET_SESSION), 1);
        func_ov026_0208444c(pEntries, func_ov026_0208427c(pEntries, WIDGET_SESSION));
    }
    func_ov026_0208444c(pEntries, func_ov026_0208427c(pEntries, WIDGET_CURSOR));
    ctx->limits.nColumns = 10;
    ctx->limits.nRows = 3;
    func_02036298(ctx->inputHeader, &ctx->limits);
    ctx->nFirst = 0;
    handlers.pFirst = func_ov026_0208e6e8;
    handlers.pSecond = func_ov026_0208e720;
    func_ov026_02090e74(ctx->record, &handlers);
    return func_ov026_0208ab5c;
}
