extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov064_020b69c8(int a, char *node) {
    signed char st = node[0];
    if (st == 0 || st == 4 || st == 5) {
        func_0202accc((int)(node + 4), 0, (int)(node + 0xe4), 0);
        func_0202accc((int)(node + 4), 2, (int)(node + 0xe4), 0);
        func_01fff774((int)(node + 4), 0, 0);
        func_01fff774((int)(node + 4), 2, 0);
        *(int *)(node + 0x10c) = 0;
        *(int *)(node + 0x110) = 0;
        node[0] = 1;
    }
}
