extern void func_01ffa724(int scale, void *src, void *dst);

int func_ov148_020d1cdc(int node, int arg2, unsigned int *arg3) {
    int obj = *(int *)(node + 0x214);
    unsigned int v = (unsigned short)*arg3;
    if ((v & 1) && (v & 0x10)) {
        if (*(int *)(obj + 0x20) != 0) return 0;
        func_01ffa724(-0x1000, (void *)(obj + 0x14), (void *)(obj + 0x14));
        *(int *)(obj + 0x20) = 1;
        *(int *)(obj + 0x24) = 0;
        return 1;
    }
    return 0;
}
