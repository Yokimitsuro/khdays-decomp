/* Builds the scene's two tiled graphics surfaces.
 *
 * The 0x28-byte constant template at data_ov000_0205a98c is a TileSurfaceCfg -- the known 40-byte
 * config consumed by the TileSurface_Init* family. func_0202ff8c is TileSurface_InitAndUpload4bpp,
 * so both surfaces are 4bpp and uploaded on init. The template is copied to the stack and patched
 * per surface, which is why the two calls differ only in pVramTarget and nUnk1c.
 *
 * On pVramTarget: at this call site it is an IN-CONTEXT staging buffer (+0x9910, +0xb110), not a
 * VRAM address -- func_ov000_02059d78 later DMAs that region out in seven 0x600 transfers of
 * stride 0x800. The two buffers are 0x1800 apart, so the first surface owns transfer slots 0..2
 * and the second owns 3..6. The field keeps the name the TileSurfaceCfg type already gives it
 * rather than forking a rival name.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 unknown_00[0x18];
    void *pVramTarget; /* +0x18 -- staging buffer at this call site, see header */
    u32 nUnk1c;        /* +0x1c -- the only other per-surface difference */
    void *pPixels;     /* +0x20 */
    u32 unknown_24;
} TileSurfaceCfg;

typedef struct {
    u8 pad_0000[0x88];
    u8 object_0088[0x0c];  /* +0x88  source object; also yields the variant below */
    u8 surface_0094[0x3c]; /* +0x94  a TileSurface -- 0x3c is that type's exact size */
    u8 surface_00d0[0x9588];
    u8 resource_9658[0x2b8];
    u8 buffer_9910[0x1800];
    u8 buffer_b110[0x2004];
    void *variant_d114;
} Ov000SceneContext;

typedef struct {
    u8 pad_0000[0x9660];
    void *resource_9660;
} Ov000SharedContext;

extern const TileSurfaceCfg data_ov000_0205a98c;
extern u8 data_ov000_0205abbc[];
extern Ov000SharedContext *data_ov000_0205ac3c;
extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02056938(void *object, const void *config);
extern void func_020136b0(void *resource, void *shared_resource);
extern void func_0202ff8c(void *surface, const TileSurfaceCfg *config);
extern void *func_ov000_02056970(void *object, int variant);

void func_ov000_0205906c(void) {
    TileSurfaceCfg config = data_ov000_0205a98c;
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();

    func_ov000_02056938(context->object_0088, data_ov000_0205abbc);
    func_020136b0(context->resource_9658,
                  data_ov000_0205ac3c->resource_9660);

    config.pPixels = context->resource_9658;
    config.pVramTarget = context->buffer_9910;
    func_0202ff8c(context->surface_0094, &config);

    config.pVramTarget = context->buffer_b110;
    config.nUnk1c = 20;
    func_0202ff8c(context->surface_00d0, &config);

    context->variant_d114 = func_ov000_02056970(context->object_0088, 0);
}
