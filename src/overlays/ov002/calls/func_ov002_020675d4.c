/* Rebuild one of the HUD's tiled surfaces from a const config template.
 *
 * Copies the 40-byte TileSurfaceCfg template, patches its VRAM target and pixel source (allocated
 * for slot 0x1a), uploads it as a 4bpp TileSurface at base+0xe8, and raises the "present" flag on
 * the two contiguous surfaces (base+0xd4, stride 0x3c). base is the HUD object held at
 * data_ov002_0207f9fc.
 */

typedef unsigned char u8;

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

extern const TileSurfaceCfg data_ov002_0207e520;
extern int *data_ov002_0207f9fc;
extern void func_ov002_02067558(void);
extern int func_ov002_02053bb8(int slot);
extern void *func_ov002_0205740c(void);
extern void func_ov002_02053cd4(int slot);
extern void func_0202ff8c(void *surface, const TileSurfaceCfg *cfg);

void func_ov002_020675d4(void) {
    int base = (int)data_ov002_0207f9fc;
    TileSurfaceCfg cfg = data_ov002_0207e520;
    int i;

    func_ov002_02067558();
    cfg.nVramTarget = func_ov002_02053bb8(0x1a);
    cfg.pPixels = func_ov002_0205740c();
    func_ov002_02053cd4(0x1a);
    func_0202ff8c((void *)(base + 0xe8), &cfg);

    for (i = 0; i < 2; i++) {
        *(int *)(base + 0xd4) = 1;
        base += 0x3c;
    }
}
