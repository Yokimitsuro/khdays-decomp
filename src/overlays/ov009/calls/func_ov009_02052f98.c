typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct CharacterResourceBlock {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterResourceBlock;

typedef struct PaletteResourceBlock {
    u8 pad_00[0x08];
    u32 size;
    void *data;
} PaletteResourceBlock;

typedef struct ScreenResourceBlock {
    u8 pad_00[0x08];
    u32 size;
    void *data;
} ScreenResourceBlock;

typedef struct GraphicsResourceCell {
    ScreenResourceBlock *screen;
    CharacterResourceBlock *character;
    PaletteResourceBlock *palette;
} GraphicsResourceCell;

extern const char data_ov009_02056338[];
extern const char data_ov009_02056350[];

extern int   func_ov009_0204e42c(void);
extern void *func_0201ef9c(const void *handle, int heapId);
extern void  func_02024c94(GraphicsResourceCell *cell, void *resource,
                          int screenIndex, int characterIndex,
                          int paletteIndex);
extern void  GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern u32   func_ov009_0204e5b8(int index);
extern void  func_020119d4(void *resource, CharacterResourceBlock **block);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  func_ov009_020522f8(int tracker, const void *resource);
extern int   func_ov009_020525cc(int tracker, u32 tag);
extern void  func_ov009_02052660(int tracker, int entry);

static volatile u32 *const REG_DISPCAPCNT =
    (volatile u32 *)0x04000018;

void func_ov009_02052f98(void)
{
    int tracker;
    void *resource;
    GraphicsResourceCell cell;
    u32 alternateHandle;
    void *alternate;
    CharacterResourceBlock *alternateBlock;
    int entry;

    tracker = func_ov009_0204e42c();
    resource = func_0201ef9c(data_ov009_02056338, 14);
    func_02024c94(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    alternateHandle = func_ov009_0204e5b8(2);
    if (alternateHandle != 0) {
        alternate = func_0201ef9c((const void *)alternateHandle, 14);
        func_020119d4(alternate, &alternateBlock);
        DC_FlushRange(alternateBlock->data, alternateBlock->size);
        GX_LoadBG3Char(alternateBlock->data, 0, alternateBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    } else {
        GX_LoadBG3Char(cell.character->data, 0, cell.character->size);
    }

    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    *REG_DISPCAPCNT = 0x01e600e3;
    func_ov009_020522f8(tracker, data_ov009_02056350);
    entry = func_ov009_020525cc(tracker, 0);
    func_ov009_02052660(tracker, entry);
    entry = func_ov009_020525cc(tracker, 1);
    func_ov009_02052660(tracker, entry);
}
