/* Build one text item from the const TileSurfaceCfg template at
 * data_ov002_0207dbe8: patch in the VRAM target handle for id 9 and point the
 * surface at the context's +0x24 pixel block, mark the context dirty at +0x4c,
 * then initialise the 4bpp surface at +0xbc (func_0202ffa4 = TileSurface_Init
 * with upload off and 4bpp), draw the string looked up at index 8, and release
 * the lookup. The template is 40 bytes, which is exactly sizeof(TileSurfaceCfg). */
/* TileSurfaceCfg -- spelled out locally because delinking rules out shared headers. */
typedef struct {
    int nUnk00;
    int nUnk04;
    int nWidthTiles;
    int nHeightTiles;
    int nRowTiles;
    int nPaletteIndex;
    int nVramTarget;   /* +0x18 */
    int nUnk1c;
    void *pPixels;     /* +0x20 */
    int nUnk24;
} TileSurfaceCfg;

typedef struct {
    int w0;
    int w4;
    int w8;
} Ov002StringRef;

extern int data_ov002_0207f614;
extern const TileSurfaceCfg data_ov002_0207dbe8;
extern int data_ov002_0207e908;

extern void func_ov002_0205280c(void *ref, void *src);
extern int func_ov002_02053bb8(int id);
extern int func_0202ffa4(void *widget, void *cfg);
extern void *func_ov002_02052844(void *ref, int idx);
extern void func_02030278(void *widget, int a, int b, int c, void *text, int d);
extern void func_020300f8(void *widget);
extern void func_ov002_02052834(void *ref);

void func_ov002_02055b24(void) {
    TileSurfaceCfg cfg;
    Ov002StringRef ref;
    char *ctx = (char *)*(int *)&data_ov002_0207f614;

    cfg = data_ov002_0207dbe8;
    func_ov002_0205280c(&ref, &data_ov002_0207e908);
    cfg.nVramTarget = func_ov002_02053bb8(9);
    cfg.pPixels = ctx + 0x24;
    *(int *)(ctx + 0x4c) = 1;
    func_0202ffa4(ctx + 0xbc, &cfg);
    func_02030278(ctx + 0xbc, 2, 3, 2, func_ov002_02052844(&ref, 8), 1);
    func_020300f8(ctx + 0xbc);
    func_ov002_02052834(&ref);
}
