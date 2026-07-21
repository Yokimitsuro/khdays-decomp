/* Draw a page-A element via func_020301c8, optionally preceded by a drop-shadow pass offset by
 * (+1,+1,-1). The element base is page A + 0x10; param_1 is forwarded as the draw's last argument. */
extern int func_ov008_02050cd4(void);
extern void func_020301c8(int base, int x, int y, int z, unsigned int flags, int arg);

void func_ov008_0206ac18(int param_1, int param_2, int param_3, int param_4, unsigned int param_5, int param_6) {
    int page = func_ov008_02050cd4();
    if (param_6 != 0) {
        func_020301c8(page + 0x10, param_2 + 1, param_3 + 1, param_4 - 1, param_5, param_1);
    }
    func_020301c8(page + 0x10, param_2, param_3, param_4, param_5, param_1);
}
