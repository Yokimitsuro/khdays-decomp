extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov040_020b3d18(int a, int obj) {
    *(int *)(obj + 0x234) = 1;
    *(int *)(obj + 0x230) = 0;
    func_0202accc(obj + 0x238, 0, obj + 0x318, 0);
    func_0202accc(obj + 0x238, 2, obj + 0x318, 0);
    func_01fff774(obj + 0x238, 0, 0);
    func_01fff774(obj + 0x238, 2, 0);
}
