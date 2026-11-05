/* Sets up the boot text screen: fades to black, waits VBlank, assigns the BG and BG-extended-
 * palette VRAM banks, then loads the font resource, the tile-text renderer, the message archive and
 * the text frame for the given mode. */

#include "nitro/types.h"
#include "game/heap.h"

typedef struct Ov000MessageArchive {
    u32 words[3];
} Ov000MessageArchive;

typedef struct Ov000FontResource {
    u32 words[3];
} Ov000FontResource;

typedef struct Ov000TileTextRenderer {
    u32 words[16];
} Ov000TileTextRenderer;

typedef struct Ov000TextFrame {
    u16 destinationX;
    u16 destinationY;
    u16 width;
    u16 height;
    u16 sourceX;
    u16 sourceY;
    u16 field_0c;
    u16 paletteCount;
} Ov000TextFrame;

typedef struct Ov000BootContext {
    u8 pad_0000[0x4c4c];
    int alternateLanguage;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void SetMasterBrightnessMain(int brightness);
extern void SetMasterBrightnessSub(int brightness);
extern void OS_WaitVBlankIntr(void);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void GX_SetGraphicsMode(int enabled, int field, int mode);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, unsigned int size);
extern void Ov000_InitResourceRecord(Ov000MessageArchive *archive,
                                const char *resourceName);
extern void Font_LoadUTF16(Ov000FontResource *font, const char *resourceName);
extern void GX_LoadBGPltt(const void *palette, int offset, int size);
extern void TileTextRenderer_Init(Ov000TileTextRenderer *renderer, int layer,
                          Ov000FontResource *font,
                          const Ov000TextFrame *frame);
extern void CallVirtSlot1(Ov000TileTextRenderer *renderer, int mode);
extern void *Ov000_GetVarRecordByIndex(Ov000MessageArchive *archive, int index);
extern void Text_DrawDirectional(Ov000TileTextRenderer *renderer, int x, int y,
                          int field, int width, const void *record);
extern void Text_UploadTileBuffer(Ov000TileTextRenderer *renderer);
extern void FrameStep_UpdateTaskQueue(void);
extern void TileTextRenderer_Destroy(Ov000TileTextRenderer *renderer);
extern void Ov000_FreeResourceRecordBuffer(Ov000MessageArchive *archive);

extern const char gOv000UiLoadLrdTextPath[];
extern const char gOv000TextFontEu10AllPath[];
extern const u16 data_02042958[];

void Ov000_SetupBootTextScreen(int mode) {
    Ov000FontResource font;
    Ov000TileTextRenderer renderer;
    Ov000MessageArchive messages;
    Ov000TextFrame frame;
    Ov000BootContext *context;
    const void *record;

    context = NNSi_FndGetCurrentRootHeap();
    SetMasterBrightnessMain(-0x10);
    SetMasterBrightnessSub(-0x10);
    OS_WaitVBlankIntr();
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    GX_SetGraphicsMode(1, 0, 1);

    *(vu16 *)0x0400000e =
        (*(vu16 *)0x0400000e & 0x43) | 0x204;
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x600);

    Ov000_InitResourceRecord(&messages, gOv000UiLoadLrdTextPath);
    Font_LoadUTF16(&font, gOv000TextFontEu10AllPath);
    GX_LoadBGPltt(data_02042958, 0x1a0, 0x20);

    frame.destinationX = 1;
    frame.sourceX = 1;
    frame.destinationY = 0;
    frame.field_0c = 0;
    frame.width = 0x1e;
    frame.height = 0x15;
    frame.sourceY = 0xd;
    frame.paletteCount = 6;

    TileTextRenderer_Init(&renderer, 3, &font, &frame);
    *(vu16 *)0x04000304 |= 0x8000;
    *(vu32 *)0x04000000 =
        (*(vu32 *)0x04000000 & ~0x1f00) | 0x800;
    CallVirtSlot1(&renderer, 0);

    if (mode == 0) {
        record = Ov000_GetVarRecordByIndex(&messages, 0x17);
        Text_DrawDirectional(&renderer, 0x78, 0x46, 1, 0x10, record);
    } else {
        record = Ov000_GetVarRecordByIndex(
            &messages, context->alternateLanguage == 1 ? 0x13 : 0x14);
        Text_DrawDirectional(&renderer, 0x78, 0x3c, 1, 0x10, record);
        record = Ov000_GetVarRecordByIndex(&messages, 0x15);
        Text_DrawDirectional(&renderer, 0x78, 0x5a, 1, 0x10, record);
    }

    Text_UploadTileBuffer(&renderer);
    SetMasterBrightnessMain(0);
    SetMasterBrightnessSub(0);
    OS_WaitVBlankIntr();
    FrameStep_UpdateTaskQueue();
    TileTextRenderer_Destroy(&renderer);
    FontResource_Destroy(&font);
    Ov000_FreeResourceRecordBuffer(&messages);
}
