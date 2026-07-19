extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_02029438(void *p, int i, unsigned char v);

/* Rebinds the actor model and picks its idle variant from the owner's kind. */
void func_ov002_02076f4c(char *self) {
    char *owner = *(char **)(self + 8);
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    if (*(short *)(owner + 0x68) == 0x2b) {
        func_02029438(self + 0x148, 3, 2);
    } else {
        func_02029438(self + 0x148, 3, 1);
    }
}
