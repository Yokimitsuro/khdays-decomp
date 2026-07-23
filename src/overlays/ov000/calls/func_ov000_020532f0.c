typedef unsigned char  u8;
typedef unsigned int  u32;

typedef struct Ov000ResourceBlock {
    u8 pad_0000[0x10];
    u32 size;
    void *data;
} Ov000ResourceBlock;

typedef struct Ov000PaletteBlock {
    u8 pad_0000[0x08];
    u32 size;
    void *data;
} Ov000PaletteBlock;

typedef struct Ov000ResourceCell {
    u32 reserved;
    Ov000ResourceBlock *character;
    Ov000PaletteBlock *palette;
} Ov000ResourceCell;

typedef struct Ov000ResourceTrackerConfig {
    u32 entryCapacity;
    u32 nodeCapacity;
    u32 auxiliaryCapacity;
    void (*entryCallback)(void);
    void (*nodeCallback)(void);
} Ov000ResourceTrackerConfig;

typedef struct Ov000ResourceTracker {
    u8 data[0x4c];
} Ov000ResourceTracker;

typedef struct Ov000NewGameContext {
    u8 pad_0000[0x28];
    void *archiveBase;
    Ov000ResourceTracker resourceTracker;
    u8 pad_0078[0x4bc4 - 0x78];
    int activeMode;
    int pendingMode;
} Ov000NewGameContext;

extern const Ov000ResourceTrackerConfig data_ov000_0205a858;
extern const char data_ov000_0205ab20[];
extern Ov000NewGameContext *data_ov000_0205ac28;

extern void *func_02024ee8(const void *descriptor, int mode);
extern void *func_0201ef9c(u32 handle, int heapId);
extern void func_02024c94(Ov000ResourceCell *cell, void *resource,
                         int characterIndex, int paletteIndex, int screenIndex);
extern void GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern int func_02024e5c(void);
extern void OS_Terminate(void);
extern void func_020119d4(void *resource, Ov000ResourceBlock **block);
extern void DC_FlushRange(const void *address, u32 size);
extern void GXS_LoadBG1Char(const void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void func_ov000_0205647c(Ov000ResourceTracker *tracker,
                                const Ov000ResourceTrackerConfig *config);
extern void func_ov000_02056544(Ov000ResourceTracker *tracker, u32 handle);
extern void *func_ov000_02056818(Ov000ResourceTracker *tracker, u32 tag);
extern void func_ov000_020568ac(Ov000ResourceTracker *tracker, void *entry);

#define OV000_ARCHIVE_MASK 0x00fffffc
#define OV000_SUBFILE(base, index) \
    (((((u32)(base) + 0x8000) & OV000_ARCHIVE_MASK) << 7) | \
     0x80000000 | (index))

void func_ov000_020532f0(void)
{
    Ov000ResourceTrackerConfig trackerConfig = data_ov000_0205a858;
    Ov000ResourceCell cell;
    Ov000ResourceBlock *alternateBlock;
    void *alternate;
    u32 alternateHandle;
    void *container;
    void *resource;
    Ov000NewGameContext *context;
    void *entry;

    container = func_02024ee8(data_ov000_0205ab20, 14);
    data_ov000_0205ac28->activeMode = 1;
    data_ov000_0205ac28->pendingMode = 2;

    context = data_ov000_0205ac28;
    resource = func_0201ef9c(OV000_SUBFILE(context->archiveBase, 0), 14);
    func_02024c94(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    switch (func_02024e5c()) {
    case 1:
        alternateHandle = 0;
        break;
    case 2:
        alternateHandle = OV000_SUBFILE(container, 2);
        break;
    case 3:
        alternateHandle = OV000_SUBFILE(container, 0);
        break;
    case 4:
        alternateHandle = OV000_SUBFILE(container, 3);
        break;
    case 5:
        alternateHandle = OV000_SUBFILE(container, 1);
        break;
    case 0:
    default:
        OS_Terminate();
        break;
    }

    if (alternateHandle != 0) {
        alternate = func_0201ef9c(alternateHandle, 14);
        func_020119d4(alternate, &alternateBlock);
        DC_FlushRange(alternateBlock->data, alternateBlock->size);
        GXS_LoadBG1Char(alternateBlock->data, 0, alternateBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    } else {
        GXS_LoadBG1Char(cell.character->data, 0, cell.character->size);
    }

    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    if (container != 0) {
        NNSi_FndFreeFromDefaultHeap(container);
    }

    context = data_ov000_0205ac28;
    func_ov000_0205647c(&context->resourceTracker, &trackerConfig);
    func_ov000_02056544(
        &context->resourceTracker,
        OV000_SUBFILE(data_ov000_0205ac28->archiveBase, 2));
    entry = func_ov000_02056818(&context->resourceTracker, 0);
    func_ov000_020568ac(&context->resourceTracker, entry);
}
