extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov089_020bbc28(int a, int obj) {
    if (*(int *)obj != 0) return;
    func_0202accc(obj + 0xc, 0, obj + 0xec, 0);
    func_0202accc(obj + 0xc, 2, obj + 0xec, 0);
    func_01fff774(obj + 0xc, 0, 0);
    func_01fff774(obj + 0xc, 2, 0);
    *(int *)obj = 1;
}
