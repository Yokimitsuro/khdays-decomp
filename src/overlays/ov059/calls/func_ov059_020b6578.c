extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov059_020b6578(int a, int obj) {
    *(int *)(obj + 0x234) = 3;
    *(int *)(obj + 0x230) = 0;
    func_0202accc(obj + 0x238, 0, obj + 0x318, 2);
    func_0202accc(obj + 0x238, 2, obj + 0x318, 2);
    func_01fff774(obj + 0x238, 0, 0);
    func_01fff774(obj + 0x238, 2, 0);
}
