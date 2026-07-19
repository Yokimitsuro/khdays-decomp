extern int func_ov002_0207285c(int slot);
extern int func_020235d0(unsigned short id, unsigned char kind);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_02029438(void *p, int i, unsigned char v);

static inline int Ov002_IsAnimated(unsigned short id, unsigned char kind) {
    return (func_020235d0(id, kind) & 1) != 0;
}

/* Rebinds the actor model for entities whose descriptor is flagged animated, unless the actor is
 * already in state 7. */
void func_ov002_02079f50(char *self) {
    if (Ov002_IsAnimated(*(unsigned short *)(self + 0x14), (unsigned char)self[0x16])) {
        if (*(unsigned char *)(self + 0x1b4) == 7) {
            return;
        }
        func_0202ba9c(self + 0x2c,
                      (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
        func_02029438(self + 0x148, 1, 3);
    }
}
