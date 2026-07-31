/*
 * Ov008_MainMenu_SetupTextSurfaces - build the three menu text tile-surfaces and draw the
 * heading and counter text, called from Ov008_MainMenu_StateTick (state 1).
 *
 * Copies three TileSurfaceCfg templates (data_ov008_0208ee5c/0208ee0c/0208ee34), patches all
 * three to share the tile pixel buffer (Ov008_GetCtxBlock968c) and VRAM target
 * (Ov008_ResetEntry(9)), configures the shared surface slot at obj+0x14f4, then inits and
 * uploads each 4bpp tile surface (obj+0x1420/0x145c/0x1498). Draws the directional heading
 * text into surface 0 when the menu is idle or the session is ready; measures and draws the
 * subtitle into surface 1 (variant 4, or 0 once GameState field 9 reaches 0x165); and, in
 * multiplayer mode with a context object, draws the lowest mission-id record into surface 2.
 *
 * Arity notes: func_ov008_02055c4c (surface setup) takes 2 args - the trailing r2/r3 Ghidra
 * shows are left over from the 4-word template ldm. func_020301c8 (directional text) takes 6
 * args (2 on the stack: 0x821 then data_ov008_02090344); Ghidra's 7th is an uninitialised-stack
 * phantom. Local declaration order places the three configs high-to-low so the ldm/stm copies
 * land at the ROM's sp offsets.
 */

typedef unsigned int u32;

typedef struct {
    u32 nUnk00, nUnk04, nWidthTiles, nHeightTiles, nRowTiles, nPaletteIndex;
    u32 nVramTarget;
    u32 nUnk1c;
    void *pPixels;
    u32 nUnk24;
} TileSurfaceCfg;

extern int  func_ov008_02050e74(void);
extern int  func_ov008_02050c7c(int a);
extern void func_ov008_02055c4c(void *object, void *source);
extern void func_0202ff8c(int surface, TileSurfaceCfg *cfg);
extern int  func_02030694(void);
extern void func_020301c8(int node, int a, int b, int c, int d, int e);
extern void func_020300f8(int node);
extern u32  func_020235d0(int a, int b);
extern int *WM_EndKeySharing_0x0205665c(int a, int b);
extern void func_ov008_0205af08(int *a, int b);
extern void func_02030278(int node, int a, int b, int c, int *d, int e);
extern int  func_ov008_02051028(void);
extern u32  func_ov008_0205ae90(void);
extern int *func_ov008_02055c84(int *buf, int idx);
extern void func_ov008_02055c74(int *buf);
extern void func_ov008_02050b3c(int a);
extern TileSurfaceCfg data_ov008_0208ee5c;
extern TileSurfaceCfg data_ov008_0208ee0c;
extern TileSurfaceCfg data_ov008_0208ee34;
extern char data_ov008_0209032c[];
extern char data_ov008_02090344[];
extern char data_ov008_02090348[];

void func_ov008_0205af54(int obj)
{
    TileSurfaceCfg cfg0;
    TileSurfaceCfg cfg1;
    TileSurfaceCfg cfg2;
    int textIter[3];
    int *rec;
    int vram;
    u32 counter;
    u32 sel;
    u32 minVal;

    cfg0 = data_ov008_0208ee5c;
    cfg1 = data_ov008_0208ee0c;
    cfg2 = data_ov008_0208ee34;
    cfg0.pPixels = (void *)func_ov008_02050e74();
    vram = func_ov008_02050c7c(9);
    cfg0.nVramTarget = vram;
    cfg1.nVramTarget = vram;
    cfg2.nVramTarget = vram;
    cfg1.pPixels = cfg0.pPixels;
    cfg2.pPixels = cfg0.pPixels;
    func_ov008_02055c4c((void *)(obj + 0x14f4), data_ov008_0209032c);
    func_0202ff8c(obj + 0x1420, &cfg0);
    func_0202ff8c(obj + 0x145c, &cfg1);
    func_0202ff8c(obj + 0x1498, &cfg2);
    if (*(int *)(obj + 0x14e0) == 0 || func_02030694() != 0) {
        func_020301c8(obj + 0x1420, 0x8e, 2, 1, 0x821, (int)data_ov008_02090344);
    }
    func_020300f8(obj + 0x1420);
    sel = 4;
    counter = func_020235d0(0, 9);
    if (0x165 <= counter) sel = 0;
    rec = WM_EndKeySharing_0x0205665c(obj + 0x13fc, sel);
    func_ov008_0205af08((int *)(obj + 0x145c), (int)rec);
    rec = WM_EndKeySharing_0x0205665c(obj + 0x13fc, sel);
    func_02030278(obj + 0x145c, 2, 3, 1, rec, 0);
    func_020300f8(obj + 0x145c);
    if (*(int *)(obj + 0x14e0) != 0 && func_ov008_02051028() != 0) {
        func_ov008_02055c4c(textIter, data_ov008_02090348);
        minVal = func_ov008_0205ae90();
        if (minVal != 0) {
            rec = func_ov008_02055c84(textIter, minVal + 0xe);
            func_02030278(obj + 0x1498, 2, 3, 1, rec, 0);
            func_020300f8(obj + 0x1498);
        }
        func_ov008_02055c74(textIter);
    }
    func_ov008_02050b3c(9);
}
