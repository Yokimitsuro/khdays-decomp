extern int func_ov002_0207285c(int slot);

/* Resolves the actor's model index into the low 7 bits of the flags byte; 0x7f means "none". */
int func_ov002_020710f4(char *self, int phase) {
    if (phase == 0) {
        *(char *)(self + 0x15) = (char)((*(signed char *)(self + 0x15) & ~0x7f) | 0x7f);
        if (*(signed char *)(self + 0x14) >= 0) {
            *(char *)(self + 0x15) = (char)((*(signed char *)(self + 0x15) & ~0x7f)
                | ((signed char)func_ov002_0207285c(*(signed char *)(self + 0x14)) & 0x7f));
        }
    }
    return 0;
}
