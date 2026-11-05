/*
 * Ov008_WorldMap_SetupTextSurfaces - build the three menu text tile-surfaces and draw the
 * heading and counter text, called from Ov008_WorldMap_StateTick (state 1).
 *
 * Copies three TileSurfaceCfg templates (data_ov008_0208ee5c/0208ee0c/0208ee34), patches all
 * three to share the tile pixel buffer (Ov008_GetCtxBlock968c) and VRAM target
 * (Ov008_ResetEntry(9)), configures the shared surface slot at obj+0x14f4, then inits and
 * uploads each 4bpp tile surface (obj+0x1420/0x145c/0x1498). Draws the directional heading
 * text into surface 0 when the menu is idle or the session is ready; measures and draws the
 * subtitle into surface 1 (variant 4, or 0 once GameState field 9 reaches 0x165); and, in
 * multiplayer mode with a context object, draws the lowest mission-id record into surface 2.
 *
 * Arity notes: Ov008_VarTable_Load (surface setup) takes 2 args - the trailing r2/r3 Ghidra
 * shows are left over from the 4-word template ldm. Text_DrawDirectional_2 (directional text) takes 6
 * args (2 on the stack: 0x821 then data_ov008_02090344); Ghidra's 7th is an uninitialised-stack
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

extern int  Ov008_GetCtxBlock968c(void);
extern int  Ov008_ResetEntry(int a);
extern void Ov008_VarTable_Load(void *object, void *source);
extern void TileSurface_InitAndUpload4bpp(int surface, TileSurfaceCfg *cfg);
extern int  Session_IsReady(void);
extern void Text_DrawDirectional_2(int node, int a, int b, int c, int d, int e);
extern void EnqueueObjGfxCommand(int node);
extern u32  GameState_GetField(int a, int b);
extern int *func_ov008_0205665c(int a, int b);
extern void Ov008_RemeasureTextField(int *a, int b);
extern void Text_DrawWithShadow(int node, int a, int b, int c, int *d, int e);
extern int  Ov008_GetCtxObject9634(void);
extern u32  Ov008_FindMinListValue(void);
extern int *Ov008_GetVarRecordByIndex(int *buf, int idx);
extern void Ov008_FreeResourceRecordBuffer(int *buf);
extern void Ov008_MarkSlotUsed(int a);
extern TileSurfaceCfg data_ov008_0208ee5c;
extern TileSurfaceCfg data_ov008_0208ee0c;
extern TileSurfaceCfg data_ov008_0208ee34;
extern char gOv008UiCmStrSelectTextPath[];
extern char data_ov008_02090344[];
extern char gOv008UiCmStrStatusTextPath[];

void Ov008_WorldMap_SetupTextSurfaces(int obj)
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
    cfg0.pPixels = (void *)Ov008_GetCtxBlock968c();
    vram = Ov008_ResetEntry(9);
    cfg0.nVramTarget = vram;
    cfg1.nVramTarget = vram;
    cfg2.nVramTarget = vram;
    cfg1.pPixels = cfg0.pPixels;
    cfg2.pPixels = cfg0.pPixels;
    Ov008_VarTable_Load((void *)(obj + 0x14f4), gOv008UiCmStrSelectTextPath);
    TileSurface_InitAndUpload4bpp(obj + 0x1420, &cfg0);
    TileSurface_InitAndUpload4bpp(obj + 0x145c, &cfg1);
    TileSurface_InitAndUpload4bpp(obj + 0x1498, &cfg2);
    if (*(int *)(obj + 0x14e0) == 0 || Session_IsReady() != 0) {
        Text_DrawDirectional_2(obj + 0x1420, 0x8e, 2, 1, 0x821, (int)data_ov008_02090344);
    }
    EnqueueObjGfxCommand(obj + 0x1420);
    sel = 4;
    counter = GameState_GetField(0, 9);
    if (0x165 <= counter) sel = 0;
    rec = func_ov008_0205665c(obj + 0x13fc, sel);
    Ov008_RemeasureTextField((int *)(obj + 0x145c), (int)rec);
    rec = func_ov008_0205665c(obj + 0x13fc, sel);
    Text_DrawWithShadow(obj + 0x145c, 2, 3, 1, rec, 0);
    EnqueueObjGfxCommand(obj + 0x145c);
    if (*(int *)(obj + 0x14e0) != 0 && Ov008_GetCtxObject9634() != 0) {
        Ov008_VarTable_Load(textIter, gOv008UiCmStrStatusTextPath);
        minVal = Ov008_FindMinListValue();
        if (minVal != 0) {
            rec = Ov008_GetVarRecordByIndex(textIter, minVal + 0xe);
            Text_DrawWithShadow(obj + 0x1498, 2, 3, 1, rec, 0);
            EnqueueObjGfxCommand(obj + 0x1498);
        }
        Ov008_FreeResourceRecordBuffer(textIter);
    }
    Ov008_MarkSlotUsed(9);
}
