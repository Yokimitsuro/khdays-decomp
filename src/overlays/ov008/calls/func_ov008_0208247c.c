/* func_ov008_0208247c -- Ov008_LoadShopResources: load the shop panel's
 * resources.  The two message containers (ui/shop/res.p2 at +0x4 and
 * ui/shop/res_i18n.p2 at +0x8) are opened, both tag trackers (+0x5c, +0x10)
 * configured from 0208fec8, and the container's sprite set (cell handle of
 * container A) unpacked twice: once (screen 1, palette 1) for the main
 * screen's BG palette and BG2 characters -- replaced by the page's (+0xc)
 * character block from container B (table 0208fef2) when the page has one --
 * and once (0, 0) for the sub screen's BG palette and BG1 characters.  Both
 * trackers then load ui/shop/shop.BGUI.z, the primary one is enabled, the
 * 0x600-byte row text buffer (+0x2aa8, 0xc0 entries) allocated and cleared,
 * and tags 1000 / 0x3e9 / 0x3f2 of the secondary and 0 / 1 of the primary
 * tracker invoked.  Codegen: pFile declared before ctx (ctx takes r5 after
 * the config copy's source pointer).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;

#define HEAP_FILE   0xe
#define CELL_MASK   0x00fffffc
#define SLOT_MASK   0x1ff
#define CELL_HANDLE(src, cell) (((((src) + 0x8000) & CELL_MASK) << 7) | 0x80000000 | (cell))
#define ROW_TEXT_CAPACITY 0xc0
#define ROW_TEXT_SIZE     0x600
#define ROW_TEXT_ALLOC    0x610  /* header + text + 4 spare */

typedef struct Ov008PaletteBlock   { u8 pad_00[0x08]; u32 nSize; void *pData; } Ov008PaletteBlock;
typedef struct Ov008CharacterBlock { u8 pad_00[0x10]; u32 nSize; void *pData; } Ov008CharacterBlock;

typedef struct SpriteResSet {
    void *pScreen;
    Ov008CharacterBlock *pChar;
    Ov008PaletteBlock *pPalette;
} SpriteResSet;

typedef struct Ov008SurfaceConfig {
    u32 words[5];
} Ov008SurfaceConfig;

typedef struct Ov008RowTextBuffer {
    u16 nCapacity;            /* 0x00 */
    u16 pad_02;
    u16 nCount;               /* 0x04 */
    u16 nCursor;              /* 0x06 */
    int nSize;                /* 0x08 */
    u8  aText[ROW_TEXT_SIZE]; /* 0x0c */
} Ov008RowTextBuffer;

typedef struct Ov008PanelContext {
    u8  pad_0000[4];
    int pContainerA;          /* 0x0004: ui/shop/res.p2 */
    int pContainerB;          /* 0x0008: ui/shop/res_i18n.p2 */
    s16 nPage;                /* 0x000c */
    u8  pad_000e[2];
    u8  tracker[0x5c - 0x10]; /* 0x0010: primary tag tracker */
    u8  trackerB[0x2aa8 - 0x5c]; /* 0x005c: secondary tag tracker */
    Ov008RowTextBuffer *pRowText; /* 0x2aa8 */
} Ov008PanelContext;

