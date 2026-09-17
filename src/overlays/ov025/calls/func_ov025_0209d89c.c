/* func_ov025_0209d89c -- Ov025_Tutorial_LoadBackground: load the tutorial page's background.
 * Archive member 0x43 (Ov008_PackSlotTag 02084d18; 0201ef9c, heap 0xe) gives the palette /
 * character / screen cell (Res_LoadSpriteSet 02024c94): the palette goes to the BG palette RAM
 * (GX_LoadBGPltt); the characters come from the localised sub-file 1 when there is one
 * (02084d50: its CHAR block 020119d4 is flushed from the cache and sent to BG3), else from the
 * member's own character block (GX_LoadBG3Char); the files are freed again. */
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

extern void *func_ov025_02084afc(void);                             /* Ov008_GetPageA */
extern u32   func_ov025_02084d18(int nMember);                      /* Ov008_PackSlotTag */
extern u32   func_ov025_02084d50(int nSubFile);                     /* Ov008_PackLocalisedTag */
extern void *func_0201ef9c(u32 nTag, int nHeap);                    /* Res_Open */
extern void  func_02024c94(Ov008ResourceCell *pCell, void *pFile, int nScreen, int nChar, int nPalette); /* Res_LoadSpriteSet */
extern void  func_020119d4(void *pFile, Ov008CharacterBlock **ppBlock); /* GetResourceSubBlock_CHAR2 */
extern void  DC_FlushRange(const void *pAddress, u32 nSize);
extern void  GX_LoadBGPltt(const void *pSource, u32 nOffset, u32 nSize);
extern void  GX_LoadBG3Char(const void *pSource, u32 nOffset, u32 nSize);
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov025_0209d89c(void)
{
    void *pFile;
    void *pCharFile;
    u32  nTag;
    Ov008CharacterBlock *pChar;
    Ov008ResourceCell cell;

    func_ov025_02084afc();
    pFile = func_0201ef9c(func_ov025_02084d18(0x43), 0xe);
    func_02024c94(&cell, pFile, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    nTag = func_ov025_02084d50(1);
    if (nTag != 0) {
        pCharFile = func_0201ef9c(nTag, 0xe);
        func_020119d4(pCharFile, &pChar);
        DC_FlushRange(pChar->data, pChar->size);
        GX_LoadBG3Char(pChar->data, 0, pChar->size);
        if (pCharFile != 0) {
            NNSi_FndFreeFromDefaultHeap(pCharFile);
        }
    } else {
        GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    }
    if (pFile != 0) {
        NNSi_FndFreeFromDefaultHeap(pFile);
    }
}
