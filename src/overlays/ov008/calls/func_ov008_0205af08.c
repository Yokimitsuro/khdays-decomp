/* func_ov008_0205af08 -- re-measure a text field's rendered width and rebuild its glyph run.
 * For a live field with text (param_2), measures it (func_02013768 over param_1[8]/[9]); picks the
 * narrow (func_ov008_02050e74) or wide (func_ov008_02050ea4) glyph builder by the 0x71 threshold,
 * and if the result changed, updates the head/cursor pointers (param_1[0] and [8]). */
extern int func_02013768(int *text, int len, int arg, int *out);
extern int func_ov008_02050e74(void);
extern int func_ov008_02050ea4(void);

void func_ov008_0205af08(int *param_1, int param_2) {
    if (param_1 != 0 && param_2 != 0) {
        int result = func_02013768((int *)param_1[8], param_1[9], param_2, 0);
        if (result > 0x70) {
            result = func_ov008_02050ea4();
        } else {
            result = func_ov008_02050e74();
        }
        if (result != *param_1) {
            *param_1 = result;
            param_1[8] = result;
        }
    }
}
