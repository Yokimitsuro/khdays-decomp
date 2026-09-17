/* func_ov025_0209ebb4 -- Ov025_Reports_SetupEntries: bind the reports / enemy profiles page's
 * sprites for its set (data_ov025_020b4228 row picked by the mode word +0x258).  The page's tag
 * tracker (+0xb4) and the shared tracker (Ov008_GetCtxBlock954c 02084a64) load the set's
 * tracker member (Ov008_PackSlotTag 02084d18; 020891dc); cell 2 is invoked (02089544) and
 * cells 3 / 4 kept (+0x260 / +0x264; 020894b0) with cell 6 as the selection marker (+0x268) for
 * the reports and cell 3 for the enemies.  The entry context (+0xb8) takes the layout template
 * data_ov025_020b4240 with the set's layout member (020883f8), binds the resource named by
 * data_ov025_020b4218 (02084d94 / 02088410), loads the set's 0x5c entries (0208832c) and
 * releases the list slots in mode 2 (02088a7c); entries 3, 4 and 1 become the up arrow, the
 * down arrow and the scroll knob (+0x26c / +0x270 / +0x274) and the knob is shown (0208884c).
 * The ten rows (+0xd0, seven entries each: ids 0x33 / 0x3d / 0x47 / 0x51 / 0x5b / 0x6f / 0x65
 * plus the row) release the second pair of four of their cells (020888b0), and entries
 * 0x65..0x6e resolve through func_ov025_020a0e1c (02088420). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008LayoutTemplate {
    u32  words[4];
} Ov008LayoutTemplate;

typedef struct Ov025ReportsRow {
    void *pTitle;             /* 0x00: entry 0x33 + row */
    void *pMark1;             /* 0x04: entry 0x3d + row */
    void *pMark2;             /* 0x08: entry 0x47 + row */
    void *pMark3;             /* 0x0c: entry 0x51 + row */
    void *pMark4;             /* 0x10: entry 0x5b + row */
    void *pBadge;             /* 0x14: entry 0x6f + row */
    void *pNumber;            /* 0x18: entry 0x65 + row */
} Ov025ReportsRow;            /* 0x1c */

