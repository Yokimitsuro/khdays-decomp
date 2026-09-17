/* func_ov025_0209da74 -- Ov025_Tutorial_SetupSurfaces: prepare the tutorial page's graphics.  The
 * title strip loader (+0x6c of the page) takes "UI/cm/str/ttl_&.s.z" and the topic loader
 * (+0x78) "UI/tutorial/root_&.s.z" (0208985c); the 32 x 24 text surface at +0x84 is built from
 * the template data_ov025_020b41b4 with the shared tile pixel buffer (02084c84) and VRAM slot 9
 * (02084aa4) and uploaded as 4bpp tiles (0202ff8c). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct TileSurfaceCfg {
    u32  nUnk00;
    u32  nUnk04;
    u32  nWidthTiles;
    u32  nHeightTiles;
    u32  nRowTiles;
    u32  nPaletteIndex;
    u32  nVramTarget;
    u32  nUnk1c;
    void *pPixels;
    u32  nUnk24;
} TileSurfaceCfg;

typedef struct Ov025TutorialList {
    void *pHeader;            /* 0x00 */
    void *pFooter;            /* 0x04 */
    void *apRow[15];          /* 0x08 */
    int  nVisible;            /* 0x44: rows placed by Ov025_Tutorial_PlaceRows */
    int  nTotal;              /* 0x48 */
    int  nScroll;             /* 0x4c: the row requested by Ov025_Tutorial_ScrollTo */
    int  nRows;               /* 0x50: 4..18 */
    int  nRowBase;            /* 0x54: the row offset the entries are placed from */
    int  nField58;            /* 0x58 */
} Ov025TutorialList;          /* 0x5c */

typedef struct Ov025TutorialTopic {
    const u16 *pName;         /* 0x00 */
    int  nId;                 /* 0x04 */
} Ov025TutorialTopic;

typedef struct Ov025TutorialPage {
    s16  nTop;                /* 0x000: the first visible topic */
    s16  nCursor;             /* 0x002 */
    s16  nCount;              /* 0x004 */
    s16  nField06;            /* 0x006 */
    int  nField08;            /* 0x008 */
    u32  nPhase : 2;          /* 0x00c bits 0-1: 1 = cursor moved, redraw */
    int  nScrollDir : 2;      /* 0x00c bits 2-3: a page scroll in flight */
    Ov025TutorialList list;   /* 0x010 */
    u8   textTitle[0xc];      /* 0x06c: "UI/cm/str/ttl_&.s.z" */
    u8   textTopics[0xc];     /* 0x078: "UI/tutorial/root_&.s.z" */
    u8   surface[0x3c];       /* 0x084: the text surface */
    int  nField0c0;           /* 0x0c0 */
    int  nTracker;            /* 0x0c4: the tag tracker (markers) */
    int  nCtx;                /* 0x0c8: the entry context (rows, arrows, knob) */
    Ov025TutorialTopic aTopic[58]; /* 0x0cc: the unlocked topics in display order */
    void *pMarkerCell;        /* 0x29c */
    void *pMarkerLitCell;     /* 0x2a0 */
    void *pUpArrow;           /* 0x2a4 */
    void *pDownArrow;         /* 0x2a8 */
    void *pKnob;              /* 0x2ac */
} Ov025TutorialPage;          /* 0x2b0: a view of page A (Ov008_GetPageA) */

extern Ov025TutorialPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern void  func_ov025_0208985c(void *pLoader, const char *pszPath); /* Ov008_Set_5c4c */
extern void *func_ov025_02084c84(void);                             /* Ov008_GetCtxBlock968c */
extern int   func_ov025_02084aa4(int nSlot);                        /* Ov008_ResetEntry: slot handle */
extern void  func_0202ff8c(void *pSurface, TileSurfaceCfg *pCfg);   /* TileSurface_InitAndUpload4bpp */
extern TileSurfaceCfg data_ov025_020b41b4;
extern char  data_ov025_020b51b0[];                                 /* "UI/cm/str/ttl_&.s.z" */
extern char  data_ov025_020b51c4[];                                 /* "UI/tutorial/root_&.s.z" */

void func_ov025_0209da74(void)
{
    TileSurfaceCfg cfg;
    Ov025TutorialPage *pPage;

    cfg = data_ov025_020b41b4;
    pPage = func_ov025_02084afc();
    func_ov025_0208985c(pPage->textTitle, data_ov025_020b51b0);
    func_ov025_0208985c(pPage->textTopics, data_ov025_020b51c4);
    cfg.pPixels = func_ov025_02084c84();
    cfg.nVramTarget = func_ov025_02084aa4(9);
    func_0202ff8c(pPage->surface, &cfg);
}
