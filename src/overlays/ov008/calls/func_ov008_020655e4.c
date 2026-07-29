/* func_ov008_020655e4 -- Ov008_UpdateButton3State (128 B, 6 relocs).
 * Toggles menu widget id 3 in sync with the func_ov008_0206f78c() condition, using
 * state->field48 to remember whether it is currently disabled so the work is done only on the
 * transition. When the condition holds and the button is not already disabled, it disables
 * widget 3 and sets state->field48 = 1; when the condition clears and the button is currently
 * disabled, it re-enables widget 3 and clears state->field48. The widget context comes from
 * func_ov008_02050c54; the enable flag is pushed via func_ov008_02054ba4. */
typedef unsigned char u8;

typedef struct Ov008ToggleState {
    u8  pad_0000[0x48];
    int field48;            /* 0x48: 1 while widget 3 is disabled */
} Ov008ToggleState;

extern void *func_ov008_02050c54(void);
extern int   func_ov008_0206f78c(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054ba4(void *ctx, void *widget, int flag);

void func_ov008_020655e4(Ov008ToggleState *param_1)
{
    void *ctx = func_ov008_02050c54();

    if (func_ov008_0206f78c() != 0) {
        if (param_1->field48 != 0) {
            return;
        }
        func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 3), 0);
        param_1->field48 = 1;
    } else {
        if (param_1->field48 == 0) {
            return;
        }
        func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 3), 1);
        param_1->field48 = 0;
    }
}
