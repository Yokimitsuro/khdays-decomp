/* func_ov025_020917e4 -- Ov008_LayoutMenuRows2 (244 B, 9 relocs).
 * Sibling of func_ov008_02071378 for a different menu screen. Sets the row origin
 * ctx->field2fc = arg1 + 0x18, reads a shared base (func_ov025_02088544 on widget 0xd) into the
 * {base,pos} pair, then lays out widgets 0xf..0x1a at ((field2fc + (i-0xf)*8 + 0x10) << 12),
 * widget 0xd at (field2fc << 12), and widget 0xe at ((field2fc + ctx->field2f8 - 0x10) << 12),
 * each pushed via func_ov025_02088500. field2fc is re-read from the object each iteration
 * (matching the ROM's per-iteration load). */
typedef unsigned char u8;

typedef struct WidgetPos {
    int base;   /* 0x0 */
    int pos;    /* 0x4 */
} WidgetPos;

typedef struct Ov008LayoutCtx2 {
    u8  pad_0000[0x2f8];
    int field2f8;   /* 0x2f8 */
    int field2fc;   /* 0x2fc: row origin (set from arg1 + 0x18) */
} Ov008LayoutCtx2;

extern void *func_ov025_02084a7c(void);
extern void *func_ov025_0208843c(void *wctx, int id);
extern int  *func_ov025_02088544(void *wctx, void *w);
extern void  func_ov025_02088500(void *wctx, void *w, WidgetPos *wp);

void func_ov025_020917e4(Ov008LayoutCtx2 *ctx, int arg1)
{
    WidgetPos wp = {0, 0};
    void *wctx;
    int i;

    ctx->field2fc = arg1 + 0x18;
    wctx = func_ov025_02084a7c();
    wp.base = *func_ov025_02088544(wctx, func_ov025_0208843c(wctx, 0xd));
    for (i = 0xf; i <= 0x1a; i++) {
        wp.pos = (ctx->field2fc + (i - 0xf) * 8 + 0x10) << 12;
        func_ov025_02088500(wctx, func_ov025_0208843c(wctx, i), &wp);
    }
    wp.pos = ctx->field2fc << 12;
    func_ov025_02088500(wctx, func_ov025_0208843c(wctx, 0xd), &wp);
    wp.pos = (ctx->field2fc + ctx->field2f8 - 0x10) << 12;
    func_ov025_02088500(wctx, func_ov025_0208843c(wctx, 0xe), &wp);
}
