/* Teardown for the scene func_ov002_02062bd8 starts, and it CONFIRMS that
 * function's layout from the other end: +0x74 is released with
 * func_ov002_02053904 (the step object registered there), +0x78/+0x7c with
 * func_02024fd4 (paired with the func_02024ee8 that allocated them), and +0x1b4
 * with func_ov002_02052834 (paired with func_ov002_0205280c).  Nothing here was
 * guessed from a neighbouring offset.
 *
 * Four tiled surfaces are released, each behind its own in-use flag, and the
 * flags are NOT adjacent to their surfaces: +0x4c guards the surface at +0x10
 * (0x10 + 0x3c, i.e. the word just past it), while +0x8c/+0x90/+0x94 are a
 * three-flag array guarding the three contiguous 0x3c-stride surfaces at
 * +0xc0/+0xfc/+0x138.  The 0x3c stride is what identifies them as TileSurface.
 *
 * Finally it clears bits 13-15 of the SUB engine's DISPCNT (0x04001000) -- Win0,
 * Win1 and OBJWin -- and nulls the context slot the scene was published in. */
typedef struct {
    char pad00[0x3c];
} TileSurface;

typedef struct {
    void *pObjectA;             /* +0x000 */
    void *pObjectB;             /* +0x004 */
    char pad08[8];
    TileSurface surface10;      /* +0x010 */
    int bSurface10Used;         /* +0x04c */
    char pad50[0x24];
    void *pStepObject;          /* +0x074 */
    void *pAnimA;               /* +0x078 */
    void *pAnimB;               /* +0x07c */
    char pad80[0xc];
    int aSurfaceUsed[3];        /* +0x08c */
    char pad98[0x1c];
    void *pBufferB4;            /* +0x0b4 */
    void *pBufferB8;            /* +0x0b8 */
    char padbc[4];
    TileSurface aSurfaces[3];   /* +0x0c0 */
    char pad174[0x40];
    int aSubCtx[1];             /* +0x1b4 */
} Ov002SceneContext;

extern void func_0200c5fc(void);
extern void func_0200ca50(int a);
extern void func_0200ca68(int a);
extern void func_ov002_02053904(void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_0202ffbc(TileSurface *s);
extern void func_ov002_02052834(int *p);
extern void WM_EndKeySharing_0x02023ad0(void *obj);
extern void func_02024fd4(void *p);

extern char *data_ov002_0207f62c;

void func_ov002_02062cb0(void) {
    Ov002SceneContext *ctx = (Ov002SceneContext *)(&data_ov002_0207f62c)[1];

    func_0200c5fc();
    func_0200ca50(4);
    func_0200ca68(4);
    func_ov002_02053904(ctx->pStepObject);
    if (ctx->pBufferB4 != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pBufferB4);
    }
    if (ctx->pBufferB8 != 0) {
        NNSi_FndFreeFromDefaultHeap(ctx->pBufferB8);
    }
    if (ctx->bSurface10Used != 0) {
        func_0202ffbc(&ctx->surface10);
    }
    if (ctx->aSurfaceUsed[0] != 0) {
        func_0202ffbc(&ctx->aSurfaces[0]);
    }
    if (ctx->aSurfaceUsed[1] != 0) {
        func_0202ffbc(&ctx->aSurfaces[1]);
    }
    if (ctx->aSurfaceUsed[2] != 0) {
        func_0202ffbc(&ctx->aSurfaces[2]);
    }
    func_ov002_02052834(ctx->aSubCtx);
    WM_EndKeySharing_0x02023ad0(ctx->pObjectA);
    if (ctx->pObjectB != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->pObjectB);
    }
    func_02024fd4(ctx->pAnimB);
    func_02024fd4(ctx->pAnimA);
    *(unsigned int *)0x04001000 = 0xffff1fff & *(unsigned int *)0x04001000;
    (&data_ov002_0207f62c)[1] = 0;
}
