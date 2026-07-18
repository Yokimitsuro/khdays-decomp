extern int func_0202a818(int a, int b);

void func_ov092_020bb064(int a, int *node, int dt) {
    switch (node[0]) {
    default:
        return;
    case 1: {
        int t = node[0x43] + dt;
        node[0x43] = t;
        if (t >= 0x3000) node[0] = 2;
        return;
    }
    case 2: {
        int t = node[0x43] + dt;
        node[0x43] = t;
        if (t >= 0xc000) node[0] = 3;
    }
    case 3:
        if (func_0202a818((int)node + 4, dt) != 0) {
            node[0x43] = 0;
            node[0] = 0;
        }
        return;
    }
}
