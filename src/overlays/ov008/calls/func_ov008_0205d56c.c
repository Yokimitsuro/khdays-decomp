typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008CharacterBlock { u8 pad0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008PaletteBlock { u8 pad0000[0x08]; u32 size; void *data; } Ov008PaletteBlock;
typedef struct Ov008MenuContext {
    u8 pad0000[0x2e8]; u32 backgroundBackupSize;
    u8 pad02ec[0x2f0 - 0x2ec]; void *backgroundBackup;
    u8 pad02f4[0x1e78 - 0x2f4]; int savePageCount;
} Ov008MenuContext;
typedef void (*Ov008TrackerCallback)(void);

extern void *func_ov008_02050c28(void);
extern u32 func_ov008_02050f08(int slot);
extern void *func_0201ef9c(u32 handle, int heapId);
extern int func_02011988(void *resource, Ov008CharacterBlock **block);
extern int func_02011a20(void *resource, Ov008PaletteBlock **block);
extern void GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void MIi_CpuCopyFast(const void *source, void *destination, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void func_ov008_02055534(void *context, u32 handle);
extern void *func_ov008_02055808(void *context, u16 tag);
extern void func_ov008_0205589c(void *context, void *entry);
extern void func_ov008_020559c0(void *context, void *entry,
    u8 x, u8 y, u8 width, u8 height, u16 mask, Ov008TrackerCallback callback);

extern const u32 data_ov008_0208f130[];
extern void func_ov008_02066c30(void);
extern void func_ov008_02066de0(void);
extern void func_ov008_02066e1c(void);
extern void func_ov008_02066fb0(void);
extern void func_ov008_02066fe0(void);
extern void func_ov008_02067020(void);
extern void func_ov008_02067060(void);
extern void func_ov008_02067074(void);
extern void func_ov008_02067088(void);
extern void func_ov008_0206709c(void);
extern void func_ov008_020670b0(void);
extern void func_ov008_020670c4(void);
extern void func_ov008_020670d8(void);
extern void func_ov008_020670ec(void);

void func_ov008_0205d56c(Ov008MenuContext *context)
{
    void *layoutContext;
    void *resource;
    Ov008CharacterBlock *character;
    Ov008PaletteBlock *palette;
    void *entry;

    layoutContext = func_ov008_02050c28();
    resource = func_0201ef9c(func_ov008_02050f08(0x1b), 0xe);
    func_02011988(resource, &character);
    GX_LoadBG3Char(character->data, 0, character->size);
    context->backgroundBackupSize = 0x4000;
    context->backgroundBackup = NNSi_FndAllocFromDefaultExpHeap(0x4000);
    MIi_CpuCopyFast((u8 *)character->data + 0x5800,
        context->backgroundBackup, 0x4000);
    if (resource != 0) NNSi_FndFreeFromDefaultHeap(resource);

    resource = func_0201ef9c(func_ov008_02050f08(0x1c), 0xe);
    func_02011a20(resource, &palette);
    GX_LoadBGPltt(palette->data, 0, palette->size);
    if (resource != 0) NNSi_FndFreeFromDefaultHeap(resource);

    func_ov008_02055534(layoutContext, func_ov008_02050f08(0x1a));
    entry = func_ov008_02055808(layoutContext,
        data_ov008_0208f130[context->savePageCount - 1] & 0xffff);
    func_ov008_0205589c(layoutContext, entry);

    entry = func_ov008_02055808(layoutContext, 5);
    func_ov008_020559c0(layoutContext, entry, 0x68, 0x18, 0x80, 0x80, 0xffff, func_ov008_02066c30);
    entry = func_ov008_02055808(layoutContext, 6);
    func_ov008_020559c0(layoutContext, entry, 0xe8, 0x18, 0x10, 0x80, 0xffff, func_ov008_02066de0);
    entry = func_ov008_02055808(layoutContext, 7);
    func_ov008_020559c0(layoutContext, entry, 8, 0x18, 0x50, 0x80, 0xffff, func_ov008_02066e1c);
    entry = func_ov008_02055808(layoutContext, 0x28);
    func_ov008_020559c0(layoutContext, entry, 0x60, 0, 0x18, 0x10, 0xffff, func_ov008_02067060);
    entry = func_ov008_02055808(layoutContext, 0x29);
    func_ov008_020559c0(layoutContext, entry, 0x78, 0, 0x10, 0x10, 0xffff, func_ov008_02067074);
    entry = func_ov008_02055808(layoutContext, 0x2a);
    func_ov008_020559c0(layoutContext, entry, 0x88, 0, 0x10, 0x10, 0xffff, func_ov008_02067088);
    entry = func_ov008_02055808(layoutContext, 0x2b);
    func_ov008_020559c0(layoutContext, entry, 0x98, 0, 0x10, 0x10, 0xffff, func_ov008_0206709c);
    entry = func_ov008_02055808(layoutContext, 0x2c);
    func_ov008_020559c0(layoutContext, entry, 0xa8, 0, 0x10, 0x10, 0xffff, func_ov008_020670b0);
    entry = func_ov008_02055808(layoutContext, 0x2d);
    func_ov008_020559c0(layoutContext, entry, 0xb8, 0, 0x10, 0x10, 0xffff, func_ov008_020670c4);
    entry = func_ov008_02055808(layoutContext, 0x2e);
    func_ov008_020559c0(layoutContext, entry, 0xc8, 0, 0x10, 0x10, 0xffff, func_ov008_020670d8);
    entry = func_ov008_02055808(layoutContext, 0x2f);
    func_ov008_020559c0(layoutContext, entry, 0xd8, 0, 0x10, 0x10, 0xffff, func_ov008_020670ec);
    entry = func_ov008_02055808(layoutContext, 0x3f);
    func_ov008_020559c0(layoutContext, entry, 0, 0, 0x18, 0x10, 0xffff, func_ov008_02066fb0);
    entry = func_ov008_02055808(layoutContext, 0x40);
    func_ov008_020559c0(layoutContext, entry, 0x18, 0, 0x18, 0x10, 0xffff, func_ov008_02066fe0);
    entry = func_ov008_02055808(layoutContext, 0x41);
    func_ov008_020559c0(layoutContext, entry, 0x30, 0, 0x18, 0x10, 0xffff, func_ov008_02067020);
}
