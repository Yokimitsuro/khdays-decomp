/* func_ov000_02050514 -- push a value to the logo scene's sub-widget, ov000. Reads
 * the current selection (func_ov000_02055b48 over the widget @scene+0x4c) and applies
 * `value` to it via func_ov000_02055cb4. */
extern char *data_ov000_0205ac24;
extern int  func_ov000_02055b48(void *widget, int count);
extern void func_ov000_02055cb4(void *widget, int sel, int value);
void func_ov000_02050514(int value) {
    char *base = data_ov000_0205ac24;
    int sel = func_ov000_02055b48(base + 0x4c, 0x3c);
    func_ov000_02055cb4(base + 0x4c, sel, value);
}
