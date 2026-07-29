/* func_ov008_020592d4 -- Ov008_SetupMenuBgCells (248 B, 18 relocs).
 * Loads the main-menu background graphics and seeds its cell list. Sets the 3D H-offset,
 * grabs the menu cell-list context (02050c28), unpacks archive subfile 0xa into a resource
 * cell (func_02024c94 takes FIVE args -- the trailing stack 0 is the ROM's str r2,[sp]),
 * uploads the BG3 palette and character data from the unpacked blocks, frees the temp
 * resource, attaches subfile 7 (02055534), then registers four cells (tags 0,1,2,4 -- 3 is
 * deliberately skipped) by looking each up (02055808) and adding it (0205589c).
 * Resource-cell layout mirrors the ov000 loader (screen/character/palette pointer trio). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock   { u8 pad_0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008ScreenBlock    { u8 pad_0000[0x08]; u32 size; u8 data[1]; } Ov008ScreenBlock;
typedef struct Ov008ResourceCell {
    Ov008ScreenBlock    *screen;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock   *palette;
} Ov008ResourceCell;

extern void  G3X_SetHOffset(int off);
extern void *func_ov008_02050c28(void);
extern u32   func_ov008_02050f08(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov008_02055534(void *ctx, u32 handle);
extern void *func_ov008_02055808(void *ctx, int tag);
extern void  func_ov008_0205589c(void *ctx, void *cell);

void func_ov008_020592d4(void)
{
    void *ctx;
    void *resource;
    Ov008ResourceCell cell;

    G3X_SetHOffset(-0x3b);
    ctx = func_ov008_02050c28();
    resource = func_0201ef9c(func_ov008_02050f08(0xa), 0xe);
    func_02024c94(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    func_ov008_02055534(ctx, func_ov008_02050f08(7));
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 0));
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 1));
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 2));
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 4));
}
