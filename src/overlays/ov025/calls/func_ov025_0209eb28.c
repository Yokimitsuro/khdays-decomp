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

typedef struct Ov025ReportsPage {
    u8   pad_000[0x6c];
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    u8   pad_0b4[0xc8 - 0xb4];
    int  nState;              /* 0x0c8 */
    u8   pad_0cc[0x248 - 0xcc];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    u8   pad_25c[0x278 - 0x25c];
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

typedef struct Ov025ReportsSet {
    u8   nBgMember;           /* 0x00: the background archive member */
    u8   aField01[4];         /* 0x01 */
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
