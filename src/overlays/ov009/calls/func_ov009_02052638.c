/* Forward to 02056874 (full args) and 0205687c (a, b, d). */
extern void func_ov009_02052628(int a, int b, int c, int d);
extern void func_ov009_02052630(int a, int b, int d);
void func_ov009_02052638(int param_1, int param_2, int param_3, int param_4) {
    func_ov009_02052628(param_1, param_2, param_3, param_4);
    func_ov009_02052630(param_1, param_2, param_4);
}
