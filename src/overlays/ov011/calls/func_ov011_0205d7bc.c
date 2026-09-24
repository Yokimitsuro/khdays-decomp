/* func_ov011_0205d7bc = Ov011_SetupTitleBackgrounds (676 B, ARM, 25 relocs).
 * Title/movie BG bring-up: allocs two BG tilesets keyed off the scene VRAM base (func_0201ebdc),
 * clears BG0 char (0xffffffff) and BG0 screen (0x00c000c0) on both engines, clears and fills the
 * 32x32 BG1 tilemap at scene+0x23294 with a running u16 counter 0..0x3ff, allocs and registers a
 * palette (func_02024c58), enqueues four GFXi palette commands (0x11/0x21/0x0f/0x1f), clears BG1
 * char/screen on both engines and sets the windows with the SDK's G2 / G2S window inlines (main:
 * WIN0 inside 0x1f + effect, outside 0x33; sub: WIN0 inside 0x3f; both WIN0 at x 0..0x46, y 0..0xc0).
 * The SDK inlines (absolute register macros, `tmp |= 0x20` under `if (effect)`) are what give the
 * ROM's two pool anchors and the unfolded `orr #0x1f; orr #0x20`; the loop counters need `col` at
 * function scope and row / counter / rowBase zeroed in that order. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov011Scene {
    u8    pad_0000[0x0c];
    int   nBgVramBase;                        /* 0x0c */
    void *hRegistered;                        /* 0x10 */
    void *hTileset0;                          /* 0x14 */
    u8    pad_0018[0x10954 - 0x18];
    void *hTileset1;                          /* 0x10954 */
    u8    pad_10958[0x23294 - 0x10958];
    u16   tilemapBg1[0x400];                  /* 0x23294 */
} Ov011Scene;

typedef struct Ov011Globals {
    int         nTimer;
    Ov011Scene *pScene;
} Ov011Globals;


#define reg_G2_WIN0H       (*(volatile u16 *)0x04000040)
#define reg_G2_WIN0V       (*(volatile u16 *)0x04000044)
#define reg_G2_WININ       (*(volatile u16 *)0x04000048)
#define reg_G2_WINOUT      (*(volatile u16 *)0x0400004a)
#define reg_G2S_DB_WIN0H   (*(volatile u16 *)0x04001040)
#define reg_G2S_DB_WIN0V   (*(volatile u16 *)0x04001044)
#define reg_G2S_DB_WININ   (*(volatile u16 *)0x04001048)
#define reg_G2S_DB_WINOUT  (*(volatile u16 *)0x0400104a)

static inline void G2_SetWnd0InsidePlane(int wnd, int effect)
{
    u32 tmp;

    tmp = ((reg_G2_WININ & ~0x3f) | ((u32)wnd << 0));
    if (effect) {
        tmp |= (0x20 << 0);
    }
    reg_G2_WININ = (u16)tmp;
}

static inline void G2_SetWndOutsidePlane(int wnd, int effect)
{
    u32 tmp;

    tmp = ((reg_G2_WINOUT & ~0x3f) | ((u32)wnd << 0));
    if (effect) {
        tmp |= (0x20 << 0);
    }
    reg_G2_WINOUT = (u16)tmp;
}

static inline void G2_SetWnd0Position(int x1, int y1, int x2, int y2)
{
    reg_G2_WIN0H = (u16)(((x1 << 8) & 0xff00) | ((x2 << 0) & 0x00ff));
    reg_G2_WIN0V = (u16)(((y1 << 8) & 0xff00) | ((y2 << 0) & 0x00ff));
}

static inline void G2S_SetWnd0InsidePlane(int wnd, int effect)
{
    u32 tmp;

    tmp = ((reg_G2S_DB_WININ & ~0x3f) | ((u32)wnd << 0));
    if (effect) {
        tmp |= (0x20 << 0);
    }
    reg_G2S_DB_WININ = (u16)tmp;
}

