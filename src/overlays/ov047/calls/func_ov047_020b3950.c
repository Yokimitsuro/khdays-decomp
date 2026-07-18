extern void func_0202a818(int a, int b);

void func_ov047_020b3950(int self, int *node, int dt) {
    if (node[4] != 0 && *(int *)(self + 0x6bc) != 0x31) {
        node[4] = 0;
    }
    switch (node[4]) {
    default:
        return;
    case 1: {
        int t = node[0x47] + dt;
        node[0x47] = t;
        if (t >= 0x12000) node[4] = 2;
        return;
    }
    case 2:
        func_0202a818((int)node + 0x14, dt);
        return;
    }
}
