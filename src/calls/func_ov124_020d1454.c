extern void func_01ffa724(int scale, void *src, void *dst);

int func_ov124_020d1454(int node, int arg2, unsigned int *arg3) {
    int obj = *(int *)(node + 0x214);
    if ((unsigned short)*arg3 & 1) {
        if (*(int *)(obj + 0x24) != 0) return 0;
        func_01ffa724(-0x1000, (void *)(obj + 0x18), (void *)(obj + 0x18));
        *(int *)(obj + 0x24) = 1;
        *(int *)(obj + 0x28) = 0;
        return 1;
    }
    return 0;
}
