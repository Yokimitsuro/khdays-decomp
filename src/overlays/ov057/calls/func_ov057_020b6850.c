extern int func_0202a818(int a, int b);
extern void func_ov057_020b6af4(int a, int b);
extern int data_ov057_020b74a0;

void func_ov057_020b6850(int self, int *node, int dt) {
    char *blk = (char *)(*(int *)&data_ov057_020b74a0 + 0x2c + 0x2c00);
    if (node[0] == 1) {
        int st = *(int *)(self + 0x6bc);
        if (st != 0x2f && st != 0x32) node[0] = 0;
    }
    switch (node[0]) {
    default:
        return;
    case 1:
        if (*(int *)(self + 0x7b0) >= 0x12000) node[0] = 2;
        return;
    case 2:
        if (func_0202a818((int)node + 4, dt) == 0) return;
        func_ov057_020b6af4(self, (int)(blk + 0x118));
        node[0] = 0;
        return;
    }
}
