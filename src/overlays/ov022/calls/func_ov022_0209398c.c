extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov022_0209398c(int arg0, int arg1) {
    int p = arg1 * 0x108 + (arg0 + 0x20);
    func_0202accc(p, 0, p + 0xe0, 0);
    func_0202accc(p, 3, p + 0xe0, 0);
    func_0202accc(p, 2, arg1 * 0x24 + (arg0 + 0x440), 0);
    func_01fff774(p, 0, 0);
    func_01fff774(p, 3, 0);
    func_01fff774(p, 2, 0);
}
