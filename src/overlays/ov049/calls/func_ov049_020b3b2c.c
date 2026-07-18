extern void func_0202accc(int a, int b, int c, int d);

void func_ov049_020b3b2c(int a, char *node) {
    signed char st = node[0];
    if (st == 0 || st == 5 || st == 6) {
        *(int *)(node + 0x110) = 0;
        *(int *)(node + 0x114) = 0;
        node[0] = 1;
        return;
    }
    if (st != 3) return;
    func_0202accc((int)(node + 4), 0, *(int *)(node + 0x10c), 3);
    func_0202accc((int)(node + 4), 2, *(int *)(node + 0x10c), 3);
    node[0] = 4;
}
