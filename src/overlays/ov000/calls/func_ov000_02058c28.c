typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int  u32;

typedef struct Ov000CharacterBlock {
    u8 pad_0000[0x10];
    u32 size;
    void *data;
} Ov000CharacterBlock;

typedef struct Ov000PaletteBlock {
    u8 pad_0000[0x08];
    u32 size;
    void *data;
} Ov000PaletteBlock;

typedef struct Ov000ScreenBlock {
    u8 pad_0000[0x08];
    u32 size;
    u8 data[1];
} Ov000ScreenBlock;

typedef struct Ov000ResourceCell {
    Ov000ScreenBlock *screen;
    Ov000CharacterBlock *character;
    Ov000PaletteBlock *palette;
} Ov000ResourceCell;

typedef struct Ov000ListGraphicsContext {
    u8 pad_0000[0x84];
    void *archiveBase;
    u8 pad_0088[0x95e4];
    u16 graphicsFlags;
    u8 pad_966e[0x0aa2];
    u8 secondaryScreenData[0x800];
    u8 mainScreenData[0x800];
} Ov000ListGraphicsContext;

extern const char data_ov000_0205aba8[];

extern Ov000ListGraphicsContext *NNSi_FndGetCurrentRootHeap(void);
extern void *func_02024ee8(const void *descriptor, int mode);
extern int func_02024e5c(void);
extern void OS_Terminate(void);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void func_02024c94(Ov000ResourceCell *cell, void *resource,
                         int screenIndex, int characterIndex, int paletteIndex);
extern void GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void func_020119d4(void *resource, Ov000CharacterBlock **block);
extern void DC_FlushRange(const void *address, u32 size);
extern void GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void MIi_CpuCopy32(
    const void *source, void *destination, u32 size);
extern void GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void GXS_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void *G2_GetBG2CharPtr(void);
extern void MIi_CpuClearFast(
    u32 value, void *destination, u32 size);
extern void func_02024fd4(void *container);

#define OV000_ARCHIVE_MASK 0x00fffffc
#define OV000_SUBFILE(base, index) \
    (((((u32)(base) + 0x8000) & OV000_ARCHIVE_MASK) << 7) | \
     0x80000000 | (index))

void func_ov000_02058c28(void)
{
    Ov000ListGraphicsContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000ResourceCell cell;
    Ov000CharacterBlock *alternateBlock;
    void *resource;
    void *container;
    void *alternate;
    u32 alternateHandle;

    container = func_02024ee8(data_ov000_0205aba8, 14);

    switch (func_02024e5c()) {
    case 1:
        alternateHandle = 0;
        break;
    case 2:
        alternateHandle = OV000_SUBFILE(container, 1);
        break;
    case 3:
        alternateHandle = OV000_SUBFILE(container, 3);
        break;
    case 4:
        alternateHandle = OV000_SUBFILE(container, 0);
        break;
    case 5:
        alternateHandle = OV000_SUBFILE(container, 2);
        break;
    case 0:
    default:
        OS_Terminate();
        break;
    }

    resource =
        func_0201ef9c(OV000_SUBFILE(context->archiveBase, 3), 14);
    func_02024c94(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    if (alternateHandle != 0) {
        alternate = func_0201ef9c(alternateHandle, 14);
        func_020119d4(alternate, &alternateBlock);
        DC_FlushRange(alternateBlock->data, alternateBlock->size);
        GX_LoadBG3Char(alternateBlock->data, 0, alternateBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    } else {
        GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    }

    MIi_CpuCopy32(
        cell.screen->data, context->mainScreenData, cell.screen->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    resource =
        func_0201ef9c(OV000_SUBFILE(context->archiveBase, 0), 14);
    func_02024c94(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    context->graphicsFlags |= 4;
    MIi_CpuClearFast(0, (u8 *)G2_GetBG2CharPtr() + 0x3200, 0x40);
    MIi_CpuClearFast(
        0x00c800c8, context->secondaryScreenData, 0x800);
    func_02024fd4(container);
}
