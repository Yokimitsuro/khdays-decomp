/* func_ov008_0206fe50 -- push (param_3,param_4) to the widget bound to tag param_2
 * (func_ov008_020558b8). Resolves the tag entry via func_ov008_02055808 (called twice, as the ROM
 * does; the first result is unused). */
extern int  func_ov008_02055808(int owner, unsigned short tag);
extern void func_ov008_020558b8(int owner, int entry, unsigned short a, unsigned short b);

void func_ov008_0206fe50(int param_1, unsigned int param_2, unsigned short param_3, unsigned short param_4) {
    func_ov008_02055808(param_1, param_2);
    int entry = func_ov008_02055808(param_1, param_2);
    func_ov008_020558b8(param_1, entry, param_3, param_4);
}
