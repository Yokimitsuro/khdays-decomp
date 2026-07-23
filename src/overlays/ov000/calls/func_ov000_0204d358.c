typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

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
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void OS_WaitVBlankIntr(void);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void func_020056b4(int enabled, int field, int mode);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, unsigned int size);
extern void func_ov000_02056938(Ov000MessageArchive *archive,
                                const char *resourceName);
extern void func_0202f7fc(Ov000FontResource *font, const char *resourceName);
extern void GX_LoadBGPltt(const void *palette, int offset, int size);
extern void func_0202f834(Ov000TileTextRenderer *renderer, int layer,
                          Ov000FontResource *font,
                          const Ov000TextFrame *frame);
extern void func_0202fa20(Ov000TileTextRenderer *renderer, int mode);
extern void *func_ov000_02056970(Ov000MessageArchive *archive, int index);
extern void func_0202fa38(Ov000TileTextRenderer *renderer, int x, int y,
                          int field, int width, const void *record);
extern void func_0202f9f8(Ov000TileTextRenderer *renderer);
extern void func_020115b8(void);
extern void func_0202f9ec(Ov000TileTextRenderer *renderer);
extern void func_0202f818(Ov000FontResource *font);
extern void func_ov000_02056960(Ov000MessageArchive *archive);

extern const char data_ov000_0205a9ec[];
extern const char data_ov000_0205aa00[];
extern const u16 data_02042958[];

void func_ov000_0204d358(int mode) {
    Ov000FontResource font;
    Ov000TileTextRenderer renderer;
    Ov000MessageArchive messages;
    Ov000TextFrame frame;
    Ov000BootContext *context;
    const void *record;

    context = NNSi_FndGetCurrentRootHeap();
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    OS_WaitVBlankIntr();
    GX_SetBankForBG(0x10);
    GX_SetBankForBGExtPltt(0);
    func_020056b4(1, 0, 1);

    *(vu16 *)0x0400000e =
        (*(vu16 *)0x0400000e & 0x43) | 0x204;
    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x600);

    func_ov000_02056938(&messages, data_ov000_0205a9ec);
    func_0202f7fc(&font, data_ov000_0205aa00);
    GX_LoadBGPltt(data_02042958, 0x1a0, 0x20);

    frame.destinationX = 1;
    frame.sourceX = 1;
    frame.destinationY = 0;
    frame.field_0c = 0;
    frame.width = 0x1e;
    frame.height = 0x15;
    frame.sourceY = 0xd;
    frame.paletteCount = 6;

    func_0202f834(&renderer, 3, &font, &frame);
    *(vu16 *)0x04000304 |= 0x8000;
    *(vu32 *)0x04000000 =
        (*(vu32 *)0x04000000 & ~0x1f00) | 0x800;
    func_0202fa20(&renderer, 0);

    if (mode == 0) {
        record = func_ov000_02056970(&messages, 0x17);
        func_0202fa38(&renderer, 0x78, 0x46, 1, 0x10, record);
    } else {
        record = func_ov000_02056970(
            &messages, context->alternateLanguage == 1 ? 0x13 : 0x14);
        func_0202fa38(&renderer, 0x78, 0x3c, 1, 0x10, record);
        record = func_ov000_02056970(&messages, 0x15);
        func_0202fa38(&renderer, 0x78, 0x5a, 1, 0x10, record);
    }

    func_0202f9f8(&renderer);
    func_0201e374(0);
    func_0201e3cc(0);
    OS_WaitVBlankIntr();
    func_020115b8();
    func_0202f9ec(&renderer);
    func_0202f818(&font);
    func_ov000_02056960(&messages);
}
