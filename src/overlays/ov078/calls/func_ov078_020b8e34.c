extern int func_ov022_020923dc(int a, int b);
extern void func_01fff774(int a, int b, int c);

void func_ov078_020b8e34(int self, signed char *node, int dt) {
    int st;
    if (func_ov022_020923dc(self + 0x248 + 0x2400, 5) == 0) {
        node[1] = 0;
    }
    st = *(int *)(self + 0x6bc);
    if (st != 0x2f && st != 0x32) {
        node[1] = 0;
    }
    switch (node[1]) {
    default:
        return;
    case 1:
        if (*(int *)(self + 0x7b0) >= 0x9000) node[1] = 2;
        return;
    case 2:
        func_01fff774((int)node + 4, 2, *(int *)(self + 0x7b0) - 0x9000 + dt);
        return;
    }
}
