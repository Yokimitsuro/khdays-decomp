extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, int id, int a, void *b);
extern int func_ov002_02074460(int id);
extern void func_ov002_02073ed0(int id, int a, int b);

void func_ov014_0207fb88(char *self) {
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]),
                  0, 0);
    if (*(unsigned char *)(self + 0x1b1) & 0x80) {
        return;
    }
    if (*(short *)(self + 0x1d0) < 0) {
        return;
    }
    if (func_ov002_02074460(*(short *)(self + 0x1d0)) < 0) {
        return;
    }
    func_ov002_02073ed0(*(short *)(self + 0x1d0), 0, -1);
}
