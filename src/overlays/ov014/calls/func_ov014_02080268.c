typedef unsigned short u16;
typedef struct { int x, y, z; } Vec;

extern unsigned int func_020235d0(int bitOffset, int bitCount);
extern void func_ov014_020801d0(int this_);
extern int func_ov002_0206da70(int arg0);
extern void func_0202a634(int this_, int arg1, int arg2, int arg3);
extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);

void func_ov014_02080268(int this_) {
    char *self = (char *)this_;
    int entry = *(int *)(self + 8);
    Vec saved;

    if (*(signed char *)(self + 0x135) == 0) {
        unsigned int state = func_020235d0(*(u16 *)(self + 0x14),
                                            *(unsigned char *)(self + 0x16));
        if ((((state & 0xfffe) << 15) >> 16) == 1)
            func_ov014_020801d0(this_);
    }

    if (*(signed char *)(entry + 0x58) == 0)
        return;

    saved = *(Vec *)(self + 0xd0);
    func_0202a634(this_ + 0x2c, func_ov002_0206da70(entry + 0x58), 1, 4);
    *(Vec *)(self + 0xd0) = saved;
    *(u16 *)(self + 0xa8) = *(u16 *)(self + 0x18);
    *(u16 *)(self + 0x2c) |= 0x20;
    *(u16 *)(self + 0x12) |= 4;
    func_ov002_0207c618((short *)(self + 0x2c), *(signed char *)(self + 0x135), 0);
}
