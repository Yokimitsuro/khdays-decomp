/* Builds a 4bpp TileSurface config from the caller's parameters and uploads it. */

typedef struct {
    int nUnk00;
    int nUnk04;
    int nWidthTiles;
    int nHeightTiles;
    int nRowTiles;
    int nPaletteIndex;
    int nVramTarget;
    int nUnk1c;
    void *pPixels;
    int nUnk24;
} TileSurfaceCfg;

extern void func_0202ff8c(void *surface, const TileSurfaceCfg *cfg);

void func_ov008_02082978(int surface, int a, int b, int width, int height,
                         int rows, int vram, int unk1c, void *pixels) {
    TileSurfaceCfg cfg;

    cfg.nUnk00 = b;
    cfg.nUnk04 = a;
    cfg.nWidthTiles = width;
    cfg.nHeightTiles = height;
    cfg.nRowTiles = rows;
    cfg.nPaletteIndex = 0xf;
    cfg.nVramTarget = vram;
    cfg.nUnk1c = unk1c;
    cfg.pPixels = pixels;
    cfg.nUnk24 = 0x20;
    func_0202ff8c((void *)surface, &cfg);
}
