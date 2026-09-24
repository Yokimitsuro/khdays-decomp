/* Ov011_BuildTitleLayout0 -- switch case 0 of the title menu tick: swap both panes' graphics to
 * the next archive entries, upload the palette to both engines, show BG0-BG2+OBJ with window 0,
 * start a brightness fade-in on both screens and register the VBlank scroll task.
 *
 * The overwritten `nMode = 0` store is removed by the optimiser but still spends mwcc's per-block
 * IR budget; without it the pane base `pTop + 0x10000` is kept across the fade calls and every
 * register in the display block shifts. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Pane {
    void *pBuffer;
    u8    pad_00004[0x1091a - 4];
    u16   wScrollPhase;
    u8    pad_1091c[0x10931 - 0x1091c];
    u8    nPhase;
    u8    nFlag;
    u8    pad_10933[0x10938 - 0x10933];
    u32   nSpeed;
    u32   nAccum;
} Ov011Pane;

typedef struct Ov011Scene {
    int       nA;
    int       nMode;
    u8        pad_00008[4];
    u32       nArchiveBase;
    u8        pad_00010[4];
    Ov011Pane aPane[2];
    u8        pad_21294[0x23294 - 0x21294];
    u8        aPalette[0x800];
    u8        pad_23a94[0x23abd - 0x23a94];
    u8        nPaneFlags;
    u8        pad_23abe[0x23ac8 - 0x23abe];
    u16       nAnimIndex;
    u16       nAnimCount;
    const void *pAnimTable;
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern const u8 data_ov011_0205e130[];
extern u8 data_ov011_0205e930[];

extern void  NNSi_FndFreeFromDefaultHeap(void *p);
extern void *func_0201ef9c(u32 nHandle, int nHeap);
extern void  GFXi_EnqueueCommand(int nType, int nOffset, const void *pSrc, u32 nSize);
extern void  G2x_SetBlendBrightness_(volatile void *pReg, int nPlane, int nBrightness);
extern void  func_02000f48(int nSlot, u8 *pName, void (*pFn)(void));
extern void  func_ov011_0205d218(void);

#define reg_GX_DISPCNT      (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT  (*(volatile u32 *)0x04001000)

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline void GX_SetVisibleWnd(int window)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | (window << 13);
}

static inline void GXS_SetVisibleWnd(int window)
{
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0xe000) | (window << 13);
}

void func_ov011_0205be38(void)
{
    Ov011Scene *pScene = data_ov011_0205e960.pScene;
    Ov011Pane *pTop = &pScene->aPane[0];
    Ov011Pane *pBottom = &pScene->aPane[1];

    pScene->nMode = 0;
    pScene->nMode = 1;
    data_ov011_0205e960.pScene->pAnimTable = data_ov011_0205e130;
    data_ov011_0205e960.pScene->nAnimCount = 0x75;
    data_ov011_0205e960.pScene->nAnimIndex = 0;
    NNSi_FndFreeFromDefaultHeap(pTop->pBuffer);
    NNSi_FndFreeFromDefaultHeap(pBottom->pBuffer);
    pTop->pBuffer = func_0201ef9c(
        ((data_ov011_0205e960.pScene->nArchiveBase + 0x8000 & 0xfffffc) << 7)
            | 0x80000002, 0xe);
    pBottom->pBuffer = func_0201ef9c(
        ((data_ov011_0205e960.pScene->nArchiveBase + 0x8000 & 0xfffffc) << 7)
            | 0x80000003, 0xe);
    GFXi_EnqueueCommand(0xa, 0, data_ov011_0205e960.pScene->aPalette, 0x800);
    GFXi_EnqueueCommand(0x1a, 0, data_ov011_0205e960.pScene->aPalette, 0x800);
    GX_SetVisiblePlane(0x17);
    GXS_SetVisiblePlane(0x17);
    GX_SetVisibleWnd(1);
    GXS_SetVisibleWnd(1);
    *(volatile u16 *)0x04000050 = 0;
    *(volatile u16 *)0x04001050 = 0;
    pTop->nFlag = 0;
    pBottom->nFlag = 0;
    pTop->nPhase = 5;
    pBottom->nPhase = 5;
    G2x_SetBlendBrightness_((volatile void *)0x04000050, 4, -0x10);
    G2x_SetBlendBrightness_((volatile void *)0x04001050, 4, -0x10);
    func_02000f48(1, data_ov011_0205e930, func_ov011_0205d218);
    pTop->wScrollPhase = 0;
    pBottom->wScrollPhase = 0;
    pTop->nSpeed = 0x5dc0;
    pBottom->nSpeed = 0;
    pTop->nAccum = 0;
    pBottom->nAccum = 0;
    data_ov011_0205e960.pScene->nPaneFlags =
        (u8)((data_ov011_0205e960.pScene->nPaneFlags & ~1) | 1);
}
