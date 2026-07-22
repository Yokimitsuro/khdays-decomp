extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern int func_020235d0(unsigned short id, int kind);

/* Rebinds the actor model unless the entity's descriptor says it is a fixed prop. */
void func_ov002_02079224(char *self) {
    int flags;
    int kind = *(unsigned char *)(self + 0x16);
    if (kind == 2) {
        flags = 0;
    } else {
        flags = (unsigned int)((func_020235d0(*(unsigned short *)(self + 0x14), kind) & 0xfffe) << 0xf)
                >> 0x10 & 2;
    }
    if (flags != 0) {
        return;
    }
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
}
