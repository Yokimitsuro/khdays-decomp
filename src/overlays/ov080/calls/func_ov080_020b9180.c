extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov080_020b9180(int obj) {
    *(int *)obj = 2;
    func_0202accc(obj + 4, 0, obj + 0xe4, 0);
    func_0202accc(obj + 4, 2, obj + 0xe4, 0);
    func_0202accc(obj + 4, 1, obj + 0xe4, 0);
    func_01fff774(obj + 4, 0, 0);
    func_01fff774(obj + 4, 2, 0);
    func_01fff774(obj + 4, 1, 0);
}
