/* func_ov008_0206fee0 -- push (param_3,param_4) to the widget bound to tag param_2, then fire its
 * change callback. Finds the entry (func_ov008_02055808), sets its value (func_ov008_02055874),
 * and invokes its +0x?? handler (func_ov008_020558f4). */
extern int  func_ov008_02055808(int owner, unsigned int tag);
extern void func_ov008_02055874(int owner, int entry, unsigned short a, unsigned short b);
extern void func_ov008_020558f4(int owner, int entry);

void func_ov008_0206fee0(int param_1, unsigned int param_2, unsigned short param_3, unsigned short param_4) {
    int entry = func_ov008_02055808(param_1, param_2 & 0xffff);
    func_ov008_02055874(param_1, entry, param_3, param_4);
    func_ov008_020558f4(param_1, entry);
}
