/* Ov008_DrawSavePage -- Ov008_DrawSavePage (936 B, 44 relocs).
 * Renders one save/equip page. Fetches the draw context (Obj_GetWord18) and snapshots a blit
 * source; copies a 3-word tag template out of data_ov008_0208f118; then runs the Ov008IterFrame
 * list walker over the u16 cell grid at *gGameState + 0xc10 + page*0xf0 (the same grid as
 * Ov008_CheckPageItemLimits) to build the view, capturing the walker's field 4 (before the count) and
 * field 0 (after). It blits the panel, draws the page label + three fixed captions, then formats
 * three text fields with the variadic sprintf Text_FormatUtf16 (branching on a game-state flag from
 * GameState_IsFlagSet) and draws each. When the flag is set it runs the character-portrait cursor logic
 * (temporarily swapping ctx[0x108] around a draw when NNSi_G2dFontGetTextWidth/Cursor_MaxOverRun returns
 * >= 0x56). Finally it asks Ov008_CheckPageItemLimits whether the page is over capacity and, if so, draws
 * the warning caption, then finalizes the walker and enqueues the gfx command.
 *
 * The draw helpers take their buffer/record argument as a pointer (a6 is void *, not an int): that
 * makes mwcc re-materialize the frame-relative text address fresh before each draw instead of
 * caching it in a callee-saved register -- the (int)-cast form is 8 bytes short. */

#include "nitro/types.h"

typedef struct Tmpl3 { unsigned a, b, c; } Tmpl3;

typedef struct NNSFndList {
    u16   numObjects;
    u16   offset;
    void *head;
    void *tail;
} NNSFndList;

typedef struct IterSelf {
    unsigned f00;              /* 0x00 */
    unsigned f04;              /* 0x04 */
    u8  pad_0008[0x2c - 0x08];
    int f2c;                   /* 0x2c */
    u8  pad_0030[0x74 - 0x30];
    int f74;                   /* 0x74 */
    u8  pad_0078[0x100 - 0x78];
} IterSelf;                    /* 0x100 */

extern char     *gGameState;
extern unsigned  data_ov008_0208f118[3];
extern char      data_ov008_020903c4[];
extern char      data_ov008_020903d0[];
extern char      data_ov008_020903dc[];
extern char      data_ov008_020903e0[];
extern char      data_ov008_020903e8[];

extern int   Obj_GetWord18(int a);
extern void  NNS_FndInitList(NNSFndList *list, int off);
extern void  Ov008_InitRecordContext(IterSelf *self, int a);
extern void  Ov008_BuildMenuGrid(IterSelf *self, void *entries, NNSFndList *list, void *ids);
extern void  Ov008_RebuildViewAndCountCells(IterSelf *self, void *entries, NNSFndList *list);
extern int   Ov008_CountChildEntries(IterSelf *self);
extern void  Ov008_ReleaseHandleGridAndList(IterSelf *self, void *entries, NNSFndList *list);
extern void  MIi_CpuCopyFast(void *dst, void *src, unsigned n);
extern int  *Ov008_GetVarRecordByIndex(int base, int idx);
extern void  Text_DrawWithShadow(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  Text_DrawDirectional_2(int dctx, int x, int y, int mode, int a5, void *a6);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern int   GameState_IsFlagSet(int flagId);
extern int   NNSi_G2dFontGetTextWidth(int a, int b, int c);
extern int   Ov008_GetCtxBlock968c(void);
extern int   Ov008_GetDescriptor3(void);
extern int   Ov008_CheckPageItemLimits(int ctx, int page);
extern void  func_ov008_02053464(IterSelf *self);
extern void  EnqueueObjGfxCommand(int dctx);

void Ov008_DrawSavePage(int ctx, int page)
{
    struct { unsigned tag[3]; NNSFndList list; } hdr;
    unsigned collect[120];
    IterSelf self;
    u16      text[128];
    void    *saved;
    int      f04, count, f00, flag;
    int     *rec;

    saved = *(void **)(Obj_GetWord18(ctx + 0xe8) + 0x20);
    *(Tmpl3 *)hdr.tag = *(Tmpl3 *)data_ov008_0208f118;
    NNS_FndInitList(&hdr.list, 0x28);
    Ov008_InitRecordContext(&self, ctx + 0x2090);
    Ov008_BuildMenuGrid(&self, collect, &hdr.list, gGameState + 0xc10 + page * 0xf0);
    Ov008_RebuildViewAndCountCells(&self, collect, &hdr.list);
    f04 = self.f04;
    count = Ov008_CountChildEntries(&self);
    f00 = self.f00;
    Ov008_ReleaseHandleGridAndList(&self, collect, &hdr.list);
    MIi_CpuCopyFast(*(void **)(ctx + 0x2f4), saved, *(unsigned *)(ctx + 0x2ec));

    rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, hdr.tag[page]);
    Text_DrawWithShadow(ctx + 0xe8, 8, 4, 0xf3, (int)rec, 0);
    rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, 0x17);
    Text_DrawDirectional_2(ctx + 0xe8, 0xca, 4, 0xf3, 0x821, rec);
    rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, 0x18);
    Text_DrawDirectional_2(ctx + 0xe8, 0x9a, 0x12, 0xf3, 0x821, rec);
    rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, 0x19);
    Text_DrawDirectional_2(ctx + 0xe8, 0xde, 0x12, 0xf3, 0x821, rec);

    flag = GameState_IsFlagSet(page + 0x3c67);
    if (flag != 0) {
        int clamp = *(int *)(ctx + 0x1e74);
        if (clamp > 0x78) {
            Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903c4, f04, 0x78);
        } else {
            Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903c4, f04, clamp);
        }
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903d0, data_ov008_020903dc, data_ov008_020903dc);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xf8, 4, 0xf1, 0x821, text);

    if (flag != 0) {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903e0, count);
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903e8, data_ov008_020903dc);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xb4, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903e0, f00);
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov008_020903e8, data_ov008_020903dc);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xf8, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        int a = Ov008_GetCtxBlock968c();
        int b = Ov008_GetDescriptor3();
        int hi;
        if (self.f2c != 0) {
            rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, 0x23);
        } else {
            rec = *(int **)(self.f74 * 0x3e0 + *(int *)(ctx + 0x208c) + 0xc);
        }
        hi = NNSi_G2dFontGetTextWidth(*(int *)(ctx + 0x108), *(int *)(ctx + 0x10c), rec) >= 0x56;
        if (hi) *(int *)(ctx + 0x108) = b;
        Text_DrawWithShadow(ctx + 0xe8, 8, 0x12, 0xf3, (int)rec, 0);
        if (hi) *(int *)(ctx + 0x108) = a;
    }

    if (Ov008_CheckPageItemLimits(ctx, page) != 0) {
        rec = Ov008_GetVarRecordByIndex(ctx + 0x28c, 0x1a);
        Text_DrawWithShadow(ctx + 0xe8, 0x2c, 4, 0xf1, (int)rec, 0);
    }
    func_ov008_02053464(&self);
    EnqueueObjGfxCommand(ctx + 0xe8);
}
