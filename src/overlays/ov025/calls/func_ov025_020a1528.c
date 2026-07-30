/* func_ov025_020a1528 -- Ov008_BuildMenuScreen (444 B, 27 relocs).
 * Full setup of a menu screen. Loads the sub-screen background (archive subfile 0x27) into a
 * resource cell and uploads its BG palette + BG3 characters; when func_ov025_02084d50(0) is
 * non-zero it overlays an alternate character bank (subfile 0, resolved by func_020119d4,
 * cache-flushed, uploaded at BG3 offset 0x1800). It then runs the sub-screen BG loader
 * (func_ov025_020a0f1c) on the first context, opens a second cell-list context
 * (func_ov025_02084a64), attaches subfile 0x26 to it, registers cells for tags {1,2}, and lays
 * out two interactive items via func_ov025_020895d0 -- each taking a cell, geometry, a 0xffff
 * mask, and a draw/action callback (func_ov025_020a4998 and func_ov025_020a4aac). Returns 0.
 * Resource-cell / character-block layout matches func_ov008_020592d4. */
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
typedef void (*Ov008ItemCb)(void);

extern void *func_ov025_02084b14(void);
extern void *func_ov025_02084a64(void);
extern u32   func_ov025_02084d18(int subfile);
extern u32   func_ov025_02084d50(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  func_020119d4(void *resource, Ov008CharacterBlock **block);
extern void  GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GXS_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov025_020a0f1c(void *a, int b);
extern void  func_ov025_020891dc(void *ctx, u32 handle);
extern void *func_ov025_020894b0(void *ctx, int tag);
extern void  func_ov025_02089544(void *ctx, void *cell);
extern void  func_ov025_020895d0(void *ctx, void *item, int a, int b, int c, int d, int mask, Ov008ItemCb cb);
extern void  func_ov025_020a4998(void);
extern void  func_ov025_020a4aac(void);

int func_ov025_020a1528(void)
{
    void *ctx;
    void *ctx2;
    void *resource;
    void *alternate;
    u32 altHandle;
    Ov008ResourceCell cell;
    Ov008CharacterBlock *altBlock;

    ctx = func_ov025_02084b14();
    resource = func_0201ef9c(func_ov025_02084d18(0x27), 0xe);
    func_02024c94(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    altHandle = func_ov025_02084d50(0);
    if (altHandle != 0) {
        alternate = func_0201ef9c(altHandle, 0xe);
        func_020119d4(alternate, &altBlock);
        DC_FlushRange(altBlock->data, altBlock->size);
        GXS_LoadBG3Char(altBlock->data, 0x1800, altBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    }
    func_ov025_020a0f1c(ctx, 0);

    ctx2 = func_ov025_02084a64();
    func_ov025_020891dc(ctx2, func_ov025_02084d18(0x26));
    func_ov025_02089544(ctx2, func_ov025_020894b0(ctx2, 1));
    func_ov025_02089544(ctx2, func_ov025_020894b0(ctx2, 2));
    func_ov025_020895d0(ctx2, func_ov025_020894b0(ctx2, 1), 0xa0, 8, 0x10, 0x90, 0xffff, func_ov025_020a4998);
    func_ov025_020895d0(ctx2, func_ov025_020894b0(ctx2, 2), 0x10, 8, 0x88, 0x80, 0xffff, func_ov025_020a4aac);
    return 0;
}
