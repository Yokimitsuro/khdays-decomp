/* Enters New Game mode: sets activeMode=1, loads the resource container
 * (Msg_OpenContainerAndReadHeader) and sets up the resource tracker/cell from the template at
 * data_ov000_0205a858. */

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
extern const char gOv000UiNewgameResI18NPath[];
extern Ov000NewGameContext *data_ov000_0205ac28;

extern void *Msg_OpenContainerAndReadHeader(const void *descriptor, int mode);
extern void *Archive_LoadFile(u32 handle, int heapId);
extern void GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void OS_Terminate(void);
extern void GetResourceSubBlock_CHAR2(void *resource, Ov000ResourceBlock **block);
extern void DC_FlushRange(const void *address, u32 size);
extern void GXS_LoadBG1Char(const void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void Ov000_Container_Init(Ov000ResourceTracker *tracker,
                                const Ov000ResourceTrackerConfig *config);
extern void Ov000_LoadAndInitResourceSections(Ov000ResourceTracker *tracker, u32 handle);
extern void *Ov000_FindEntryByTag(Ov000ResourceTracker *tracker, u32 tag);
extern void Ov000_TagTracker_InvokeCallback(Ov000ResourceTracker *tracker, void *entry);


void Ov000_StartNewGameMode(void)
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

    container = Msg_OpenContainerAndReadHeader(gOv000UiNewgameResI18NPath, 14);
    data_ov000_0205ac28->activeMode = 1;
    data_ov000_0205ac28->pendingMode = 2;

    context = data_ov000_0205ac28;
    resource = Archive_LoadFile(ARCHIVE_HANDLE(context->archiveBase, 0), 14);
    Res_LoadSpriteSet(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    switch (GetLanguage()) {
    case 1:
        alternateHandle = 0;
        break;
    case 2:
        alternateHandle = ARCHIVE_HANDLE(container, 2);
        break;
    case 3:
        alternateHandle = ARCHIVE_HANDLE(container, 0);
        break;
    case 4:
        alternateHandle = ARCHIVE_HANDLE(container, 3);
        break;
    case 5:
        alternateHandle = ARCHIVE_HANDLE(container, 1);
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

    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    if (container != 0) {
        NNSi_FndFreeFromDefaultHeap(container);
    }

    context = data_ov000_0205ac28;
    Ov000_Container_Init(&context->resourceTracker, &trackerConfig);
    Ov000_LoadAndInitResourceSections(
        &context->resourceTracker,
        ARCHIVE_HANDLE(data_ov000_0205ac28->archiveBase, 2));
    entry = Ov000_FindEntryByTag(&context->resourceTracker, 0);
    Ov000_TagTracker_InvokeCallback(&context->resourceTracker, entry);
}
