/* Temporarily nudge sub-object param_2's transform by param_3*2 (field at
 * param_1+0x1c, 0x18-stride), redraw it via func_020233b0, then undo the nudge.
 * Skipped entirely when the global mode (data_0204be08->[4]->[0xd0]) is 3, param_2
 * is 1, and bit 1 of func_02020a9c() is set (i.e. a special-cased state). */
#pragma thumb on
extern unsigned short func_02020a9c(void);
extern void func_020233b0(int a, int b);
extern char data_0204be08[];
void func_02023400(int param_1, int param_2, int param_3) {
    if (*(int *)(*(int *)(data_0204be08 + 4) + 0xd0) != 3 || param_2 != 1 ||
        (func_02020a9c() & 2) == 0) {
        int delta = param_3 * 2;
        int *field = (int *)(param_1 + 0x1c + param_2 * 0x18);
        *field = *field + delta;
        func_020233b0(param_1, param_2);
        *field = *field - delta;
    }
}
