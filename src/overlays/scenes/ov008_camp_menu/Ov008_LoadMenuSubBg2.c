/* Ov008_LoadMenuSubBg2 -- Ov008_LoadMenuSubBg2 (152 B, 8 relocs).
 * Loads a sub-screen BG2 character bank for the menu. Fetches two contexts (02050cec for the
 * archive base, 02050c3c for the cell-list), and returns early if param_1 is 0. Builds a packed
 * archive-subfile handle for subfile 0x30 from ctx->archiveBase (the standard NDS archive-handle
 * formula), unpacks it (GetResourceSubBlock_CHAR resolves the character block), uploads the block as BG2
 * characters at offset 0x4f40, frees the temp resource, and attaches a descriptor
 * (gOv008UiTutorialTutPath) to the cell-list context. Character-block layout matches the loader family
 * (size at +0x10, data at +0x14). */

#include "nitro/types.h"
#include "game/archive.h"

typedef struct Ov008CharacterBlock { u8 pad_0000[0x10]; u32 size; void *data; } Ov008CharacterBlock;
typedef struct Ov008MenuContext { u8 pad_0000[0x34]; u32 archiveBase; } Ov008MenuContext;

extern u8 gOv008UiTutorialTutPath[];
extern Ov008MenuContext *Ov008_GetPageB(void);
extern void *Ov008_GetCtxBlock954c(void);
extern void *Archive_LoadFile(u32 handle, int heapId);
extern void  GetResourceSubBlock_CHAR(void *resource, Ov008CharacterBlock **block);
extern void  GXS_LoadBG2Char(const void *source, u32 offset, u32 size);
extern void  NNSi_FndFreeFromDefaultHeap(void *allocation);
extern void  Ov008_LoadLayoutResource(void *ctx, void *desc);


void Ov008_LoadMenuSubBg2(int param_1)
{
    Ov008MenuContext *ctx1 = Ov008_GetPageB();
    void *ctx2 = Ov008_GetCtxBlock954c();
    void *resource;
    Ov008CharacterBlock *block;

    if (param_1 == 0) {
        return;
    }
    resource = Archive_LoadFile(ARCHIVE_HANDLE(ctx1->archiveBase, 0x30), 0xe);
    GetResourceSubBlock_CHAR(resource, &block);
    GXS_LoadBG2Char(block->data, 0x4f40, block->size);
    if (resource != 0) {
        NNSi_FndFreeFromDefaultHeap(resource);
    }
    Ov008_LoadLayoutResource(ctx2, gOv008UiTutorialTutPath);
}
