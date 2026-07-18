extern int func_0202aee0(int a, int b);
extern void func_01fff774(int a, int b, int c);

void func_ov037_020b461c(int self, char *blk) {
    int st = *(int *)(self + 0x6bc);
    int t;
    if (st != 0x2f && st != 0x30 && *(int *)(blk + 0x11c) != 0) {
        *(int *)(blk + 0x11c) = 0;
    }
    if (*(int *)(blk + 0x11c) != 2) return;
    t = func_0202aee0(*(int *)(self + 0x20) + 4, 0);
    if (t <= 0x1000) return;
    func_01fff774((int)(blk + 0x120), 0, t - 0x1000);
    func_01fff774((int)(blk + 0x120), 2, t - 0x1000);
    func_01fff774((int)(blk + 0x120), 1, t - 0x1000);
}
