extern void func_0202accc(int a, int b, int c, short d);
extern void func_01fff774(int a, int b, int c);

void func_ov057_020b67e8(int a, int obj, int idx) {
    *(int *)obj = 1;
    func_0202accc(obj + 4, 0, obj + 0xe4, idx);
    func_0202accc(obj + 4, 2, obj + 0xe4, idx);
    func_01fff774(obj + 4, 0, 0);
    func_01fff774(obj + 4, 2, 0);
}
