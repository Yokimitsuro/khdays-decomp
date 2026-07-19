extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_02029438(void *p, int i, unsigned char v);

/* Rebinds the actor model unless it is flagged hidden, then applies the owner's palette index. */
void func_ov002_0207a4b8(char *self) {
    char *owner = *(char **)(self + 8);
    int palette;
    if ((*(unsigned short *)(self + 0x12) & 2) != 0) {
        return;
    }
    func_0202ba9c(self + 0x1c,
                  (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    palette = *(signed char *)(owner + 0x7a);
    if (palette < 0) {
        return;
    }
    func_02029438(self + 0x138, 3, (unsigned char)palette);
}
