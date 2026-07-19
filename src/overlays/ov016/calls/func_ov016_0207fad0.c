extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);

extern void func_02029438(void *p, int a, int b);

/* Rebinds the actor model and restarts its idle animation. */
void func_ov016_0207fad0(char *self) {
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    func_02029438(self + 0x148, 3, 1);
}
