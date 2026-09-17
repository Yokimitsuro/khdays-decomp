/* func_ov025_020afdd4 -- Ov025_ReportDetail_LoadBackground: load the sub-screen background of
 * the report detail view of page B (Ov025_GetPageB 02084b14) for its mode (+0x54: reports or
 * enemy profiles).  The archive member of data_ov025_020b4960[mode] (Ov025_PackSlotTag
 * 02084d18; 0201ef9c, heap 0xe) gives the palette / character / screen cell
 * (Res_LoadSpriteSet 02024c94): the palette goes to the sub BG palette RAM (GXS_LoadBGPltt);
 * the BG3 characters come from the localised sub-file of data_ov025_020b495c[mode] (02084d50)
 * when there is one (unpacked with 020119d4, flushed and uploaded), else from the cell.  The
 * files are freed, the 0x40 bytes at +0x2800 of the sub BG2 characters cleared and the sub BG2
 * screen filled with tile 0xa0. */
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
typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;
typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

extern u32   func_ov025_02084d18(int nMember);                      /* Ov025_PackSlotTag */
extern u32   func_ov025_02084d50(int nSubFile);                     /* Ov025_PackLocalisedTag */
extern void *func_0201ef9c(u32 nTag, int nHeap);                    /* Res_Open */
extern void  func_02024c94(Ov008ResourceCell *pCell, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  func_020119d4(void *pFile, Ov008CharacterBlock **ppBlock); /* NNS_G2dGetUnpackedCharacterData */
extern void  GXS_LoadBGPltt(const void *pSrc, u32 nOffset, u32 nSize);
extern void  GXS_LoadBG3Char(const void *pSrc, u32 nOffset, u32 nSize);
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern u8   *G2S_GetBG2CharPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void  MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);
extern const Ov025ReportDetailSet  data_ov025_020b4960[];
extern const Ov025ReportDetailText data_ov025_020b495c[];

void func_ov025_020afdd4(void)
{
    Ov025ReportDetailPage *pPage;
    void *pFile;
    void *pCharFile;
    u32 nCharTag;
    Ov008ResourceCell cell;
    Ov008CharacterBlock *pBlock;

    pPage = func_ov025_02084b14();
    pFile = func_0201ef9c(func_ov025_02084d18(data_ov025_020b4960[pPage->bMissionMode].nBgMember), 0xe);
    func_02024c94(&cell, pFile, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    nCharTag = func_ov025_02084d50(data_ov025_020b495c[pPage->bMissionMode].nCharSubFile);
    if (nCharTag != 0) {
        pCharFile = func_0201ef9c(nCharTag, 0xe);
        func_020119d4(pCharFile, &pBlock);
        DC_FlushRange(pBlock->data, pBlock->size);
        GXS_LoadBG3Char(pBlock->data, 0, pBlock->size);
        if (pCharFile != 0) {
            NNSi_FndFreeFromDefaultHeap(pCharFile);
        }
    } else {
        GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    }
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
    MIi_CpuClearFast(0, G2S_GetBG2CharPtr() + 0x2800, 0x40);
    MIi_CpuClearFast(0x00a000a0, G2S_GetBG2ScrPtr(), 0x800);
}