extern const Ov008SurfaceConfig data_ov008_0208fec8;
extern Ov008PanelContext *data_ov008_02090fac;
extern char data_ov008_02090de4[];                                /* "ui/shop/res.p2" */
extern char data_ov008_02090df4[];                                /* "ui/shop/res_i18n.p2" */
extern s8   data_ov008_0208fef2[];                                /* per page: character cell of container B */
extern char data_ov008_02090e08[];                                /* "ui/shop/shop.BGUI.z" */
extern int   func_02024ee8(const char *pPath, int nHeap);         /* Msg_OpenContainerAndReadHeader */
extern void  func_ov008_0205546c(void *pTracker, const Ov008SurfaceConfig *pConfig);
extern void *func_0201ef9c(u32 nHandle, int nHeap);               /* Archive_LoadFile */
extern void  func_02024c94(SpriteResSet *pSet, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  GX_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  func_020119d4(void *pFile, Ov008CharacterBlock **ppBlock); /* GetResourceSubBlock_CHAR2 */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GX_LoadBG2Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG1Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  func_ov008_02055534(void *pTracker, const char *pPath); /* Ov008_LoadLayoutResource */
extern void  func_ov008_02055c08(void *pTracker, int bEnable);
extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern void  INITi_CpuClear32_0x01ff86fc(int nValue, void *pDst, u32 nSize);
extern void *func_ov008_02055808(void *pTracker, int nTag);        /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(void *pTracker, void *pCell);     /* Ov008_TagTracker_InvokeCallback */

void func_ov008_0208247c(void)
{
    Ov008SurfaceConfig config;
    SpriteResSet setMain;
    SpriteResSet setSub;
    Ov008CharacterBlock *pChar;
    void *pFile;
    Ov008PanelContext *ctx;
    void *pBlock;
    Ov008RowTextBuffer *pRowText;
    int nSlot;

    config = data_ov008_0208fec8;
    ctx = data_ov008_02090fac;
    ctx->pContainerA = func_02024ee8(data_ov008_02090de4, HEAP_FILE);
    ctx->pContainerB = func_02024ee8(data_ov008_02090df4, HEAP_FILE);
    func_ov008_0205546c(ctx->trackerB, &config);
    func_ov008_0205546c(ctx->tracker, &config);
    pFile = func_0201ef9c(CELL_HANDLE(ctx->pContainerA, 0), HEAP_FILE);
    func_02024c94(&setMain, pFile, -1, 1, 1);
    GX_LoadBGPltt(setMain.pPalette->pData, 0, setMain.pPalette->nSize);
    nSlot = data_ov008_0208fef2[ctx->nPage * 4];
    if (nSlot >= 0) {
        pBlock = func_0201ef9c(CELL_HANDLE(ctx->pContainerB, nSlot & SLOT_MASK), HEAP_FILE);
        func_020119d4(pBlock, &pChar);
        DC_FlushRange(pChar->pData, pChar->nSize);
        GX_LoadBG2Char(pChar->pData, 0, pChar->nSize);
        if (pBlock != 0) {
            NNSi_FndFreeFromDefaultHeap(pBlock);
        }
    } else {
        GX_LoadBG2Char(setMain.pChar->pData, 0, setMain.pChar->nSize);
    }
    func_02024c94(&setSub, pFile, -1, 0, 0);
    GXS_LoadBGPltt(setSub.pPalette->pData, 0, setSub.pPalette->nSize);
    GXS_LoadBG1Char(setSub.pChar->pData, 0, setSub.pChar->nSize);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
    func_ov008_02055534(ctx->trackerB, data_ov008_02090e08);
    func_ov008_02055534(ctx->tracker, data_ov008_02090e08);
    func_ov008_02055c08(ctx->tracker, 1);
    pRowText = NNSi_FndAllocFromDefaultExpHeap(ROW_TEXT_ALLOC);
    pRowText->nCapacity = ROW_TEXT_CAPACITY;
    pRowText->nCount = 0;
    pRowText->nCursor = 0;
    pRowText->nSize = ROW_TEXT_SIZE;
    INITi_CpuClear32_0x01ff86fc(0, pRowText->aText, ROW_TEXT_SIZE);
    ctx->pRowText = pRowText;
    func_ov008_0205589c(ctx->trackerB, func_ov008_02055808(ctx->trackerB, 1000));
    func_ov008_0205589c(ctx->trackerB, func_ov008_02055808(ctx->trackerB, 0x3e9));
    func_ov008_0205589c(ctx->trackerB, func_ov008_02055808(ctx->trackerB, 0x3f2));
    func_ov008_0205589c(ctx->tracker, func_ov008_02055808(ctx->tracker, 0));
    func_ov008_0205589c(ctx->tracker, func_ov008_02055808(ctx->tracker, 1));
}
