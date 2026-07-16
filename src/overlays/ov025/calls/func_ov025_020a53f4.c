/* func_ov025_020a53f4 -- push (param_3,param_4) to the widget bound to tag param_2
 * (func_ov025_02089560). Resolves the tag entry via func_ov025_020894b0 (called twice, as the ROM
 * does; the first result is unused). */
extern int  func_ov025_020894b0(int owner, unsigned short tag);
extern void func_ov025_02089560(int owner, int entry, unsigned short a, unsigned short b);

void func_ov025_020a53f4(int param_1, unsigned int param_2, unsigned short param_3, unsigned short param_4) {
    func_ov025_020894b0(param_1, param_2);
    int entry = func_ov025_020894b0(param_1, param_2);
    func_ov025_02089560(param_1, entry, param_3, param_4);
}
