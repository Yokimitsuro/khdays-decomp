/*
 * TileSurface_Init - initialise a 0x3c-byte TileSurface from a TileSurfaceCfg.
 *
 * bpp is 0x40 (8bpp) or 0x20 (4bpp) per bIs8bpp, giving nRowBytes = bpp*rowTiles and
 * nTotalBytes = bpp*widthTiles*heightTiles. Clears the surface, inits its embedded list,
 * copies pixel pointer and dimensions, sets the 8bpp flag, finishes the header via
 * func_0202fff8 (pCurrentData = pCurrent + 8, pCursor = pPixels), then when bUpload is set
 * uploads through func_02014174 with the palette index defaulting to 15 when negative.
 *
 * THUMB. nRowBytes written rowTiles*bpp so bpp stays in r0 across both multiplies; the
 * pCurrent/pPixels reads are grouped so mwcc schedules the two loads together like the ROM.
 */
typedef struct {
    void *pPixels;
    int nWidthTiles;
    int nHeightTiles;
    int nTotalBytes;
    int nRowBytes;
    int nUnk14;
    void *pCurrent;
    void *pCurrentData;
    void *pCursor;
    int nUnk24;
    int nUnk28;
    int nUnk2c;
    int nUnk30;
    int nUnk34;
    unsigned int dwIs8bpp;
} TileSurface;

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

extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);
extern void NNS_FndInitList(void *list, unsigned short offset);
extern void func_0202fff8(TileSurface *s, int a);
extern void func_02014174(int vram, int w, int h, int u04, int u00, int u24,
                          int rowTiles, int pal);

void func_0202fec8(TileSurface *s, TileSurfaceCfg *cfg, int bUpload, unsigned int bIs8bpp)
{
    int bpp;

    MI_CpuFill8(s, 0, 0x3c);
    NNS_FndInitList(&s->nUnk2c, 0);
    bpp = bIs8bpp != 0 ? 0x40 : 0x20;
    s->nRowBytes = cfg->nRowTiles * bpp;
    s->pPixels = cfg->pPixels;
    s->nTotalBytes = bpp * (cfg->nWidthTiles * cfg->nHeightTiles);
    s->nUnk14 = cfg->nUnk1c;
    s->nWidthTiles = cfg->nWidthTiles;
    s->nHeightTiles = cfg->nHeightTiles;
    s->dwIs8bpp = bIs8bpp;
    func_0202fff8(s, 1);
    {
        void *pc = s->pCurrent;
        void *pp = s->pPixels;
        s->pCurrentData = (char *)pc + 8;
        s->pCursor = pp;
    }
    s->nUnk24 = 0;
    s->nUnk28 = 0;
    if (bUpload != 0) {
        int pal = cfg->nPaletteIndex;
        if (pal < 0)
            pal = 0xf;
        func_02014174(cfg->nVramTarget, cfg->nWidthTiles, cfg->nHeightTiles, cfg->nUnk04,
                      cfg->nUnk00, cfg->nUnk24, cfg->nRowTiles, pal);
    }
}
