extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);
extern int func_0202a818(int a, int b);

void func_ov074_020b8a3c(int a, int *node, int dt) {
    switch (node[0]) {
    default:
        return;
    case 1: {
        int t = node[0x43] + dt;
        node[0x43] = t;
        if (t < node[0x44]) return;
        func_0202accc((int)node + 4, 0, (int)node + 0xe4, 0);
        func_0202accc((int)node + 4, 2, (int)node + 0xe4, 0);
        func_01fff774((int)node + 4, 0, 0);
        func_01fff774((int)node + 4, 2, 0);
        node[0] = 2;
        node[0x43] = 0;
        return;
    }
    case 2:
        node[0x43] += dt;
        if (func_0202a818((int)node + 4, dt) != 0) {
            node[0] = 0;
        }
        return;
    }
}
