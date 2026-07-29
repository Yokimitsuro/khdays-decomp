/* func_ov008_0206bdf0 -- Ov008_BuildMenuScreen (444 B, 27 relocs).
 * Full setup of a menu screen. Loads the sub-screen background (archive subfile 0x27) into a
 * resource cell and uploads its BG palette + BG3 characters; when func_ov008_02050f40(0) is
 * non-zero it overlays an alternate character bank (subfile 0, resolved by func_020119d4,
 * cache-flushed, uploaded at BG3 offset 0x1800). It then runs the sub-screen BG loader
 * (func_ov008_0206b754) on the first context, opens a second cell-list context
 * (func_ov008_02050c3c), attaches subfile 0x26 to it, registers cells for tags {1,2}, and lays
 * out two interactive items via func_ov008_020559c0 -- each taking a cell, geometry, a 0xffff
 * mask, and a draw/action callback (func_ov008_0206f3ac and func_ov008_0206f4c0). Returns 0.
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

extern void *func_ov008_02050cec(void);
extern void *func_ov008_02050c3c(void);
extern u32   func_ov008_02050f08(int subfile);
extern u32   func_ov008_02050f40(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  func_020119d4(void *resource, Ov008CharacterBlock **block);
extern void  GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GXS_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov008_0206b754(void *a, int b);
extern void  func_ov008_02055534(void *ctx, u32 handle);
extern void *func_ov008_02055808(void *ctx, int tag);
extern void  func_ov008_0205589c(void *ctx, void *cell);
extern void  func_ov008_020559c0(void *ctx, void *item, int a, int b, int c, int d, int mask, Ov008ItemCb cb);
extern void  func_ov008_0206f3ac(void);
extern void  func_ov008_0206f4c0(void);

int func_ov008_0206bdf0(void)
{
    void *ctx;
    void *ctx2;
    void *resource;
    void *alternate;
    u32 altHandle;
    Ov008ResourceCell cell;
    Ov008CharacterBlock *altBlock;

    ctx = func_ov008_02050cec();
    resource = func_0201ef9c(func_ov008_02050f08(0x27), 0xe);
    func_02024c94(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    altHandle = func_ov008_02050f40(0);
    if (altHandle != 0) {
        alternate = func_0201ef9c(altHandle, 0xe);
        func_020119d4(alternate, &altBlock);
        DC_FlushRange(altBlock->data, altBlock->size);
        GXS_LoadBG3Char(altBlock->data, 0x1800, altBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    }
    func_ov008_0206b754(ctx, 0);

    ctx2 = func_ov008_02050c3c();
    func_ov008_02055534(ctx2, func_ov008_02050f08(0x26));
    func_ov008_0205589c(ctx2, func_ov008_02055808(ctx2, 1));
    func_ov008_0205589c(ctx2, func_ov008_02055808(ctx2, 2));
    func_ov008_020559c0(ctx2, func_ov008_02055808(ctx2, 1), 0xa0, 8, 0x10, 0x90, 0xffff, func_ov008_0206f3ac);
    func_ov008_020559c0(ctx2, func_ov008_02055808(ctx2, 2), 0x10, 8, 0x88, 0x80, 0xffff, func_ov008_0206f4c0);
    return 0;
}
