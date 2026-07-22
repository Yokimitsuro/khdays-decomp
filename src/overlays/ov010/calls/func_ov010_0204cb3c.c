/* Title-screen / 2D-engine setup: bring both engines up from scratch, load the
 * title resources, spawn the menu node and hand back the scene's step function.
 *
 * The back half of this used to sit one callee-saved allocation away from the ROM
 * (mwcc lookahead-held the sub-engine base 0x04001000 and reused it where the ROM
 * recomputes it per block). Eight source forms and 25 compiler builds failed to move
 * it, all of them varying the open-coded register writes. The lever was to stop
 * open-coding them: with each hardware poke behind a `static inline` SDK-style helper
 * (GX_SetVisiblePlaneInline / GXS_SetVisiblePlaneInline / GX_SetDispSelectInline /
 * PriRet) every expansion gets its OWN address local, so the base really is
 * recomputed each time -- which is exactly what the ROM does. The other half of the
 * fix is the palette header: one 4-byte struct copy, not two halfword stores.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 palette[2];
    u16 rect[8];
} InitFrame;

typedef struct {
    u16 colors[2];
} PaletteData;

typedef struct {
    u8 pad_00c[0x0c];
    u8 text_engine[0x0c];
    u8 tile_engine[0x5c];
    void *node;
    u32 state;
    u32 parameter;
} Ov010Context;

#define REG_BG3CNT  (*(volatile u16 *)0x0400000e)
#define REG_POWCNT1 (*(volatile u16 *)0x04000304)

static inline void GX_SetVisiblePlaneInline(int plane) {
    volatile u32 *reg = (volatile u32 *)0x04000000;
    *reg = (*reg & ~0x1f00) | (plane << 8);
}

static inline void GXS_SetVisiblePlaneInline(int plane) {
    volatile u32 *reg = (volatile u32 *)0x04001000;
    *reg = (*reg & ~0x1f00) | (plane << 8);
}

static inline void GX_SetDispSelectInline(int select) {
    REG_POWCNT1 = (u16)((REG_POWCNT1 & ~0x8000) | (select << 15));
}

static inline u16 PriRet(volatile u16 *reg, int p) {
    return (u16)((*reg & ~3) | p);
}

extern Ov010Context *NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable_0x02023650(void);
extern void func_0202362c(int value);
extern void func_0201e1d0(void);
extern void func_02023c30(int value);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dest, int size);
extern void GX_LoadBGPltt(void *src, int offset, int size);
extern void func_ov010_0204cac0(Ov010Context *context, char *name);
extern void *func_ov010_0204cb04(Ov010Context *context, int flag);
extern void func_0202f7fc(void *text_engine, char *name);
extern void func_0202f834(void *tile_engine, int layer, void *text_engine, u16 *rect);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern const PaletteData data_ov010_0204cf88;
extern char data_ov010_0204cfb4[];
extern char data_ov010_0204cfc8[];
extern void func_ov010_0204ce60(void);

void *func_ov010_0204cb3c(u32 parameter) {
    InitFrame frame;
    Ov010Context *context;
    int previous_state;
    u32 bg3cnt;
    void *buffer;

    context = NNSi_FndGetCurrentRootHeap();

    *(PaletteData *)frame.palette = data_ov010_0204cf88;

    previous_state = OS_IsThreadAvailable_0x02023650();
    func_0202362c(0);

    {
        register volatile u16 *palette = (volatile u16 *)0x05000000;
        register volatile u32 *display = (volatile u32 *)0x04000000;

        palette[0] = 0;
        palette[0x200] = 0;

        GX_SetVisiblePlaneInline(0);
        GXS_SetVisiblePlaneInline(0);
    }

    func_0201e1d0();
    func_02023c30(0);

    {
        volatile u32 *display = (volatile u32 *)0x04000000;

        GX_SetDispSelectInline(1);

        display[0] &= 0xc7ffffff;
        display[0] &= 0xf8ffffff;
    }

    GX_SetBankForBG(3);
    GX_SetBankForSubBG(4);
    GX_SetBankForOBJ(0x70);
    GX_SetBankForSubOBJ(8);

    {
        volatile u16 *bg = (volatile u16 *)0x04000008;

        bg[0] = PriRet(&bg[0], 3);
        bg[1] = PriRet(&bg[1], 2);
        bg[2] = PriRet(&bg[2], 1);
        bg[3] = PriRet(&bg[3], 0);
    }

    GX_SetDispSelectInline(1);

    buffer = G2_GetBG3ScrPtr();
    MIi_CpuClearFast(0, buffer, 0x600);

    bg3cnt = REG_BG3CNT & 0x43 | 0x304;
    REG_BG3CNT = (u16)bg3cnt;

    GX_LoadBGPltt(&frame, 0, 4);

    func_ov010_0204cac0(context, data_ov010_0204cfb4);

    if (parameter == 0xffffffff) {
        context->node = func_ov010_0204cb04(context, 1);
    } else {
        context->node = func_ov010_0204cb04(context, 0);
    }

    func_0202f7fc(context->text_engine, data_ov010_0204cfc8);

    frame.rect[0] = 0;
    frame.rect[1] = 0;
    frame.rect[4] = 0;
    frame.rect[6] = 0;
    frame.rect[2] = 0x20;
    frame.rect[3] = 0x18;
    frame.rect[7] = 6;
    frame.rect[5] = 0;

    func_0202f834(context->tile_engine, 3, context->text_engine, frame.rect);

    GX_SetVisiblePlaneInline(8);
    GXS_SetVisiblePlaneInline(8);

    func_0201e374(0);
    func_0201e3cc(0);

    context->state = 2;
    context->parameter = parameter;

    func_0202362c(previous_state);

    return func_ov010_0204ce60;
}
