/* Register two handler slots for the sub-object at param_1+0xe0 (types 0 and 2). */
extern void func_0202accc(int a, int b, int c, int d);

void func_ov106_020b7794(int param_1) {
    func_0202accc(param_1, 0, param_1 + 0xe0, 0);
    func_0202accc(param_1, 2, param_1 + 0xe0, 0);
}
