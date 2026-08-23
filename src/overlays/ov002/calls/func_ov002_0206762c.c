/*
 * Ov002_BuildHudRecordSurfaces - build the page's remaining record surfaces.
 *
 * The first three surfaces are built first, then the three that hold records
 * one to three are laid out from their own templates. All of them share the
 * VRAM target and pixel buffer of slot 0x1a, which is claimed once the configs
 * are filled in. The four surfaces from +0xd4 on are marked present.
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
extern const TileSurfaceCfg data_ov002_0207e4f8;
extern const TileSurfaceCfg data_ov002_0207e570;
extern const TileSurfaceCfg data_ov002_0207e5e8;

extern void func_ov002_02067558(void);
extern int func_ov002_02053bb8(int nSlot);
extern void *func_ov002_0205740c(void);
extern void func_ov002_02053cd4(int nSlot);
extern void func_0202ff8c(void *pSurface, const TileSurfaceCfg *pCfg);

void func_ov002_0206762c(void)
{
    TileSurfaceCfg cfgRec1;
    TileSurfaceCfg cfgRec2;
    TileSurfaceCfg cfgRec3;
    int hud;
    int nVram;
    void *pPixels;
    int i;

    hud = (int)data_ov002_0207f9fc;
    cfgRec1 = data_ov002_0207e570;
    cfgRec2 = data_ov002_0207e5e8;
    cfgRec3 = data_ov002_0207e4f8;
    func_ov002_02067558();
    nVram = func_ov002_02053bb8(0x1a);
    cfgRec3.nVramTarget = nVram;
    cfgRec2.nVramTarget = nVram;
    cfgRec1.nVramTarget = nVram;
    pPixels = func_ov002_0205740c();
    cfgRec3.pPixels = pPixels;
    cfgRec2.pPixels = pPixels;
    cfgRec1.pPixels = pPixels;
    func_ov002_02053cd4(0x1a);
    func_0202ff8c((void *)(hud + 0xe8), &cfgRec1);
    func_0202ff8c((void *)(hud + 0x124), &cfgRec2);
    func_0202ff8c((void *)(hud + 0x160), &cfgRec3);
    for (i = 0; i < 4; i++) {
        *(int *)(hud + 0xd4) = 1;
        hud += 0x3c;
    }
}
