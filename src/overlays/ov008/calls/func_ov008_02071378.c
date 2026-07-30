/* func_ov008_02071378 -- Ov008_LayoutMenuRows (240 B, 9 relocs).
 * Lays out a vertical run of menu widgets in FX32 (<<12) coordinates. Reads a shared base value
 * (func_ov008_0205489c on widget 2) into wp.base, computes the row origin r5 = ctx->field20 +
 * ctx->field14, then positions widgets 4..0x13 at y = ((i-4)*8 + 0x10 + r5), widget 2 at y = r5,
 * and widget 3 at y = r5 + ctx->field24 - 0x10, each pushed through func_ov008_02054858 with the
 * {base, pos} pair. The row-offset add is written `p += r5` so the freshly-built offset (not the
 * loop-invariant r5) is the dying operand mwcc reuses for the destination register. */
typedef unsigned char u8;

typedef struct WidgetPos {
    int base;   /* 0x0: shared base value from func_ov008_0205489c */
    int pos;    /* 0x4: per-widget FX32 position */
} WidgetPos;

typedef struct Ov008LayoutCtx {
    u8  pad_0000[0x14];
    int field14;   /* 0x14 */
    u8  pad_0018[0x8];
    int field20;   /* 0x20 */
    int field24;   /* 0x24 */
} Ov008LayoutCtx;

extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *wctx, int id);
extern int  *func_ov008_0205489c(void *wctx, void *w);
extern void  func_ov008_02054858(void *wctx, void *w, WidgetPos *wp);

void func_ov008_02071378(Ov008LayoutCtx *ctx)
{
    void *wctx = func_ov008_02050c64();
    WidgetPos wp = {0, 0};
    int r5;
    int i;

    wp.base = *func_ov008_0205489c(wctx, func_ov008_02054788(wctx, 2));
    r5 = ctx->field20 + ctx->field14;
    for (i = 4; i <= 0x13; i++) {
        int p = (i - 4) * 8 + 0x10;
        p += r5;
        wp.pos = p << 12;
        func_ov008_02054858(wctx, func_ov008_02054788(wctx, i), &wp);
    }
    wp.pos = r5 << 12;
    func_ov008_02054858(wctx, func_ov008_02054788(wctx, 2), &wp);
    wp.pos = (r5 + ctx->field24 - 0x10) << 12;
    func_ov008_02054858(wctx, func_ov008_02054788(wctx, 3), &wp);
}
