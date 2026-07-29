typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TileSurfaceCfg {
    u32 field00;
    u32 field04;
    u32 widthTiles;
    u32 heightTiles;
    u32 rowTiles;
    u32 paletteIndex;
    int vramTarget;
    u32 field1c;
    void *pixels;
    u32 field24;
} TileSurfaceCfg;

typedef struct Ov009SaveContext {
    u8 pad000[0x15c];
    u8 varRecords[0x0c];
    u8 surface168[0x3c];
    u8 surface1a4[0x3c];
    u8 surface1e0[1];
} Ov009SaveContext;

extern const TileSurfaceCfg data_ov009_02056058;
extern const TileSurfaceCfg data_ov009_02056080;
extern const TileSurfaceCfg data_ov009_02056030;

extern void *func_ov009_0204e59c(void);
extern int func_ov009_0204e450(int slot);
extern void func_0202ff8c(void *surface, const TileSurfaceCfg *config);
extern u16 *func_ov009_02052788(void *records, int index);
extern void func_ov009_02053308(
    void *surface,
    int x,
    int y,
    int style,
    const u16 *text,
    int shadow
);
extern void func_ov009_02053398(
    void *surface,
    int x,
    int y,
    int style,
    const u16 *text
);
extern void func_020300f8(void *surface);
extern void func_ov009_0204e3f4(int slot);

void func_ov009_02053404(Ov009SaveContext *ctx)
{
    TileSurfaceCfg config168 = data_ov009_02056058;
    TileSurfaceCfg config1e0 = data_ov009_02056080;
    TileSurfaceCfg config1a4 = data_ov009_02056030;
    const u16 *text;

    config168.pixels = func_ov009_0204e59c();
    config168.vramTarget = func_ov009_0204e450(9);
    config1a4.pixels = func_ov009_0204e59c();
    config1a4.vramTarget = func_ov009_0204e450(9);
    config1e0.pixels = func_ov009_0204e59c();
    config1e0.vramTarget = func_ov009_0204e450(9);

    func_0202ff8c(ctx->surface168, &config168);
    func_0202ff8c(ctx->surface1a4, &config1a4);
    func_0202ff8c(ctx->surface1e0, &config1e0);

    text = func_ov009_02052788(ctx->varRecords, 0);
    func_ov009_02053308(ctx->surface168, 0x8e, 2, 2, text, 1);

    text = func_ov009_02052788(ctx->varRecords, 1);
    func_ov009_02053398(ctx->surface1a4, 0x62, 0, 2, text);

    func_020300f8(ctx->surface1a4);
    func_020300f8(ctx->surface168);
    func_020300f8(ctx->surface1e0);
    func_ov009_0204e3f4(9);
}
