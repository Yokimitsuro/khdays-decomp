/* func_ov008_0206fe98 -- push (param_3,param_4) to the active widget for tag param_2, then mark it
 * dirty. Finds the active entry (func_ov008_02055a8c), sets its value (func_ov008_02055ba4), and
 * flags it (func_ov008_02055aec(...,1)). */
extern int  func_ov008_02055a8c(int owner, unsigned int tag);
extern void func_ov008_02055ba4(int owner, int entry, unsigned short a, unsigned short b);
extern void func_ov008_02055aec(int owner, int entry, int flag);

void func_ov008_0206fe98(int param_1, unsigned int param_2, unsigned short param_3, unsigned short param_4) {
    int entry = func_ov008_02055a8c(param_1, param_2 & 0xffff);
    func_ov008_02055ba4(param_1, entry, param_3, param_4);
    func_ov008_02055aec(param_1, entry, 1);
}
