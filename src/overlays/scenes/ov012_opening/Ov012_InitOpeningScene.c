/* Initializes the opening scene, clears its script workspace, loads the NFTR font and opening
 * archives, builds 41 sprite resource sets, starts op/scr.z and returns the opening-scene update
 * callback. */

#include "nitro/types.h"
#include "game/archive.h"

typedef struct SpriteResSet {
    int words[3];
} SpriteResSet;

extern int data_ov012_0205cb20;
extern char gOv012TextFontEu10AllPath[];
extern int data_ov012_0205c2d0;
extern char gOv012OpOpPath[];
extern int data_ov012_0205caf4;
extern char gOv012OpScrPath[];
extern u32 OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((u32)&OVERLAY_24_ID)

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void LoadOverlaySync(int processor, int overlayId);
extern void Ov012_ConfigureOpeningDisplay(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Font_LoadUTF16(void *dst, const void *path);
extern void GX_LoadBGPltt(const void *src, int offset, int size);
extern void GXS_LoadBGPltt(const void *src, int offset, int size);
extern void *Msg_OpenContainerAndReadHeader(const void *path, int heapId);
extern void *Archive_LoadFile(u32 archiveEntry, int heapId);
extern u32 GetLanguage(void);
extern void ZeroHalfThenFree(void *header);
extern void Res_LoadSpriteSet(SpriteResSet *set, void *archive, int character,
                         int screen, int palette);
extern void StoreGlobalArrayEntry(int slot, const void *table);
extern void Stream_DecodeIntoStagingBuffer(void *dst, const void *path, void *unused,
                         void *workspace);
extern void Ov012_RunOpeningScene(void);

void *Ov012_InitOpeningScene(int alternateMode) {
    char *root;
    void *header;
    u32 archiveEntry;
    int paletteIndex;
    int resourceIndex;
    int screenIndex;
    u32 rawKeys;
    u16 keys;
    char *workspace;
    SpriteResSet *nextSet;

    root = (char *)NNSi_FndGetCurrentRootHeap();
    LoadOverlaySync(0, FS_OVERLAY_ID_ov024);
    Ov012_ConfigureOpeningDisplay();
    data_ov012_0205cb20 = (int)root;
    *(u16 *)(root + 0) = 0;
    *(u16 *)(root + 2) = 0;
    if (alternateMode == 0) {
        *(u16 *)(root + 2) |= 0x10;
    }
    *(int *)(root + 0x8be8) = -1;
    *(int *)(root + 0x8bd8) = *(int *)(root + 0x8bdc) = 0;
    workspace = root + 0x198;
    *(u8 *)(root + 0x8be0) = 0;
    *(u8 *)(root + 0x8bf0) = 0;
    MI_CpuFill8(workspace + 0x8400, 0, 0x5a4);
    Font_LoadUTF16(root + 0x8b40, gOv012TextFontEu10AllPath);
    GX_LoadBGPltt(&data_ov012_0205c2d0, 0x1a0, 0x20);
    GXS_LoadBGPltt(&data_ov012_0205c2d0, 0x1a0, 0x20);
    *(void **)(root + 0x85a4) = root + 0x8b4c;
    header = Msg_OpenContainerAndReadHeader(gOv012OpOpPath, 0xe);
    archiveEntry = ARCHIVE_HANDLE(header, 0);
    *(void **)(root + 0x8bf8) = Archive_LoadFile(archiveEntry, 0xe);
    *(void **)(root + 0x8bfc) =
        Archive_LoadFile(archiveEntry | (GetLanguage() & 0x1ff), 0xe);
    ZeroHalfThenFree(header);

    resourceIndex = 0;
    paletteIndex = 0;
    screenIndex = 0;
    do {
        Res_LoadSpriteSet((SpriteResSet *)(root + 0x8c00 + resourceIndex * 12),
                      *(void **)(root + 0x8bf8), screenIndex, screenIndex,
                      paletteIndex);
        nextSet = (SpriteResSet *)(root + 0x8c00 + (resourceIndex + 1) * 12);
        resourceIndex += 2;
        Res_LoadSpriteSet(nextSet,
                      *(void **)(root + 0x8bf8), screenIndex + 1,
                      screenIndex + 1, -1);
        if (paletteIndex < 13) {
            nextSet = (SpriteResSet *)(root + 0x8c00 + resourceIndex * 12);
            resourceIndex++;
            Res_LoadSpriteSet(nextSet,
                          *(void **)(root + 0x8bfc), paletteIndex,
                          paletteIndex, -1);
        }
        paletteIndex++;
        screenIndex += 2;
    } while (paletteIndex < 14);

    StoreGlobalArrayEntry(3, &data_ov012_0205caf4);
    Stream_DecodeIntoStagingBuffer(root + 4, gOv012OpScrPath, 0, root + 0x8598);
    *(u16 *)(root + 2) |= 1;
    *(u8 *)(root + 0x8be1) = 0;
    rawKeys = *(volatile u16 *)0x04000130 | *(volatile u16 *)0x027fffa8;
    keys = (rawKeys ^ 0x2fff) & 0x2fff;
    *(int *)(root + 0x8bec) = keys & 8;
    return (void *)Ov012_RunOpeningScene;
}