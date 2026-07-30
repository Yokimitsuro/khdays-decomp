/* func_ov008_02071d40 -- Ov008_ApplyModeWidgets (380 B, 26 relocs).
 * Reconfigures the menu widgets 0x35..0x38 for a two-state mode toggle. When mode != 0 it wires
 * the pair (0x35 -> "checked" via func_ov008_02054cc4, 0x36 -> "unchecked" via
 * func_ov008_02054d3c) and enables widget 0x37 / disables 0x38; when mode == 0 it swaps the pair
 * (0x36 checked, 0x35 unchecked) and disables 0x37 / enables 0x38. Both branches first zero the
 * values of 0x35 and 0x36 (func_ov008_02054c80). If the applied mode changed since last time
 * (ctx->selected), it fires func_02033b78(0, 0), then stores the new mode. Twin of
 * func_ov008_02076e80 (same shape, ctx->selected at 0x184 there). */
typedef unsigned char u8;

typedef struct Ov008ModeCtx {
    u8  pad_0000[0x4fc];
    int selected;   /* 0x4fc: last applied mode */
} Ov008ModeCtx;

extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *wctx, int id);
extern void  func_ov008_02054c80(void *wctx, void *w, int val);
extern void  func_ov008_02054cc4(void *wctx, void *w);
extern void  func_ov008_02054d3c(void *wctx, void *w, int arg);
extern void  func_ov008_02054ba4(void *wctx, void *w, int flag);
extern void  func_02033b78(int a, int b);

void func_ov008_02071d40(Ov008ModeCtx *ctx, int mode)
{
    void *wctx = func_ov008_02050c64();
    if (mode != 0) {
        func_ov008_02054c80(wctx, func_ov008_02054788(wctx, 0x35), 0);
        func_ov008_02054c80(wctx, func_ov008_02054788(wctx, 0x36), 0);
        func_ov008_02054cc4(wctx, func_ov008_02054788(wctx, 0x35));
        func_ov008_02054d3c(wctx, func_ov008_02054788(wctx, 0x36), 0);
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, 0x37), 1);
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, 0x38), 0);
    } else {
        func_ov008_02054c80(wctx, func_ov008_02054788(wctx, 0x35), 0);
        func_ov008_02054c80(wctx, func_ov008_02054788(wctx, 0x36), 0);
        func_ov008_02054cc4(wctx, func_ov008_02054788(wctx, 0x36));
        func_ov008_02054d3c(wctx, func_ov008_02054788(wctx, 0x35), 0);
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, 0x37), 0);
        func_ov008_02054ba4(wctx, func_ov008_02054788(wctx, 0x38), 1);
    }
    if (ctx->selected != mode) {
        func_02033b78(0, 0);
    }
    ctx->selected = mode;
}
