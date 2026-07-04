extern void func_ov002_0207c618();
extern void func_0202af1c();

void func_ov014_0207fa40(int this_, int arg1) {
    *(unsigned char *)(this_ + 0x1b1) |= 2;
    if ((*(unsigned short *)(this_ + 0x12) & 4) == 0) return;
    func_ov002_0207c618(this_ + 0x3c, arg1, 0);
    func_0202af1c(this_ + 0x3c);
}
