/* func_ov025_0209eb28 -- Ov025_Reports_LoadPalette: load the report page's background palette
 * and BG3 tiles.  The archive member for the page's set (byte 0 of the 5-byte row of
 * data_ov025_020b4228 picked by the mode word at +0x258; Ov008_PackSlotTag 02084d18) is opened
 * (0201ef9c, heap 0xe), its palette / character / screen cell bound (Res_LoadSpriteSet
 * 02024c94), the palette sent to the BG palette RAM (GX_LoadBGPltt) and the characters to BG3
 * (GX_LoadBG3Char); the file is freed again (NNSi_FndFreeFromDefaultHeap). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;

typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;

typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;

typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

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
extern void *func_0201ef9c(u32 nTag, int nHeap);                    /* Res_Open */
extern void  func_02024c94(Ov008ResourceCell *pCell, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  GX_LoadBGPltt(const void *pSource, u32 nOffset, u32 nSize);
extern void  GX_LoadBG3Char(const void *pSource, u32 nOffset, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern const Ov025ReportsSet data_ov025_020b4228[];                 /* per mode */

void func_ov025_0209eb28(void)
{
    void *pFile;
    Ov008ResourceCell cell;

    pFile = func_0201ef9c(func_ov025_02084d18(data_ov025_020b4228[func_ov025_02084afc()->bMissionMode].nBgMember), 0xe);
    func_02024c94(&cell, pFile, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
}
