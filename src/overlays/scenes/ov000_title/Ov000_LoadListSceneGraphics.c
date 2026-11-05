/* Loads the list scene's BG graphics. Opens the archive descriptor gOv000UiThrThrI18NPath, then picks
 * an alternate BG3 character subfile by variant (GetLanguage: 1->none, 2->#1, 3->#3, 4->#0,
 * 5->#2, else terminate). Loads the main BG palette + (alternate or default) BG3 char + screen from
 * archive subfile #3, and the sub-screen palette/char from subfile #0. Sets graphicsFlags|=4,
 * clears a 0x40 span of BG2 char and fills the sub-screen map with 0xc8. */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

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

extern const char gOv000UiThrThrI18NPath[];

extern Ov000ListGraphicsContext *NNSi_FndGetCurrentRootHeap(void);
extern void *Msg_OpenContainerAndReadHeader(const void *descriptor, int mode);
extern void OS_Terminate(void);
extern void *Archive_LoadFile(u32 handle, int heapId);
extern void GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern void GetResourceSubBlock_CHAR2(void *resource, Ov000CharacterBlock **block);
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


void Ov000_LoadListSceneGraphics(void)
{
    Ov000ListGraphicsContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000ResourceCell cell;
    Ov000CharacterBlock *alternateBlock;
    void *resource;
    void *container;
    void *alternate;
    u32 alternateHandle;

    container = Msg_OpenContainerAndReadHeader(gOv000UiThrThrI18NPath, 14);

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

    resource =
        Archive_LoadFile(ARCHIVE_HANDLE(context->archiveBase, 3), 14);
    Res_LoadSpriteSet(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    if (alternateHandle != 0) {
        alternate = Archive_LoadFile(alternateHandle, 14);
        GetResourceSubBlock_CHAR2(alternate, &alternateBlock);
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
        Archive_LoadFile(ARCHIVE_HANDLE(context->archiveBase, 0), 14);
    Res_LoadSpriteSet(&cell, resource, 0, 0, 0);
    GXS_LoadBGPltt(cell.palette->data, 0, cell.palette->size);
    GXS_LoadBG3Char(cell.character->data, 0, cell.character->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }

    context->graphicsFlags |= 4;
    MIi_CpuClearFast(0, (u8 *)G2_GetBG2CharPtr() + 0x3200, 0x40);
    MIi_CpuClearFast(
        0x00c800c8, context->secondaryScreenData, 0x800);
    ZeroHalfThenFree(container);
}
