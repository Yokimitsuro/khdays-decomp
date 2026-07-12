/* Emit the +0x4c and +0x68 spline pair from the a/b vectors, then finalize both. */
extern int func_ov026_020842f8(void);
extern void func_02035fb0(int dst, int mode, int a, int b, int extra);
extern void func_02035ffc(int dst);
void func_ov026_0208437c(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6) {
    int *va = (int *)param_4;
    int *vb = (int *)param_5;
    if (param_4 == 0) va = (int *)func_ov026_020842f8();
    func_02035fb0(param_2 + 0x4c, param_3, va[0], vb[0], param_6);
    func_02035fb0(param_2 + 0x68, param_3, va[1], vb[1], param_6);
    func_02035ffc(param_2 + 0x4c);
    func_02035ffc(param_2 + 0x68);
}