typedef struct Ov025ReportsPage {
    u8   pad_000[0x6c];
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    int  nTracker;            /* 0x0b4: the tag tracker */
    int  nCtx;                /* 0x0b8: the entry context */
    u8   pad_0bc[0xc8 - 0xbc];
    int  nState;              /* 0x0c8 */
    u8   pad_0cc[0xd0 - 0xcc];
    Ov025ReportsRow aRow[10]; /* 0x0d0 */
    void *pEntries;           /* 0x1e8: the per-report records (0x40 bytes each) */
    u8   pad_1ec[0x230 - 0x1ec];
    void *pTable;             /* 0x230: the report table file */
    void *pSpriteFile;        /* 0x234: the report sprite file */
    u8   pad_238[0x248 - 0x238];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    int  nField25c;           /* 0x25c */
    void *pCell3;             /* 0x260 */
    void *pCell4;             /* 0x264 */
    void *pSelectCell;        /* 0x268 */
    void *pUpArrow;           /* 0x26c */
    void *pDownArrow;         /* 0x270 */
    void *pKnob;              /* 0x274 */
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

typedef struct Ov025ReportsSet {
    u8   nBgMember;           /* 0x00: the background archive member */
    u8   nLayoutMember;       /* 0x01 */
    u8   nTrackerMember;      /* 0x02 */
    u8   nEntriesMember;      /* 0x03 */
    u8   nField04;            /* 0x04 */
} Ov025ReportsSet;

extern Ov025ReportsPage *func_ov025_02084afc(void);                 /* Ov008_GetPageA */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern void  func_ov025_020891dc(int nTracker, u32 nTag);           /* Ov008_TagTracker_Load */
extern int   func_ov025_02084a64(void);                             /* Ov008_GetCtxBlock954c */
extern void *func_ov025_020894b0(int nTracker, int nTag);           /* Ov008_TagTracker_FindCell */
extern void  func_ov025_02089544(int nTracker, void *pCell);        /* Ov008_TagTracker_InvokeCallback */
extern void  func_ov025_020883f8(int nCtx, Ov008LayoutTemplate *pLayout); /* Ov008_SetLayout */
extern void *func_ov025_02084d94(int nIndex);                       /* resource by index */
extern void  func_ov025_02088410(int nCtx, void *pResource);        /* ForwardTo_02031d90 */
extern void  func_ov025_0208832c(int nCtx, u32 nTag, int nCount);   /* Ov008_LoadBlockProcessAndFree */
extern void  func_ov025_02088a7c(int nCtx, int nMode);              /* Ov008_ForEachListNode */
extern void *func_ov025_0208843c(int nCtx, int nId);                /* FindEntryById */
extern void  func_ov025_0208884c(int nCtx, void *pEntry, int bVisible); /* SetEntrySlotsVisible */
extern void  func_ov025_020888b0(int nCtx, void *pEntry);           /* Ov008_ReleaseTwoSlots */
extern void  func_ov025_02088420(int nCtx, int nId, void *pCallback); /* Ov008_ResolveEntryStoreWord */
extern void  func_ov025_020a0e1c(void);
extern Ov008LayoutTemplate data_ov025_020b4240;
extern const Ov025ReportsSet data_ov025_020b4228[];                 /* per mode */
extern const u8 data_ov025_020b4218[];                              /* the resource index per mode */

void func_ov025_0209ebb4(void)
{
    Ov008LayoutTemplate layout;
    Ov025ReportsPage *pPage;
    int nShared;
    int i;
    Ov025ReportsRow *pRow;

    layout = data_ov025_020b4240;
    pPage = func_ov025_02084afc();
    func_ov025_020891dc(pPage->nTracker, func_ov025_02084d18(data_ov025_020b4228[pPage->bMissionMode].nTrackerMember));
    nShared = func_ov025_02084a64();
    func_ov025_020891dc(nShared, func_ov025_02084d18(data_ov025_020b4228[pPage->bMissionMode].nTrackerMember));
    func_ov025_02089544(pPage->nTracker, func_ov025_020894b0(pPage->nTracker, 2));
    pPage->pCell3 = func_ov025_020894b0(pPage->nTracker, 3);
    pPage->pCell4 = func_ov025_020894b0(pPage->nTracker, 4);
    if (pPage->bMissionMode == 0) {
        pPage->pSelectCell = func_ov025_020894b0(pPage->nTracker, 6);
    } else {
        pPage->pSelectCell = pPage->pCell3;
    }
    layout.words[0] = func_ov025_02084d18(data_ov025_020b4228[pPage->bMissionMode].nLayoutMember);
    func_ov025_020883f8(pPage->nCtx, &layout);
    func_ov025_02088410(pPage->nCtx, func_ov025_02084d94(data_ov025_020b4218[pPage->bMissionMode]));
    func_ov025_0208832c(pPage->nCtx, func_ov025_02084d18(data_ov025_020b4228[pPage->bMissionMode].nEntriesMember), 0x5c);
    func_ov025_02088a7c(pPage->nCtx, 2);
    pPage->pUpArrow = func_ov025_0208843c(pPage->nCtx, 3);
    pPage->pDownArrow = func_ov025_0208843c(pPage->nCtx, 4);
    pPage->pKnob = func_ov025_0208843c(pPage->nCtx, 1);
    func_ov025_0208884c(pPage->nCtx, func_ov025_0208843c(pPage->nCtx, 1), 1);
    i = 0;
    pRow = pPage->aRow;
    for (; i < 10; i++) {
        pRow->pTitle = func_ov025_0208843c(pPage->nCtx, i + 0x33);
        pRow->pMark1 = func_ov025_0208843c(pPage->nCtx, i + 0x3d);
        pRow->pMark2 = func_ov025_0208843c(pPage->nCtx, i + 0x47);
        pRow->pMark3 = func_ov025_0208843c(pPage->nCtx, i + 0x51);
        pRow->pMark4 = func_ov025_0208843c(pPage->nCtx, i + 0x5b);
        pRow->pBadge = func_ov025_0208843c(pPage->nCtx, i + 0x6f);
        pRow->pNumber = func_ov025_0208843c(pPage->nCtx, i + 0x65);
        func_ov025_020888b0(pPage->nCtx, pRow->pMark1);
        func_ov025_020888b0(pPage->nCtx, pRow->pMark2);
        func_ov025_020888b0(pPage->nCtx, pRow->pMark3);
        func_ov025_020888b0(pPage->nCtx, pRow->pBadge);
        pRow++;
    }
    func_ov025_02088420(pPage->nCtx, 0x65, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x66, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x67, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x68, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x69, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x6a, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x6b, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x6c, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x6d, func_ov025_020a0e1c);
    func_ov025_02088420(pPage->nCtx, 0x6e, func_ov025_020a0e1c);
}
