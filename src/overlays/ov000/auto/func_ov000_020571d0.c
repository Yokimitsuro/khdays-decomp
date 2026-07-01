struct S {
    int key;
    char _pad[4];
    int b8;
    char _pad2[0xdc - 0xc];
};

int func_ov000_020571d0(int a, struct S *p) {
    int i;
    int ret = 0;
    for (i = 0; i < 5; i++) {
        if (a == p[i + 1].key) {
            ret = p[i + 1].b8 & 0xff;
            break;
        }
    }
    return ret;
}
