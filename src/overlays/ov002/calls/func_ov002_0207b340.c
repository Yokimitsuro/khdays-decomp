extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);

/* Rebinds the actor model when its owner entity is still alive. */
void func_ov002_0207b340(char *self) {
    if (*(signed char *)(*(char **)(self + 8) + 0x58) != 0) {
        func_0202ba9c(self + 0x2c,
                      (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    }
}
