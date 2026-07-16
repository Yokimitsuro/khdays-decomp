/* func_ov025_020b0250 -- draw a string with a 1px drop shadow (ov025 twin of ov008 02082d44):
 * once offset (+1,+1) one colour darker, then again at (x,y) in the requested colour. */
extern int  func_ov025_02084b14(void);
extern void func_020301c8(int dst, int x, int y, int colour, unsigned int flags, int text);

void func_ov025_020b0250(int param_1, int param_2, int param_3, unsigned int param_4, int param_5) {
    int ctx = func_ov025_02084b14();
    func_020301c8(ctx + 4, param_1 + 1, param_2 + 1, param_3 - 1, param_4, param_5);
    func_020301c8(ctx + 4, param_1, param_2, param_3, param_4, param_5);
}
