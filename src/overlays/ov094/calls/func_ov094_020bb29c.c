extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov094_020bb29c(int a, int obj) {
    *(int *)(obj + 0xc) = 1;
    func_0202accc(obj + 0x10, 0, obj + 0xf0, 0);
    func_0202accc(obj + 0x10, 2, obj + 0xf0, 0);
    func_01fff774(obj + 0x10, 0, 0);
    func_01fff774(obj + 0x10, 2, 0);
}
