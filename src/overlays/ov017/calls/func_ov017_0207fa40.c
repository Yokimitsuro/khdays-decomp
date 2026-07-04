extern void func_ov002_0207c618();
extern void func_0202af1c();

void func_ov017_0207fa40(int this_, int arg1, int arg2, int arg3, int arg4) {
    *(int *)(this_ + 0x4cc) = arg3;
    *(int *)(this_ + 0x4c8) = arg4;
    if ((*(unsigned short *)(this_ + 0x12) & 4) == 0) return;
    func_ov002_0207c618(arg1, arg2, 0);
    func_0202af1c(arg1);
}
