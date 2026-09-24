#pragma thumb on
/* func_02022af4 -- pause menu opening step, MAIN (THUMB). Without data_0204bd85 or game field 0x20ef
 * it pushes step 0 and stops; while the opening delay (+0xcc) runs it counts down. Otherwise it sets
 * the menu BG (BG3, or BG2 in mode bit 1) to text 256x256 at screen base 0xf800 / char base 0xc000
 * and clears its screen, redraws the panels (unless game field 0x2483 is set), loads the menu screen
 * (func_02013408 with the resources at +0xa0/+0xa4/+0xa8), shows BG0 with the menu BG, darkens
 * both screens by 8 (the sub screen to the overlay's darker level in mode 0x2a), pauses the channels
 * outside the mode-bit-1 case of data_0204c240 bit 2, plays sound 2 and queues "pause_refresh". */
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef struct {
    int debounce;                       /* +0x00 */
    int selected;                       /* +0x04 */
} PanelSlot;

typedef struct {
    char pad0000[0xc];
    char panel[0x94];                   /* +0x0c -- opaque, passed to func_02023400 */
    void *screenData;                   /* +0xa0 */
    void *charData;                     /* +0xa4 */
    void *plttData;                     /* +0xa8 */
    PanelSlot slots[3];                 /* +0xac */
    int field_c4;
    int timer;                          /* +0xc8 */
    int openDelay;                      /* +0xcc */
    int count;                          /* +0xd0 */
} PauseContext;

typedef struct {
    char pad0000[4];
    PauseContext *pCtx;                 /* +0x04 */
} Root0204be08;

extern Root0204be08 data_0204be08;
extern unsigned char data_0204bd85;
extern unsigned char data_0204c240;
extern char data_02042748[];            /* "pause_refresh" */

extern int func_02023588(int flag);                 /* GameState_IsFlagSet */
extern void func_020208d0(unsigned char step);
extern int func_02020a9c(void);
extern void *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void func_02023204(void);
extern void func_02023400(void *panel, int index, int state);
extern void func_02013408(int bg, const void *pScreenData, const void *pCharacterData, const void *pPaletteData,
                          const void *pPositionInfo, const void *pCompressInfo, int screenBase, int characterBase);
extern void G2x_SetBlendBrightness_(vu16 *reg, int plane, int brightness);
extern int func_ov106_020b8208(void);
extern void SNDi_BroadcastChannelOp(int op);
extern void func_02033b78(int a, int b);            /* play menu sound */
extern void func_02000fb4(int mode, const void *descriptor);

#define reg_GX_DISPCNT      (*(vu32 *)0x04000000)
#define reg_G2_BG2CNT       (*(vu16 *)0x0400000c)
#define reg_G2_BG3CNT       (*(vu16 *)0x0400000e)
#define reg_G2_BLDCNT       (*(vu16 *)0x04000050)
#define reg_GXS_DB_DISPCNT  (*(vu32 *)0x04001000)
#define reg_G2S_DB_BLDCNT   (*(vu16 *)0x04001050)

static inline void G2_SetBG2Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2_BG2CNT = (u16)((reg_G2_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7) |
                          (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2_SetBG3Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2_BG3CNT = (u16)((reg_G2_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) |
                          (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline int GXS_GetVisiblePlane(void)
{
    return (int)((reg_GXS_DB_DISPCNT & 0x1f00) >> 8);
}

static inline void G2_SetBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_(&reg_G2_BLDCNT, plane, brightness);
}

static inline void G2S_SetBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_(&reg_G2S_DB_BLDCNT, plane, brightness);
}

void func_02022af4(void)
{
    PauseContext *ctx = data_0204be08.pCtx;
    int i;

    if (data_0204bd85 == 0 && func_02023588(0x20ef) == 0) {
        func_020208d0(0);
        return;
    }
    if (ctx->openDelay == 0) {
        if (!(func_02020a9c() & 2)) {
            G2_SetBG3Control(0, 0, 0x1f, 3, 0);
            MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
        } else {
            G2_SetBG2Control(0, 0, 0x1f, 3, 0);
            MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
        }
        func_02023204();
        if (func_02023588(0x2483) == 0) {
            for (i = 0; i < ctx->count; i++) {
                func_02023400(ctx->panel, i, ctx->slots[i].selected);
            }
        }
        func_02013408(3, ctx->screenData, ctx->charData, ctx->plttData, 0, 0, 0x1f, 3);
        if (!(func_02020a9c() & 2)) {
            GX_SetVisiblePlane(9);
        } else {
            GX_SetVisiblePlane(5);
        }
        G2_SetBlendBrightness(1, -8);
        G2S_SetBlendBrightness(GXS_GetVisiblePlane(), -8);
        if (func_02020a9c() == 0x2a && func_ov106_020b8208() < -8) {
            G2S_SetBlendBrightness(1, func_ov106_020b8208());
        }
        if (!(data_0204c240 & 4) || !(func_02020a9c() & 2)) {
            SNDi_BroadcastChannelOp(1);
        }
        func_02033b78(0, 2);
        func_02000fb4(1, data_02042748);
    } else {
        ctx->openDelay--;
    }
}
#pragma thumb off
