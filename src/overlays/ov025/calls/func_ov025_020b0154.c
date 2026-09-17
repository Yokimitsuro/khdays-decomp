/* func_ov025_020b0154 -- Ov025_ReportDetail_Teardown: leave the report detail view of page B
 * (Ov025_GetPageB 02084b14).  VRAM slot 0x1b is freed (Ov025_ClearSlotBit 0208499c), the
 * 0x20 x 0x18 tile grids of slots 0x18..0x1b cleared (020849d8), the four sub-screen BG screens
 * blanked (G2S_GetBGnScrPtr / MIi_CpuClearFast), the text surface (+4) released (0202ffbc), the
 * tag tracker (+0x44) cleared (020895b8) and the entry context (+0x48) unwound (020883a0 /
 * 020883d4). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov025ReportsEntry {
    u16  nId : 9;             /* 0x00 bits 0-8 */
    u16  nFlag9 : 1;          /* 0x00 bit 9 */
    u16  nPending : 6;        /* 0x00 bits 10-15: enemies still to defeat */
    u8   pad_02[8];
    u8   bUnlocked;           /* 0x0a */
    u8   nField0b;            /* 0x0b */
    struct Ov025ReportsEntry *pRead; /* 0x0c: the read variant of the record, if any */
    const u16 *pName;         /* 0x10: the title */
    u8   pad_14[4];
    const u16 *pText;         /* 0x18 */
    u8   pad_1c[0xc];
    const u16 *apLine[6];     /* 0x28: one line per chapter */
} Ov025ReportsEntry;          /* 0x40 */

typedef struct Ov025ReportDetailPage {
    int  nField00;            /* 0x00 */
    u8   surface[0x3c];       /* 0x04: the text surface (TileSurface) */
    int  nField40;            /* 0x40 */
    int  nTracker;            /* 0x44: the tag tracker */
    int  nCtx;                /* 0x48: the entry context */
    int  nField4c;            /* 0x4c */
    Ov025ReportsEntry *pEntry; /* 0x50: the report shown */
    int  bMissionMode;        /* 0x54: enemy profiles rather than reports */
    int  nChapter;            /* 0x58: GameState field 3, +1 under 6 */
    void *pTitleEntry;        /* 0x5c: entry 0 */
    void *apDigit[3];         /* 0x60: entries 1..3 */
    void *pMarkEntry;         /* 0x6c: entry 4 */
    void *pCountEntry;        /* 0x70: entry 5 */
    void *pSlashEntry;        /* 0x74: entry 7 */
    void *pTotalEntry;        /* 0x78: entry 6 */
    void *pEntry8;            /* 0x7c: entry 8 */
    void *pEntry9;            /* 0x80: entry 9 */
} Ov025ReportDetailPage;      /* 0x84 */

typedef struct Ov025ReportDetailSet {
    u8   nBgMember;           /* 0x00: the background archive member */
    u8   nLayoutMember;       /* 0x01 */
    u8   nEntriesMember;      /* 0x02 */
} Ov025ReportDetailSet;

typedef struct Ov025ReportDetailText {
    u8   nCharSubFile;        /* 0x00: the localised BG3 characters (0 = the background's own) */
    u8   nResource;           /* 0x01: the resource by index */
} Ov025ReportDetailText;

extern Ov025ReportDetailPage *func_ov025_02084b14(void);            /* Ov025_GetPageB */
extern void  func_ov025_0208499c(int nSlot);                        /* Ov025_ClearSlotBit */
extern void  func_ov025_020849d8(int nSlot, int nX, int nY, int nW, int nH); /* Ov025_ClearGridRows */
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern void  func_0202ffbc(void *pSurface);                         /* TileSurface_Release */
extern void  func_ov025_020895b8(int nTracker);                     /* Ov025_TagTracker_Clear */
extern void  func_ov025_020883a0(int nCtx);                         /* Ov025_ReleaseEntryList */
extern void  func_ov025_020883d4(int nCtx);                         /* Ov025_ReleaseEntryLayout */

void func_ov025_020b0154(void)
{
    Ov025ReportDetailPage *pPage;

    pPage = func_ov025_02084b14();
    func_ov025_0208499c(0x1b);
    func_ov025_020849d8(0x18, 0, 0, 0x20, 0x18);
    func_ov025_020849d8(0x19, 0, 0, 0x20, 0x18);
    func_ov025_020849d8(0x1a, 0, 0, 0x20, 0x18);
    func_ov025_020849d8(0x1b, 0, 0, 0x20, 0x18);
    MIi_CpuClearFast(0, G2S_GetBG0ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);
    func_0202ffbc(pPage->surface);
    func_ov025_020895b8(pPage->nTracker);
    func_ov025_020883a0(pPage->nCtx);
    func_ov025_020883d4(pPage->nCtx);
}
