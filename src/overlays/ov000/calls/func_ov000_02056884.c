/* Forward to 02056874 (full args) and 0205687c (a, b, d). */
extern void func_ov000_02056874(int a, int b, int c, int d);
extern void func_ov000_0205687c(int a, int b, int d);
void func_ov000_02056884(int param_1, int param_2, int param_3, int param_4) {
    func_ov000_02056874(param_1, param_2, param_3, param_4);
    func_ov000_0205687c(param_1, param_2, param_4);
}
