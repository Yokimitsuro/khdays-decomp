/* Loads the save menu background's palette and its variant character set, then the layout's
 * resources. */

#include "nitro/types.h"
#include "game/engine.h"

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

extern const char gOv009UiCmSavB000Path[];
extern const char gOv009UiCmSavePath[];

extern int   Ov009_GetCtxBlock9500(void);
extern void *Archive_LoadFile(const void *handle, int heapId);
extern void  GX_LoadBGPltt(const void *source, u32 offset, u32 size);
extern u32   Ov009_PackHandleTag(int index);
extern void  GetResourceSubBlock_CHAR2(void *resource, CharacterResourceBlock **block);
extern void  DC_FlushRange(const void *address, u32 size);
extern void  GX_LoadBG3Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  Ov009_LoadAndInitResourceSections(int tracker, const void *resource);
extern int   Ov009_FindEntryByTag(int tracker, u32 tag);
extern void  Ov009_TagTracker_InvokeCallback(int tracker, int entry);

/* BG2HOFS and BG2VOFS, engine A's BG2 scroll, written as one word. */
static volatile u32 *const REG_BG2OFS =
    (volatile u32 *)0x04000018;

void Ov009_LoadMenuBgWithVariantChars(void)
{
    int tracker;
    void *resource;
    GraphicsResourceCell cell;
    u32 alternateHandle;
    void *alternate;
    CharacterResourceBlock *alternateBlock;
    int entry;

    tracker = Ov009_GetCtxBlock9500();
    resource = Archive_LoadFile(gOv009UiCmSavB000Path, 14);
    Res_LoadSpriteSet(&cell, resource, 0, 0, 0);
    GX_LoadBGPltt(cell.palette->data, 0, cell.palette->size);

    alternateHandle = Ov009_PackHandleTag(2);
    if (alternateHandle != 0) {
        alternate = Archive_LoadFile((const void *)alternateHandle, 14);
        GetResourceSubBlock_CHAR2(alternate, &alternateBlock);
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

    *REG_BG2OFS = 0x01e600e3;    /* horizontal 0xe3, vertical 0x1e6 */
    Ov009_LoadAndInitResourceSections(tracker, gOv009UiCmSavePath);
    entry = Ov009_FindEntryByTag(tracker, 0);
    Ov009_TagTracker_InvokeCallback(tracker, entry);
    entry = Ov009_FindEntryByTag(tracker, 1);
    Ov009_TagTracker_InvokeCallback(tracker, entry);
}
