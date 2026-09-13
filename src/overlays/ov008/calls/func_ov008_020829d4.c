/* func_ov008_020829d4 -- Ov008_InitShopSurfaces: bind the shop panel's three
 * fonts (+0xc13c: font_eu_10, +0xc148: font_eu_08, +0xc154), create its four
 * 4bpp tile surfaces (+0xc160 32 x 24 with the +0x12a8 buffer, +0xc19c 22 x
 * 2 at (10, 0), +0xc1d8 22 x 6 at (10, 18) and +0xc214 24 x 16 at (4, 2)
 * with the +0xa8 buffer), raise bits 0 / 3 of the word at +0x2aac, point the
 * text loader (+0xc130) at "UI/shop/shp_&.s.z" and cache variable records
 * 0x1a, 0x1b, 0x1c, 0x1e and 0x1d at +0xc5c8.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008PanelContext {
    u8   pad_0000[0xa8];
    u8   pixelsA[0x12a8 - 0xa8];      /* 0x00a8 */
    u8   pixelsB[0x2aac - 0x12a8];    /* 0x12a8 */
    u32  nFlags;                      /* 0x2aac */
    u8   pad_2ab0[0xc130 - 0x2ab0];
    u8   textLoader[0xc];             /* 0xc130 */
    u8   fontA[0xc];                  /* 0xc13c */
    u8   fontB[0xc];                  /* 0xc148 */
    u8   fontC[0xc];                  /* 0xc154 */
    u8   textSurface[0x3c];           /* 0xc160 */
    u8   surfaceB[0x3c];              /* 0xc19c */
    u8   surfaceC[0x3c];              /* 0xc1d8 */
    u8   surfaceD[0x3c];              /* 0xc214 */
    u8   pad_c250[0xc5c8 - 0xc250];
    void *apVarText[5];               /* 0xc5c8 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern const char data_ov008_02090e44[];                                  /* "text/font_eu_10.nftr" */
extern const char data_ov008_02090e5c[];                                  /* "text/font_eu_08.nftr" */
extern const char data_ov008_02090e74[];
extern const char data_ov008_02090e8c[];                                  /* "UI/shop/shp_&.s.z" */
extern void  func_0202ff58(void *pFont, const char *pName);               /* Resource_BindByName */
extern void  func_ov008_02082978(void *pSurface, int nX, int nY, int nWidth, int nHeight, int nRows, void *pVram, int nUnk1c, void *pPixels); /* Ov008_UploadTileSurface */
extern void  func_ov008_02055c4c(void *pLoader, const char *pPath);       /* Ov008_Set_5c4c */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);             /* GetVarRecordByIndex */

void func_ov008_020829d4(void)
{
    Ov008PanelContext *ctx;
    void **apText;

    ctx = data_ov008_02090fac;
    apText = ctx->apVarText;
    func_0202ff58(ctx->fontA, data_ov008_02090e44);
    func_0202ff58(ctx->fontB, data_ov008_02090e5c);
    func_0202ff58(ctx->fontC, data_ov008_02090e74);
    func_ov008_02082978(ctx->textSurface, 0, 0, 0x20, 0x18, 0, ctx->pixelsB, 0x14, ctx->fontA);
    func_ov008_02082978(ctx->surfaceB, 10, 0, 0x16, 2, 0xc0, ctx->pixelsA, 5, ctx->fontA);
    func_ov008_02082978(ctx->surfaceC, 10, 0x12, 0x16, 6, 0x118, ctx->pixelsA, 5, ctx->fontA);
    func_ov008_02082978(ctx->surfaceD, 4, 2, 0x18, 0x10, 0x220, ctx->pixelsA, 5, ctx->fontA);
    ctx->nFlags |= 9;
    func_ov008_02055c4c(ctx->textLoader, data_ov008_02090e8c);
    apText[0] = func_ov008_02055c84(ctx->textLoader, 0x1a);
    apText[1] = func_ov008_02055c84(ctx->textLoader, 0x1b);
    apText[2] = func_ov008_02055c84(ctx->textLoader, 0x1c);
    apText[3] = func_ov008_02055c84(ctx->textLoader, 0x1e);
    apText[4] = func_ov008_02055c84(ctx->textLoader, 0x1d);
}
