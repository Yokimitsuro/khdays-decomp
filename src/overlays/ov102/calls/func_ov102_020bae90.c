extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov102_020bae90(int obj) {
    *(int *)(obj + 0x10) = 1;
    *(int *)(obj + 0x11c) = 0;
    func_0202accc(obj + 0x14, 0, obj + 0xf4, 0);
    func_0202accc(obj + 0x14, 2, obj + 0xf4, 0);
    func_01fff774(obj + 0x14, 0, 0);
    func_01fff774(obj + 0x14, 2, 0);
}
