extern void MI_Copy48B(int dst, int src);
extern void func_01ff9f00(int a, void *b, int c);
extern void func_0201571c(void);
extern void func_020279e0(int a);

void func_ov041_020b4224(int self, int *blk) {
    int tmp[3];
    if (*blk != 2 && *blk != 3 && *blk != 4) return;
    MI_Copy48B(self + 0x158 + 0x400, (int)blk + 0x84);
    {
        int v = *(int *)(blk[10] + 0x1c);
        tmp[0] = v;
        tmp[1] = v;
        tmp[2] = v;
        func_01ff9f00(0x1b, tmp, 3);
    }
    func_0201571c();
    func_01ff9f00(0x17, (void *)((int)blk + 0x84), 0xc);
    func_020279e0((int)blk + 0x24);
}
