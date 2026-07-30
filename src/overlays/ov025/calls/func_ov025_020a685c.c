/* func_ov025_020a685c -- Ov008_LayoutMenuRows (240 B, 9 relocs).
 * Lays out a vertical run of menu widgets in FX32 (<<12) coordinates. Reads a shared base value
 * (func_ov025_02088544 on widget 2) into wp.base, computes the row origin r5 = ctx->field20 +
 * ctx->field14, then positions widgets 4..0x13 at y = ((i-4)*8 + 0x10 + r5), widget 2 at y = r5,
 * and widget 3 at y = r5 + ctx->field24 - 0x10, each pushed through func_ov025_02088500 with the
 * {base, pos} pair. The row-offset add is written `p += r5` so the freshly-built offset (not the
 * loop-invariant r5) is the dying operand mwcc reuses for the destination register. */
typedef unsigned char u8;

typedef struct WidgetPos {
    int base;   /* 0x0: shared base value from func_ov025_02088544 */
    int pos;    /* 0x4: per-widget FX32 position */
} WidgetPos;

typedef struct Ov008LayoutCtx {
    u8  pad_0000[0x14];
    int field14;   /* 0x14 */
    u8  pad_0018[0x8];
    int field20;   /* 0x20 */
    int field24;   /* 0x24 */
} Ov008LayoutCtx;

extern void *func_ov025_02084a8c(void);
extern void *func_ov025_0208843c(void *wctx, int id);
extern int  *func_ov025_02088544(void *wctx, void *w);
extern void  func_ov025_02088500(void *wctx, void *w, WidgetPos *wp);

void func_ov025_020a685c(Ov008LayoutCtx *ctx)
{
    void *wctx = func_ov025_02084a8c();
    WidgetPos wp = {0, 0};
    int r5;
    int i;

    wp.base = *func_ov025_02088544(wctx, func_ov025_0208843c(wctx, 2));
    r5 = ctx->field20 + ctx->field14;
    for (i = 4; i <= 0x13; i++) {
        int p = (i - 4) * 8 + 0x10;
        p += r5;
        wp.pos = p << 12;
        func_ov025_02088500(wctx, func_ov025_0208843c(wctx, i), &wp);
    }
    wp.pos = r5 << 12;
    func_ov025_02088500(wctx, func_ov025_0208843c(wctx, 2), &wp);
    wp.pos = (r5 + ctx->field24 - 0x10) << 12;
    func_ov025_02088500(wctx, func_ov025_0208843c(wctx, 3), &wp);
}
