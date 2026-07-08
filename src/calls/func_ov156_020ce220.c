extern void func_01ffa724(int scale, void *src, void *dst);

struct bf1 { unsigned char b : 1; };

int func_ov156_020ce220(int node, int arg2, unsigned int *arg3) {
    int obj = *(int *)(node + 0x214);
    if (((unsigned short)*arg3 & 1) == 0) return 0;
    ((struct bf1 *)(obj + 0x24))->b = 1;
    func_01ffa724(-0x1000, (void *)(obj + 0x18), (void *)(obj + 0x18));
    *(int *)(obj + 0x28) = 0;
    *(int *)(node + 0x2e4) = 0x800;
    return 1;
}
