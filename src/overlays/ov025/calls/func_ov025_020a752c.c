/* func_ov025_020a752c -- Ov008_FlushMissionListGraphics: publish the mission
 * list's graphics for the frame.  In list mode 1 (+0x504) the sub engine's
 * BG2 scroll registers get the fine scroll (nScroll % 32 - nTop, in bits
 * 16..24) and the scroll / selection are latched into their previous fields.
 * A dirty BG3 map (+0x4c) reloads slot 0x1b's screen; in mode 1 a dirty BG2
 * map (+0x48) reloads slot 0x1a's screen and uploads the six rows' name,
 * info and extra tile surfaces (pixels at pCurrent+0x20, size / offset from
 * the surface) after flushing them from the cache.  Always returns 1.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define ROW_COUNT   6
#define ROW_HEIGHT  32
#define LIST_MODE_ROWS 1

typedef struct TileSurfaceObj {
    u8    pad_00[0x20];
    void *pPixels;            /* 0x20 */
} TileSurfaceObj;

typedef struct TileSurface {
    u8   pad_00[0xc];
    int  nTotalBytes;         /* 0x0c */
    int  nRowBytes;           /* 0x10: upload offset */
    u8   pad_14[4];
    TileSurfaceObj *pCurrent; /* 0x18 */
    u8   pad_1c[0x3c - 0x1c];
} TileSurface;

typedef struct Ov008MissionList {
    int nSelected;            /* 0x000 */
    int nPrevSelected;        /* 0x004 */
    u8  pad_008[4];
    int nScroll;              /* 0x00c */
    int nPrevScroll;          /* 0x010 */
    int nTop;                 /* 0x014 */
    u8  pad_018[0x48 - 0x18];
    int bDirty;               /* 0x048: BG2 map + row surfaces */
    int bMapDirty;            /* 0x04c: BG3 map */
    u8  pad_050[0x84 - 0x50];
    TileSurface aRowNameSurface[ROW_COUNT];  /* 0x084 */
    TileSurface aRowInfoSurface[ROW_COUNT];  /* 0x1ec */
    TileSurface aRowExtraSurface[ROW_COUNT]; /* 0x354 */
    u8  pad_4bc[0x504 - 0x4bc];
    int nMode;                /* 0x504 */
} Ov008MissionList;

extern Ov008MissionList *func_ov025_02084b14(void);                     /* Ov008_GetPageB */
extern void *func_ov025_02084aa4(int nSlot);                            /* Ov008_ResetEntry: slot data */
extern void  GXS_LoadBG3Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG2Scr(const void *pSrc, u32 nOffset, u32 nSize);
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GXS_LoadBG2Char(const void *pSrc, u32 nOffset, u32 nSize);

int func_ov025_020a752c(void)
{
    Ov008MissionList *pList;
    volatile int *pScroll = (volatile int *)0x04001018;
    int i;
    int nValue;
    TileSurface *pName;
    TileSurface *pInfo;
    TileSurface *pExtra;

    pList = func_ov025_02084b14();
    if (pList->nMode == LIST_MODE_ROWS) {
        nValue = 0x01ff0000 & ((pList->nScroll % ROW_HEIGHT - pList->nTop) << 16);
        pScroll[0] = nValue;
        pScroll[1] = nValue;
        pList->nPrevScroll = pList->nScroll;
        pList->nPrevSelected = pList->nSelected;
    }
    if (pList->bMapDirty != 0) {
        GXS_LoadBG3Scr(func_ov025_02084aa4(0x1b), 0, 0x800);
        pList->bMapDirty = 0;
    }
    if (pList->nMode == LIST_MODE_ROWS && pList->bDirty != 0) {
        GXS_LoadBG2Scr(func_ov025_02084aa4(0x1a), 0, 0x800);
        pName = pList->aRowNameSurface;
        pInfo = pList->aRowInfoSurface;
        pExtra = pList->aRowExtraSurface;
        for (i = 0; i < ROW_COUNT; i++) {
            DC_FlushRange(pName->pCurrent->pPixels, pName->nTotalBytes);
            GXS_LoadBG2Char(pName->pCurrent->pPixels, pName->nRowBytes, pName->nTotalBytes);
            DC_FlushRange(pInfo->pCurrent->pPixels, pInfo->nTotalBytes);
            GXS_LoadBG2Char(pInfo->pCurrent->pPixels, pInfo->nRowBytes, pInfo->nTotalBytes);
            DC_FlushRange(pExtra->pCurrent->pPixels, pExtra->nTotalBytes);
            GXS_LoadBG2Char(pExtra->pCurrent->pPixels, pExtra->nRowBytes, pExtra->nTotalBytes);
            pName++;
            pInfo++;
            pExtra++;
        }
        pList->bDirty = 0;
    }
    return 1;
}
