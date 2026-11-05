/*
 * Ov008_WorldMap_SetupTextSurfaces - build the three menu text tile-surfaces and draw the
 * heading and counter text, called from Ov008_WorldMap_StateTick (state 1).
 *
 * Copies three TileSurfaceCfg templates (data_ov025_020b39bc/0208ee0c/0208ee34), patches all
 * three to share the tile pixel buffer (Ov008_GetCtxBlock968c) and VRAM target
 * (Ov008_ResetEntry(9)), configures the shared surface slot at obj+0x14f4, then inits and
 * uploads each 4bpp tile surface (obj+0x1420/0x145c/0x1498). Draws the directional heading
 * text into surface 0 when the menu is idle or the session is ready; measures and draws the
 * subtitle into surface 1 (variant 4, or 0 once GameState field 9 reaches 0x165); and, in
 * multiplayer mode with a context object, draws the lowest mission-id record into surface 2.
 *
 * Arity notes: Ov025_InitResourceRecord (surface setup) takes 2 args - the trailing r2/r3 Ghidra
 * shows are left over from the 4-word template ldm. Text_DrawDirectional_2 (directional text) takes 6
 * args (2 on the stack: 0x821 then data_ov025_020b4d10); Ghidra's 7th is an uninitialised-stack
 * phantom. Local declaration order places the three configs high-to-low so the ldm/stm copies
 * land at the ROM's sp offsets.
 */

#include "nitro/types.h"

typedef struct {
    u32 nUnk00, nUnk04, nWidthTiles, nHeightTiles, nRowTiles, nPaletteIndex;
    u32 nVramTarget;
    u32 nUnk1c;
    void *pPixels;
    u32 nUnk24;
} TileSurfaceCfg;

extern int  Ov025_GetCtxBlock968c(void);
extern int  Ov025_LookupEntry(int a);
extern void Ov025_InitResourceRecord(void *object, void *source);
extern void TileSurface_InitAndUpload4bpp(int surface, TileSurfaceCfg *cfg);
extern int  Session_IsReady(void);
extern void Text_DrawDirectional_2(int node, int a, int b, int c, int d, int e);
extern void EnqueueObjGfxCommand(int node);
extern u32  GameState_GetField(int a, int b);
extern int *func_ov025_0208a26c(int a, int b);
extern void Ov025_UpdateThresholdSlot(int *a, int b);
extern void Text_DrawWithShadow(int node, int a, int b, int c, int *d, int e);
extern int  Ov025_GetCtxObject9634(void);
extern u32  Ov025_FindMinListValue(void);
extern int *Ov025_GetVarRecordByIndex(int *buf, int idx);
extern void Ov025_FreeResourceRecordBuffer(int *buf);
extern void Ov025_MarkSlotUsed(int a);
extern TileSurfaceCfg data_ov025_020b39bc;
extern TileSurfaceCfg data_ov025_020b396c;
extern TileSurfaceCfg data_ov025_020b3994;
extern char gOv025UiCmStrSelectTextPath[];
extern char data_ov025_020b4d10[];
extern char gOv025UiCmStrStatusTextPath[];

void Ov025_WorldMap_SetupTextSurfaces(int obj)
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

    cfg0 = data_ov025_020b39bc;
    cfg1 = data_ov025_020b396c;
    cfg2 = data_ov025_020b3994;
    cfg0.pPixels = (void *)Ov025_GetCtxBlock968c();
    vram = Ov025_LookupEntry(9);
    cfg0.nVramTarget = vram;
    cfg1.nVramTarget = vram;
    cfg2.nVramTarget = vram;
    cfg1.pPixels = cfg0.pPixels;
    cfg2.pPixels = cfg0.pPixels;
    Ov025_InitResourceRecord((void *)(obj + 0x14f4), gOv025UiCmStrSelectTextPath);
    TileSurface_InitAndUpload4bpp(obj + 0x1420, &cfg0);
    TileSurface_InitAndUpload4bpp(obj + 0x145c, &cfg1);
    TileSurface_InitAndUpload4bpp(obj + 0x1498, &cfg2);
    if (*(int *)(obj + 0x14e0) == 0 || Session_IsReady() != 0) {
        Text_DrawDirectional_2(obj + 0x1420, 0x8e, 2, 1, 0x821, (int)data_ov025_020b4d10);
    }
    EnqueueObjGfxCommand(obj + 0x1420);
    sel = 4;
    counter = GameState_GetField(0, 9);
    if (0x165 <= counter) sel = 0;
    rec = func_ov025_0208a26c(obj + 0x13fc, sel);
    Ov025_UpdateThresholdSlot((int *)(obj + 0x145c), (int)rec);
    rec = func_ov025_0208a26c(obj + 0x13fc, sel);
    Text_DrawWithShadow(obj + 0x145c, 2, 3, 1, rec, 0);
    EnqueueObjGfxCommand(obj + 0x145c);
    if (*(int *)(obj + 0x14e0) != 0 && Ov025_GetCtxObject9634() != 0) {
        Ov025_InitResourceRecord(textIter, gOv025UiCmStrStatusTextPath);
        minVal = Ov025_FindMinListValue();
        if (minVal != 0) {
            rec = Ov025_GetVarRecordByIndex(textIter, minVal + 0xe);
            Text_DrawWithShadow(obj + 0x1498, 2, 3, 1, rec, 0);
            EnqueueObjGfxCommand(obj + 0x1498);
        }
        Ov025_FreeResourceRecordBuffer(textIter);
    }
    Ov025_MarkSlotUsed(9);
}
