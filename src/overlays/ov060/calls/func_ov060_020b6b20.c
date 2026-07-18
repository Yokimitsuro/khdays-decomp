extern int func_0202aee0(int a, int b);
extern void func_01fff774(int a, int b, int c);

void func_ov060_020b6b20(int self, int *node) {
    int t;
    if (*(int *)(self + 0x6bc) != 0x30 && node[0] != 0) {
        node[0] = 0;
    }
    if (node[0] != 2) return;
    t = func_0202aee0(*(int *)(self + 0x20) + 4, 0);
    if (t <= 0x1000) return;
    func_01fff774((int)node + 4, 0, t - 0x1000);
    func_01fff774((int)node + 4, 2, t - 0x1000);
    func_01fff774((int)node + 4, 1, t - 0x1000);
}
