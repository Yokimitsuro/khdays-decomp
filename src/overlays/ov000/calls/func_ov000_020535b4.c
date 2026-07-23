typedef unsigned char  u8;
typedef unsigned int u32;

typedef struct TileSurfaceCfg {
    u8 unknown_00[0x18];
    void *pVramTarget;
    u32 nUnk1c;
    void *pPixels;
    u32 unknown_24;
} TileSurfaceCfg;

typedef struct Ov000LogoSceneContext {
    u8 pad_0000[0x4af8];
    u8 resourceStorage[8];
    void *resource;
    u8 surface0[0x3c];
    u8 surface1[0x3c];
    u8 surface2[0x3c];
    u8 pad_4bb8[0];
    u8 variantObject[0x0c];
} Ov000LogoSceneContext;

extern const TileSurfaceCfg data_ov000_0205a8d4;
extern const TileSurfaceCfg data_ov000_0205a884;
extern const TileSurfaceCfg data_ov000_0205a8ac;
extern const u8 data_ov000_0205ab38[];
extern Ov000LogoSceneContext *volatile data_ov000_0205ac28;

extern void func_020136b0(void *resource, void *sharedResource);
extern void func_ov000_02056938(void *object, const void *config);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *destination, u32 size);
extern void func_0202ff8c(void *surface, const TileSurfaceCfg *config);
extern void func_ov000_02053ac8(int selector, int argument);

void func_ov000_020535b4(void) {
    TileSurfaceCfg config2 = data_ov000_0205a8d4;
    Ov000LogoSceneContext *context = data_ov000_0205ac28;
    TileSurfaceCfg config1 = data_ov000_0205a884;
    TileSurfaceCfg config0 = data_ov000_0205a8ac;

    func_020136b0(context->resourceStorage, context->resource);
    func_ov000_02056938(data_ov000_0205ac28->variantObject,
                        data_ov000_0205ab38);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x800);

    config2.pPixels = data_ov000_0205ac28->resourceStorage;
    config2.pVramTarget = G2S_GetBG3ScrPtr();
    config1.pPixels = data_ov000_0205ac28->resourceStorage;
    config1.pVramTarget = G2S_GetBG3ScrPtr();
    config0.pPixels = data_ov000_0205ac28->resourceStorage;
    config0.pVramTarget = G2S_GetBG3ScrPtr();

    func_0202ff8c(data_ov000_0205ac28->surface0, &config2);
    func_0202ff8c(data_ov000_0205ac28->surface1, &config1);
    func_0202ff8c(data_ov000_0205ac28->surface2, &config0);

    func_ov000_02053ac8(0, 2);
    func_ov000_02053ac8(1, 2);
    func_ov000_02053ac8(2, 2);
}
