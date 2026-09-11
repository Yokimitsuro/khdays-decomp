extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *obj, int index, int p3, void *p4);

void func_ov021_02080738(char *self) {
    func_0202ba9c(self + (0x49 << 2),
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]),
                  0, 0);
}
