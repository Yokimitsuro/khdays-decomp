/* func_ov008_0206b5f4 -- Ov008_UpdateCommWidgets (184 B, 12 relocs).
 * Reflects a wireless/comm status value into the two menu widgets (ids 2 and 1) on the menu's
 * widget context. Bails out early if the context is unavailable or either gate check
 * (func_02030640 / func_02030670) is false. Reads a signed 8-bit value from the WM query: when
 * it is valid (>= 0) both widgets are set to that value via func_ov008_02054c80; when it is
 * unavailable (< 0) both widgets are disabled via func_ov008_02054ba4(..., 0). */
typedef unsigned short u16;

extern void *func_ov008_02050c64(void);
extern int   func_02030640(void);
extern int   func_02030670(void);
extern int   WM_EndKeySharing_0x020bf240(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054c80(void *ctx, void *widget, int value);
extern void  func_ov008_02054ba4(void *ctx, void *widget, int flag);

void func_ov008_0206b5f4(void)
{
    void *ctx = func_ov008_02050c64();
    if (ctx == 0) return;
    if (func_02030640() == 0) return;
    if (func_02030670() == 0) return;
    {
        int v = (signed char)WM_EndKeySharing_0x020bf240();
        if (v >= 0) {
            func_ov008_02054c80(ctx, func_ov008_02054788(ctx, 2), (u16)v);
            func_ov008_02054c80(ctx, func_ov008_02054788(ctx, 1), (u16)v);
        } else {
            func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 2), 0);
            func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 1), 0);
        }
    }
}
