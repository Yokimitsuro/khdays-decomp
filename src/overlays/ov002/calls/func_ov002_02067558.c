/*
 * Ov002_BuildHudSurfaces - build the tutorial page's three tiled surfaces.
 *
 * Each surface starts from its own const template; all three share the VRAM
 * target and the pixel buffer that slot 0x1a hands out, so the page draws into
 * one allocation. They are uploaded in screen order: the title strip, the body
 * and the footer.
 *
 * THUMB.
 */

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

extern int *data_ov002_0207f9fc;
extern const TileSurfaceCfg data_ov002_0207e548;
extern const TileSurfaceCfg data_ov002_0207e598;
extern const TileSurfaceCfg data_ov002_0207e5c0;

extern int func_ov002_02053bb8(int nSlot);
extern void *func_ov002_0205740c(void);
extern void func_0202ff8c(void *pSurface, const TileSurfaceCfg *pCfg);

void func_ov002_02067558(void)
{
    TileSurfaceCfg cfgTitle;
    TileSurfaceCfg cfgBody;
    TileSurfaceCfg cfgFoot;
    int hud;
    int nVram;
    void *pPixels;

    hud = (int)data_ov002_0207f9fc;
    cfgTitle = data_ov002_0207e598;
    cfgBody = data_ov002_0207e5c0;
    cfgFoot = data_ov002_0207e548;
    nVram = func_ov002_02053bb8(0x1a);
    cfgFoot.nVramTarget = nVram;
    cfgBody.nVramTarget = nVram;
    cfgTitle.nVramTarget = nVram;
    pPixels = func_ov002_0205740c();
    cfgFoot.pPixels = pPixels;
    cfgBody.pPixels = pPixels;
    cfgTitle.pPixels = pPixels;
    func_0202ff8c((void *)(hud + 0x34), &cfgTitle);
    func_0202ff8c((void *)(hud + 0x70), &cfgBody);
    func_0202ff8c((void *)(hud + 0xac), &cfgFoot);
}
