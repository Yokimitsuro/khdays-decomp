/* func_ov025_020afef4 -- Ov025_ReportDetail_SetupEntries: bind the sprites of the report detail
 * view of page B (Ov025_GetPageB 02084b14) for its mode (+0x54).  The entry context (+0x48)
 * takes the layout template data_ov025_020b4968 with the layout member of
 * data_ov025_020b4960[mode] as its resource (Ov025_PackSlotTag 02084d18; 020883f8), the
 * resource of data_ov025_020b495c[mode] by index (02084d94; 02088410), loads the ten entries of
 * the entries member (Ov025_LoadBlockProcessAndFree 0208832c) and releases the list slots in
 * mode 2 (02088a7c).  Entries 0..5, 7, 6, 8 and 9 are kept at +0x5c..+0x80 (FindEntryById
 * 0208843c); the second slot pair of the three digits, the count and the slash is released
 * (Ov025_ReleaseTwoSlots 020888b0) and cell 0 of the tag tracker (+0x44) invoked
 * (Ov025_TagTracker_InvokeCallback 02089544). */
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
typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

extern u32   func_ov025_02084d18(int nMember);                      /* Ov025_PackSlotTag */
extern void *func_ov025_02084d94(int nIndex);                       /* Ov025_ResourceByIndex */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov025_SetLayout */
extern void  func_ov025_02088410(int nCtx, void *pResource);        /* Ov025_SetEntryResource */
extern void  func_ov025_0208832c(int nCtx, u32 nTag, int nCount);   /* Ov025_LoadBlockProcessAndFree */
extern void  func_ov025_02088a7c(int nCtx, int nMode);              /* Ov025_ReleaseAllListSlots */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);           /* Ov025_ReleaseTwoSlots */
extern void *func_ov025_020894b0(int nTracker, int nTag);           /* Ov025_TagTracker_FindCell */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov025_TagTracker_InvokeCallback */
extern Ov008LayoutTemplate data_ov025_020b4968;
extern const Ov025ReportDetailSet  data_ov025_020b4960[];
extern const Ov025ReportDetailText data_ov025_020b495c[];

void func_ov025_020afef4(void)
{
    Ov008LayoutTemplate layout;
    Ov025ReportDetailPage *pPage;

    layout = data_ov025_020b4968;
    pPage = func_ov025_02084b14();
    layout.words[0] = func_ov025_02084d18(data_ov025_020b4960[pPage->bMissionMode].nLayoutMember);
    func_ov025_020883f8(pPage->nCtx, &layout);
    func_ov025_02088410(pPage->nCtx, func_ov025_02084d94(data_ov025_020b495c[pPage->bMissionMode].nResource));
    func_ov025_0208832c(pPage->nCtx, func_ov025_02084d18(data_ov025_020b4960[pPage->bMissionMode].nEntriesMember), 0xa);
    func_ov025_02088a7c(pPage->nCtx, 2);
    pPage->pTitleEntry = func_ov025_0208843c(pPage->nCtx, 0);
    pPage->apDigit[0] = func_ov025_0208843c(pPage->nCtx, 1);
    pPage->apDigit[1] = func_ov025_0208843c(pPage->nCtx, 2);
    pPage->apDigit[2] = func_ov025_0208843c(pPage->nCtx, 3);
    pPage->pMarkEntry = func_ov025_0208843c(pPage->nCtx, 4);
    pPage->pCountEntry = func_ov025_0208843c(pPage->nCtx, 5);
    pPage->pSlashEntry = func_ov025_0208843c(pPage->nCtx, 7);
    pPage->pTotalEntry = func_ov025_0208843c(pPage->nCtx, 6);
    pPage->pEntry8 = func_ov025_0208843c(pPage->nCtx, 8);
    pPage->pEntry9 = func_ov025_0208843c(pPage->nCtx, 9);
    func_ov025_020888b0(pPage->nCtx, pPage->apDigit[0]);
    func_ov025_020888b0(pPage->nCtx, pPage->apDigit[1]);
    func_ov025_020888b0(pPage->nCtx, pPage->apDigit[2]);
    func_ov025_020888b0(pPage->nCtx, pPage->pCountEntry);
    func_ov025_020888b0(pPage->nCtx, pPage->pSlashEntry);
    func_ov025_02089544(pPage->nTracker, func_ov025_020894b0(pPage->nTracker, 0));
}
