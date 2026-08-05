/* TileSurface_BlitGlyph -- draw one glyph onto a tiled surface, tile by tile.
 *
 * Entry [0] of the format dispatch table at data_02041a94, the sibling of
 * TileSurface_Fill (func_02013e10). Text_DrawGlyph (func_02014024) reaches it
 * through owner+0x14 once per character, so this is the first-visible-pixels
 * path on the boot text screen set up by Ov000_SetupBootTextScreen.
 *
 * It clips the glyph's bounding box to the surface in 8x8 tile units, walks the
 * surviving tiles right-to-left and bottom-to-top, and hands each one to
 * func_02013a38 through a stack-resident BlitCtx. The context carries the
 * destination tile, the glyph bitmap, the pixel offsets inside the tile, the
 * glyph size, the font's row stride and cell height, the surface depth, and the
 * caller's last-row index.
 *
 * CODEGEN NOTE -- four shapes are load-bearing and each was measured:
 *  - `g` is a plain local copy of the last parameter used BOTH for the metrics
 *    read and the bitmap read. mwcc spills it into that parameter's own home
 *    slot and reloads it later; a `volatile` parameter written back models the
 *    same two instructions but schedules the store to the end of its basic
 *    block instead of right after the definition, which is where the ROM has it.
 *  - `rowAdvance` is a plain int. It only reaches memory because the register
 *    pressure here forces a spill; marking it `volatile` reloads it per use and
 *    costs eight bytes.
 *  - The four clip values deliberately REUSE locals whose previous value has
 *    just died, which is what colours the registers the ROM's way:
 *    `tilesX` holds the horizontal tile count and later the row end, `boundW`
 *    holds the surface width limit and later the vertical tile count, `spanX`
 *    holds the horizontal span, and `boundH` holds the surface height limit and
 *    later the vertical span. Giving any of them a private local shifts the
 *    allocation and costs between one and forty-seven instructions.
 *  - The column end `xEnd` is the one value that must NOT share a local with the
 *    span it derives from; that separation is what moves bytesPerTile into r8.
 */

extern void func_02013a38(void *ctx);

typedef struct TileSurface {
    void *pixels;
    int widthTiles;
    int heightTiles;
    unsigned char bpp;
    unsigned char pad0d[3];
    int stride;
    void *ops;
} TileSurface;

typedef struct FontMetrics {
    unsigned char cellW;
    unsigned char width;
    unsigned char pad02[4];
    unsigned char cellH;
} FontMetrics;

typedef struct FontInfo {
    int unk00;
    int unk04;
    FontMetrics *metrics;
} FontInfo;

typedef struct GlyphDraw {
    unsigned char *metrics;
    int bitmap;
} GlyphDraw;

typedef struct BlitCtx {
    void *dst;
    int bitmap;
    int x;
    int y;
    int glyphW;
    int glyphH;
    int rowBytes;
    int cellH;
    int bpp;
    int lastRow;
} BlitCtx;

void func_02013c78(TileSurface *surf, FontInfo **font, int x, int y, int lastRow, GlyphDraw *gd) {
    BlitCtx ctx;
    GlyphDraw *g;
    int glyphW;
    int bytesPerTile;
    int boundW, boundH;
    int cellH;
    int stride;
    int glyphH;
    char *pix;
    int cx;
    int xEnd;
    int tx0, ty0, spanX, tilesX;
    int rowAdvance;
    char *dst;

    bytesPerTile = surf->bpp * 64 / 8;
    boundW = surf->widthTiles;
    boundH = surf->heightTiles;
    pix = (char *)surf->pixels;
    g = gd;
    glyphW = g->metrics[1];
    glyphH = font[0]->metrics->width;
    if (glyphW == 0) {
        return;
    }
    if (x + glyphW < 0) {
        return;
    }
    if (y + glyphH < 0) {
        return;
    }
    tx0 = (x <= 0) ? 0 : ((unsigned int)x >> 3);
    ty0 = (y <= 0) ? 0 : ((unsigned int)y >> 3);
    tilesX = (unsigned int)(x + glyphW + 7) >> 3;
    if ((unsigned int)boundW <= (unsigned int)tilesX) {
        tilesX = boundW;
    }
    boundW = (unsigned int)(y + glyphH + 7) >> 3;   /* boundW now holds tilesY */
    if ((unsigned int)boundH <= (unsigned int)boundW) {
        boundW = boundH;
    }
    spanX = tilesX - tx0;
    boundH = boundW - ty0;                          /* boundH now holds spanY */
    if (spanX < 0) {
        return;
    }
    if (boundH < 0) {
        return;
    }
    if (x >= 0) {
        x = x & 7;
    }
    stride = surf->stride;
    rowAdvance = bytesPerTile * (stride - spanX);
    dst = pix + bytesPerTile * (stride * ty0 + tx0);
    if (y >= 0) {
        y = y & 7;
    }
    ctx.bitmap = g->bitmap;
    ctx.glyphW = glyphW;
    ctx.lastRow = lastRow - 1;
    ctx.glyphH = glyphH;
    cellH = font[0]->metrics->cellH;
    tilesX = y - boundH * 8;                        /* tilesX now holds the row end */
    xEnd = x - spanX * 8;
    ctx.cellH = cellH;
    ctx.bpp = surf->bpp;
    ctx.rowBytes = (short)cellH * (short)font[0]->metrics->cellW;
    if (y <= tilesX) {
        return;
    }
    do {
        ctx.y = y;
        cx = x;
        while (cx > xEnd) {
            ctx.dst = dst;
            ctx.x = cx;
            func_02013a38(&ctx);
            cx -= 8;
            dst += bytesPerTile;
        }
        y -= 8;
        dst += rowAdvance;
    } while (y > tilesX);
}