static inline void G2S_SetWndOutsidePlane(int wnd, int effect)
{
    u32 tmp;

    tmp = ((reg_G2S_DB_WINOUT & ~0x3f) | ((u32)wnd << 0));
    if (effect) {
        tmp |= (0x20 << 0);
    }
    reg_G2S_DB_WINOUT = (u16)tmp;
}

static inline void G2S_SetWnd0Position(int x1, int y1, int x2, int y2)
{
    reg_G2S_DB_WIN0H = (u16)(((x1 << 8) & 0xff00) | ((x2 << 0) & 0x00ff));
    reg_G2S_DB_WIN0V = (u16)(((y1 << 8) & 0xff00) | ((y2 << 0) & 0x00ff));
}

extern Ov011Globals data_ov011_0205e960;

extern int   func_0201ebdc(const void *key, int id);
extern int   func_02024c58(void *out, const void *key, int id);
extern void  MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern int   GFXi_EnqueueCommand(int a, int b, int c, int d);
extern void *G2_GetBG0CharPtr(void);
extern void *G2S_GetBG0CharPtr(void);
extern void *G2_GetBG0ScrPtr(void);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2_GetBG1CharPtr(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);

void func_ov011_0205d7bc(void)
{
    int row;
    int col;
    u16 counter;
    int rowBase;
    void *pReg;

    data_ov011_0205e960.pScene->hTileset0 = (void *)func_0201ebdc(
        (const void *)((((u32)(data_ov011_0205e960.pScene->nBgVramBase + 0x8000) & 0x00fffffc) << 7) | 0x80000001),
        0xe);
    data_ov011_0205e960.pScene->hTileset1 = (void *)func_0201ebdc(
        (const void *)((((u32)(data_ov011_0205e960.pScene->nBgVramBase + 0x8000) & 0x00fffffc) << 7) | 0x80000000),
        0xe);

    MIi_CpuClearFast(0xffffffff, (u8 *)G2_GetBG0CharPtr() + 0x3000, 0x40);
    MIi_CpuClearFast(0xffffffff, (u8 *)G2S_GetBG0CharPtr() + 0x3000, 0x40);
    MIi_CpuClearFast(0x00c000c0, G2_GetBG0ScrPtr(), 0x600);
    MIi_CpuClearFast(0x00c000c0, G2S_GetBG0ScrPtr(), 0x600);
    MIi_CpuClearFast(0, data_ov011_0205e960.pScene->tilemapBg1, 0x800);

    row = 0;
    counter = 0;
    rowBase = 0;
    do {
        col = 0;
        do {
            data_ov011_0205e960.pScene->tilemapBg1[rowBase + col] = counter;
            counter++;
            col++;
        } while (col < 0x20);
        row++;
        rowBase += 0x20;
    } while (row < 0x20);

    data_ov011_0205e960.pScene->hRegistered = (void *)func_02024c58(
        &pReg,
        (const void *)((((u32)(data_ov011_0205e960.pScene->nBgVramBase + 0x8000) & 0x00fffffc) << 7) | 0x80000007),
        0xe);
    GFXi_EnqueueCommand(0x11, 0, *(int *)((u8 *)pReg + 0xc), 0x200);
    GFXi_EnqueueCommand(0x21, 0, *(int *)((u8 *)pReg + 0xc), 0x200);
    GFXi_EnqueueCommand(0x0f, 0, *(int *)((u8 *)pReg + 0xc), 0x200);
    GFXi_EnqueueCommand(0x1f, 0, *(int *)((u8 *)pReg + 0xc), 0x200);

    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);

    G2_SetWnd0InsidePlane(0x1f, 1);
    G2_SetWndOutsidePlane(0x33, 0);
    G2_SetWnd0Position(0, 0, 0x46, 0xc0);
    G2S_SetWnd0InsidePlane(0x3f, 0);
    G2S_SetWndOutsidePlane(0x33, 0);
    G2S_SetWnd0Position(0, 0, 0x46, 0xc0);

    return;
}
