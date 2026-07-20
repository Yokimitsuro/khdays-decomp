/* Builds and uploads the HUD's 5-tile row: init each 4bpp surface from its config, lay them out,
 * then flush + DMA each into BG1 character VRAM and release its scratch buffers.
 *
 * The five configs live in the const array data_ov002_0207ea14 (stride 0x28); each is pointed at
 * the shared pixel source before TileSurface_Init4bpp. func_ov002_0205b39c positions the row. The
 * second pass flushes the built tile data (surface->pCurrent[0x20]) and loads it into BG1 char
 * memory, then frees the per-surface sub-buffers.
 */

typedef unsigned char u8;

typedef struct {
    u8 pad_0000[0x20];
    void *pPixels; /* +0x20 */
    u8 pad_0024[4];
} TileSurfaceCfg;

typedef struct {
    u8 pad_0000[0x0c];
    int nLen;      /* +0x0c */
    int nDstOfs;   /* +0x10 */
    u8 pad_0014[4];
    int *pCurrent; /* +0x18 */
    u8 pad_001c[0x20];
} TileSurface;

extern void *func_ov002_020573f8(void);
extern void func_0202ffa4(TileSurface *surface, TileSurfaceCfg *cfg);
extern void func_ov002_0205b39c(TileSurface *surfaces);
extern void DC_FlushRange(void *addr, int len);
extern void GX_LoadBG1Char(void *src, int offset, int len);
extern void func_0202ffbc(TileSurface *surface);
extern TileSurfaceCfg data_ov002_0207ea14[];

void func_ov002_0205b5e4(void) {
    TileSurface surfaces[5];
    void *pixels = func_ov002_020573f8();
    TileSurfaceCfg *cfg = data_ov002_0207ea14;
    int i = 0;
    TileSurface *s = surfaces;

    for (; i < 5; i++) {
        cfg->pPixels = pixels;
        func_0202ffa4(s, cfg);
        cfg++;
        s++;
    }

    func_ov002_0205b39c(surfaces);

    i = 0;
    {
        TileSurface *t = surfaces;
        for (; i < 5; i++) {
            DC_FlushRange((void *)t->pCurrent[8], t->nLen);
            GX_LoadBG1Char((void *)t->pCurrent[8], t->nDstOfs, t->nLen);
            func_0202ffbc(t);
            t++;
        }
    }
}
