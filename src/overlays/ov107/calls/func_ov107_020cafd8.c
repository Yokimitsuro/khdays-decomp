extern void func_ov107_020c4d9c(void *self);

void func_ov107_020cafd8(char *self) {
    *(int *)(self + 0x1e4) = 0;
    char *p = *(char **)(self + 0x18c);
    if (p != 0) {
        int v = *(int *)(p + 0x2abc);
        if (*(int *)(self + 0x1b8) != v || (*(unsigned short *)(p + 0x18) & 0x803) != 0) {
            *(int *)(self + 0x1b8) = v;
            *(int *)(self + 0x1e4) |= 0x10;
        } else {
            *(int *)(self + 0x1e4) &= ~0x10;
        }
    }
    func_ov107_020c4d9c(self);
}
