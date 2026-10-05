/* Ov025_DrawSavePage -- draw the selected save/equipment page (ov025 build of Ov008_DrawSavePage).
 * Builds the page view from the preset item grid, blits the panel, draws the
 * page labels and counters, then draws the selected title and optional warning.
 * `count` is reused for the alternate font handle after the count text is drawn;
 * this preserves the original MWCC register assignment in the portrait block.
 */

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
extern unsigned  data_ov025_020b3c78[3];
extern char      data_ov025_020b4d90[];
extern char      data_ov025_020b4d9c[];
extern char      data_ov025_020b4da8[];
extern char      data_ov025_020b4dac[];
extern char      data_ov025_020b4db4[];

extern int   Obj_GetWord18(int a);
extern void  NNS_FndInitList(NNSFndList *list, int off);
extern void  Ov025_InitRecordContext(IterSelf *self, int a);
extern void  Ov025_BuildMenuGrid(IterSelf *self, void *entries, NNSFndList *list, void *ids);
extern void  Ov025_RebuildViewAndCountCells(IterSelf *self, void *entries, NNSFndList *list);
extern int   Ov025_CountChildEntries(IterSelf *self);
extern void  Ov025_ReleaseHandleGridAndList(IterSelf *self, void *entries, NNSFndList *list);
extern void  MIi_CpuCopyFast(void *dst, void *src, unsigned n);
extern int  *Ov025_GetVarRecordByIndex(int base, int idx);
extern void  Text_DrawWithShadow(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  Text_DrawDirectional_2(int dctx, int x, int y, int mode, int a5, void *a6);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern int   GameState_IsFlagSet(int flagId);
extern int   NNSi_G2dFontGetTextWidth(int a, int b, int c);
extern int   Ov025_GetCtxBlock968c(void);
extern int   Ov025_GetDescriptor3(void);
extern int   Ov025_CheckPageItemLimits(int ctx, int page);
extern void  func_ov025_02087254(IterSelf *self);
extern void  EnqueueObjGfxCommand(int dctx);

void Ov025_DrawSavePage(int ctx, int page)
{
    struct { unsigned tag[3]; NNSFndList list; } hdr;
    unsigned collect[120];
    IterSelf self;
    u16      text[128];
    void    *saved;
    int      f04, count, f00, flag;
    int     *rec;

    saved = *(void **)(Obj_GetWord18(ctx + 0xe8) + 0x20);
    *(Tmpl3 *)hdr.tag = *(Tmpl3 *)data_ov025_020b3c78;
    NNS_FndInitList(&hdr.list, 0x28);
    Ov025_InitRecordContext(&self, ctx + 0x2090);
    Ov025_BuildMenuGrid(&self, collect, &hdr.list, gGameState + 0xc10 + page * 0xf0);
    Ov025_RebuildViewAndCountCells(&self, collect, &hdr.list);
    f04 = self.f04;
    count = Ov025_CountChildEntries(&self);
    f00 = self.f00;
    Ov025_ReleaseHandleGridAndList(&self, collect, &hdr.list);
    MIi_CpuCopyFast(*(void **)(ctx + 0x2f4), saved, *(unsigned *)(ctx + 0x2ec));

    rec = Ov025_GetVarRecordByIndex(ctx + 0x28c, hdr.tag[page]);
    Text_DrawWithShadow(ctx + 0xe8, 8, 4, 0xf3, (int)rec, 0);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x28c, 0x17);
    Text_DrawDirectional_2(ctx + 0xe8, 0xca, 4, 0xf3, 0x821, rec);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x28c, 0x18);
    Text_DrawDirectional_2(ctx + 0xe8, 0x9a, 0x12, 0xf3, 0x821, rec);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x28c, 0x19);
    Text_DrawDirectional_2(ctx + 0xe8, 0xde, 0x12, 0xf3, 0x821, rec);

    flag = GameState_IsFlagSet(page + 0x3c67);
    if (flag != 0) {
        int clamp = *(int *)(ctx + 0x1e74);
        if (clamp > 0x78) {
            Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4d90, f04, 0x78);
        } else {
            Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4d90, f04, clamp);
        }
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4d9c, data_ov025_020b4da8, data_ov025_020b4da8);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xf8, 4, 0xf1, 0x821, text);

    if (flag != 0) {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4dac, count);
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4db4, data_ov025_020b4da8);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xb4, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4dac, f00);
    } else {
        Text_FormatUtf16(text, 0x80, (const unsigned short *)data_ov025_020b4db4, data_ov025_020b4da8);
    }
    Text_DrawDirectional_2(ctx + 0xe8, 0xf8, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        int a = Ov025_GetCtxBlock968c();
        count = Ov025_GetDescriptor3();
        int hi;
        rec = *(int **)(self.f74 * 0x3e0 + *(int *)(ctx + 0x208c) + 0xc);
        hi = NNSi_G2dFontGetTextWidth(*(int *)(ctx + 0x108), *(int *)(ctx + 0x10c), rec) >= 0x56;
        if (hi) *(int *)(ctx + 0x108) = count;
        Text_DrawWithShadow(ctx + 0xe8, 8, 0x12, 0xf3, (int)rec, 0);
        if (hi) *(int *)(ctx + 0x108) = a;
    }

    if (Ov025_CheckPageItemLimits(ctx, page) != 0) {
        rec = Ov025_GetVarRecordByIndex(ctx + 0x28c, 0x1a);
        Text_DrawWithShadow(ctx + 0xe8, 0x2c, 4, 0xf1, (int)rec, 0);
    }
    func_ov025_02087254(&self);
    EnqueueObjGfxCommand(ctx + 0xe8);
}
