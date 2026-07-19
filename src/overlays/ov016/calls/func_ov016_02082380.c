extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);

/* Rebinds the actor model against its own bone table and clears the pending-reload flag. */
void func_ov016_02082380(char *self) {
    func_0202ba9c(self + 0x2c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]),
                  0, self + 0xe0);
    self[0x2bc] = 0;
}
