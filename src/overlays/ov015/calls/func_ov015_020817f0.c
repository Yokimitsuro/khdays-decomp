extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202af1c(unsigned short *p);

void func_ov015_020817f0(int this_, short *arg1, int arg2, int arg3) {
    unsigned short flags = *(unsigned short *)(this_ + 0x12);
    if ((flags & 4) && (flags & 4)) {
        func_ov002_0207c618(arg1, arg2, arg3);
        func_0202af1c((unsigned short *)arg1);
    }
}
