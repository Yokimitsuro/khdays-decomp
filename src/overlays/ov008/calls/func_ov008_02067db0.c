/* func_ov008_02067db0 -- Ov008_LoadMenuBgWithVariantChars (300 B, 19 relocs).
 * Loads a menu background from a fixed archive descriptor (data_ov008_020904a4, passed to
 * func_0201ef9c by address), uploads its BG palette, then selects the BG3 character source:
 * if func_ov008_02050f40(2) is non-zero it unpacks that alternate subfile, resolves its
 * character block (func_020119d4), flushes the data cache and uploads it; otherwise it uses
 * the cell's own character block. After freeing the temp resource it programs the BG2 scroll
 * registers (a raw write of 0x01e600e3 to 0x04000018 -- both operands are pool literals, no
 * relocation), attaches a second descriptor (data_ov008_020904bc) to the cell-list context via
 * func_ov008_02055534, and registers cells for tags {0,1}. Resource-cell / character-block
 * layout matches func_ov008_020592d4; func_02024c94 takes five args. */
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

extern u8 data_ov008_020904a4[];
extern u8 data_ov008_020904bc[];
extern void *func_ov008_02050c28(void);
extern u32   func_ov008_02050f40(int subfile);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void  func_02024c94(Ov008ResourceCell *cell, void *resource, int a, int b, int c);
extern void  func_020119d4(void *resource, Ov008CharacterBlock **block);
extern void  GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void  GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov008_02055534(void *ctx, void *desc);
extern void *func_ov008_02055808(void *ctx, int tag);
extern void  func_ov008_0205589c(void *ctx, void *cell);

void func_ov008_02067db0(void)
{
    void *ctx;
    void *resource;
    void *alternate;
    u32 altHandle;
    Ov008ResourceCell cell;
    Ov008CharacterBlock *altBlock;

    ctx = func_ov008_02050c28();
    resource = func_0201ef9c((u32)data_ov008_020904a4, 0xe);
    func_02024c94(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    altHandle = func_ov008_02050f40(2);
    if (altHandle != 0) {
        alternate = func_0201ef9c(altHandle, 0xe);
        func_020119d4(alternate, &altBlock);
        DC_FlushRange(altBlock->data, altBlock->size);
        GX_LoadBG3Char(altBlock->data, 0, altBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    } else {
        GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    }
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    *(volatile u32 *)0x04000018 = 0x01e600e3;
    func_ov008_02055534(ctx, data_ov008_020904bc);
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 0));
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, 1));
}
