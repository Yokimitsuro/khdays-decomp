/* func_ov025_0209c53c -- Ov008_LoadMenuBgWithAltChars (240 B, 13 relocs).
 * Loads the main-screen menu background (archive subfile 3) into a resource cell and uploads
 * its BG palette and BG3 character data, then frees the temp. When func_02024e5c() != 1 it
 * additionally overlays an alternate character bank: unpacks subfile 8 (skipping if the handle
 * is 0), resolves its character block (func_020119d4), flushes the data cache over it, and
 * uploads it as BG3 characters at offset 0x1000, then frees it. Mode 1 uses only the base BG.
 * Note the func_02024e5c() == 1 test is a materialized bool (moveq/movne/cmp#0) and the early
 * return fires when it is TRUE, so the alternate path runs for every mode EXCEPT 1.
 * func_02024c94 takes five args; resource-cell layout matches func_ov008_020592d4. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;
typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

extern u32   func_ov025_02084d18(int subfile);
extern u32   func_ov025_02084d50(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern int   func_02024e5c(void);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  func_020119d4(void *resource, Ov008CharacterBlock **block);
extern void  GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);

void func_ov025_0209c53c(void)
{
    void *resource;
    void *alternate;
    u32 altHandle;
    Ov008ResourceCell cell;
    Ov008CharacterBlock *altBlock;
    int isMode1;

    resource = func_0201ef9c(func_ov025_02084d18(3), 0xe);
    func_02024c94(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    isMode1 = func_02024e5c() == 1;
    if (isMode1) {
        return;
    }
    altHandle = func_ov025_02084d50(8);
    if (altHandle == 0) {
        return;
    }
    alternate = func_0201ef9c(altHandle, 0xe);
    func_020119d4(alternate, &altBlock);
    DC_FlushRange(altBlock->data, altBlock->size);
    GX_LoadBG3Char(altBlock->data, 0x1000, altBlock->size);
    if (alternate != 0) {
        NNSi_FndFreeFromDefaultHeap(alternate);
    }
}
