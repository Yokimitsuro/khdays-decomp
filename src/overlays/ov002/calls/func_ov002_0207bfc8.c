extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern int func_ov002_02074460(int id);
extern void func_ov002_02073ed0(int id, int a, int b);

/* Rebinds the actor model and, if it has a live link target, re-attaches to it. */
void func_ov002_0207bfc8(char *self) {
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    *(unsigned short *)(self + 0x12) &= ~8;
    if (*(unsigned char *)(self + 0x2c1) == 4) {
        return;
    }
    if (*(short *)(self + 0x2c4) < 0) {
        return;
    }
    if (func_ov002_02074460(*(short *)(self + 0x2c4)) < 0) {
        return;
    }
    func_ov002_02073ed0(*(short *)(self + 0x2c4), 0, -1);
    *(unsigned short *)(self + 0x12) |= 8;
}
