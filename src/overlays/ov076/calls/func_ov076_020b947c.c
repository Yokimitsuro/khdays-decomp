extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov076_020b947c(int a, int obj) {
    char *p = (char *)obj;
    *(int *)(p + 0x11c) = 2;
    func_0202accc((int)(p + 0x120), 0, (int)(p + 0x200), 0);
    func_0202accc((int)(p + 0x120), 2, (int)(p + 0x200), 0);
    func_0202accc((int)(p + 0x120), 1, (int)(p + 0x200), 0);
    func_01fff774((int)(p + 0x120), 0, 0);
    func_01fff774((int)(p + 0x120), 2, 0);
    func_01fff774((int)(p + 0x120), 1, 0);
}
