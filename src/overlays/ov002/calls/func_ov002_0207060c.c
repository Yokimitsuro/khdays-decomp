extern int func_ov002_0207285c(int slot);
extern void func_0202c3e4(unsigned short id, void *a, void *b);

/* Resolves the actor's model id on the first tick and, if it has a bone table, binds it. */
int func_ov002_0207060c(char *self, int phase) {
    int id;
    if (phase == 0) {
        *(short *)(self + 0x1c) = (short)func_ov002_0207285c(*(short *)(self + 0x1a));
        id = *(short *)(self + 0x1c);
        if (id >= 0 && *(signed char *)(self + 0x38) != 0) {
            func_0202c3e4((unsigned short)id, self + 0x38, self + 0x2c);
        }
    }
    return 0;
}
