/* Ov000_LoadPageSubScreenLayer -- Scene 1: load the sub-screen layer for a menu page.
 * Opens the page's message/resource container, marks the load-state active in the
 * shared context (+0x4ad0/+0x4ad8), sets the sub display BG mode (DB_DISPCNT
 * bits 8-12 = 0x1e), initialises the context resource tracker, streams the page
 * palette to sub VRAM, then picks the language-specific character subfile
 * (GetLanguage: 1 = default charset from the page resource, 2..5 = subfiles
 * 1/3/0/2 of the container, 0 = OS_Terminate) and loads it into sub BG1.
 * Finally programs the sub BG scroll pair (0x01e601e3), registers the section
 * resource, invokes the tag callbacks 0..2, kicks the subsystem object at
 * context+0x4c, and opens windows 0/1 (WININ=0x3f, WINOUT=0x3a, DISPCNT bit13).
 * Declaration order resource < alternate < container is register-allocation
 * load-bearing (r4/r5/r6). */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

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

typedef struct Ov000LoadContext {
    u8 pad_0000[0x4ad0];
    int activeMode;
    u8 pad_4ad4[4];
    int pendingMode;
} Ov000LoadContext;

extern const Ov000ResourceTrackerConfig data_ov000_0205a6e0;
extern const char gOv000UiLoadResI18NPath[];
extern const char gOv000UiLoadLodB000Path[];
extern const char gOv000UiLoadLoadPath[];
extern Ov000LoadContext *data_ov000_0205ac24;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *Msg_OpenContainerAndReadHeader(const void *descriptor, int mode);
extern void *Archive_LoadFile(u32 handle, int heapId);
extern void GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void OS_Terminate(void);
extern void GetResourceSubBlock_CHAR2(void *resource, Ov000ResourceBlock **block);
extern void DC_FlushRange(const void *address, u32 size);
extern void GXS_LoadBG1Char(const void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void Ov000_Container_Init(Ov000LoadContext *tracker,
                                const Ov000ResourceTrackerConfig *config);
extern void Ov000_LoadAndInitResourceSections(Ov000LoadContext *tracker, u32 handle);
extern void *Ov000_FindEntryByTag(Ov000LoadContext *tracker, u32 tag);
extern void Ov000_TagTracker_InvokeCallback(Ov000LoadContext *tracker, void *entry);
extern void Ov000_InitSubsystemObject(void *object, int arg);


void Ov000_LoadPageSubScreenLayer(void)
{
    Ov000ResourceTrackerConfig trackerConfig;
    Ov000ResourceCell cell;
    Ov000ResourceBlock *alternateBlock;
    void *resource;
    void *alternate;
    u32 alternateHandle;
    void *container;
    Ov000LoadContext *context;
    void *entry;
    volatile u32 *dispcnt = (volatile u32 *)0x04001000;
    volatile u32 *scroll = (volatile u32 *)0x04001010;
    volatile u16 *winin = (volatile u16 *)0x04001048;

    NNSi_FndGetCurrentRootHeap();
    trackerConfig = data_ov000_0205a6e0;
    container = Msg_OpenContainerAndReadHeader(gOv000UiLoadResI18NPath, 14);
    context = data_ov000_0205ac24;
    context->activeMode = 1;
    data_ov000_0205ac24->pendingMode = data_ov000_0205ac24->activeMode;
    *dispcnt = (*dispcnt & ~0x1f00) | 0x1e00;
    Ov000_Container_Init(context, &trackerConfig);

    resource = Archive_LoadFile((u32)gOv000UiLoadLodB000Path, 14);
    Res_LoadSpriteSet(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    switch (GetLanguage()) {
    case 1:
        alternateHandle = 0;
        break;
    case 2:
        alternateHandle = ARCHIVE_HANDLE(container, 1);
        break;
    case 3:
        alternateHandle = ARCHIVE_HANDLE(container, 3);
        break;
    case 4:
        alternateHandle = ARCHIVE_HANDLE(container, 0);
        break;
    case 5:
        alternateHandle = ARCHIVE_HANDLE(container, 2);
        break;
    case 0:
    default:
        OS_Terminate();
        break;
    }

    if (alternateHandle != 0) {
        alternate = Archive_LoadFile(alternateHandle, 14);
        GetResourceSubBlock_CHAR2(alternate, &alternateBlock);
        DC_FlushRange(alternateBlock->data, alternateBlock->size);
        GXS_LoadBG1Char(alternateBlock->data, 0, alternateBlock->size);
        if (alternate != 0) {
            NNSi_FndFreeFromDefaultHeap(alternate);
        }
    } else {
        GXS_LoadBG1Char(cell.character->data, 0, cell.character->size);
    }

    if (container != 0) {
        NNSi_FndFreeFromDefaultHeap(container);
    }
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    scroll[0] = 0x01e601e3;
    scroll[2] = 0x01e601e3;
    Ov000_LoadAndInitResourceSections(data_ov000_0205ac24, (u32)gOv000UiLoadLoadPath);
    entry = Ov000_FindEntryByTag(context, 0);
    Ov000_TagTracker_InvokeCallback(context, entry);
    entry = Ov000_FindEntryByTag(context, 1);
    Ov000_TagTracker_InvokeCallback(context, entry);
    entry = Ov000_FindEntryByTag(context, 2);
    Ov000_TagTracker_InvokeCallback(context, entry);
    Ov000_InitSubsystemObject((u8 *)data_ov000_0205ac24 + 0x4c, 0);

    winin[0] = (winin[0] & ~0x3f) | 0x3f;
    winin[1] = (winin[1] & ~0x3f) | 0x3a;
    *dispcnt = (*dispcnt & ~0xe000) | 0x2000;
}
