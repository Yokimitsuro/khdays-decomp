/* func_ov008_0206f7b0 -- Ov008_UpdateMenuButton5 (116 B, 7 relocs).
 * Updates menu button id 5's enabled state when a tracked value changes. Bails unless the global
 * gate data_ov008_02090f20 is set and the new value differs from the cached one
 * (ctx1->fieldC) -- a short-circuit `||` guard. Caches the new value (ctx1->fieldC = param_1),
 * gets the widget context (02050c64), looks up widget id 5, then: if param_1 != 0 it primes the
 * widget (func_ov008_02054c80(ctx, widget, 0)) and enables it (func_ov008_02054ba4(ctx, widget,
 * 1)); otherwise it just disables it (func_ov008_02054ba4(ctx, widget, 0)). */
typedef unsigned char u8;

typedef struct Ov008Ctx1 { u8 pad_0000[0xc]; int fieldC; } Ov008Ctx1;

extern Ov008Ctx1 *func_ov008_02050cec(void);
extern int   data_ov008_02090f20;
extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054c80(void *ctx, void *widget, int value);
extern void  func_ov008_02054ba4(void *ctx, void *widget, int flag);

void func_ov008_0206f7b0(int param_1)
{
    Ov008Ctx1 *ctx1 = func_ov008_02050cec();
    void *ctx2;
    void *widget;

    if (data_ov008_02090f20 == 0 || ctx1->fieldC == param_1) {
        return;
    }
    ctx1->fieldC = param_1;
    ctx2 = func_ov008_02050c64();
    widget = func_ov008_02054788(ctx2, 5);
    if (param_1 != 0) {
        func_ov008_02054c80(ctx2, widget, 0);
        func_ov008_02054ba4(ctx2, widget, 1);
    } else {
        func_ov008_02054ba4(ctx2, widget, 0);
    }
}
