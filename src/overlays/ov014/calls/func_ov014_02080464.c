extern int func_02030670(void);
extern int func_ov002_0206b758(void);
extern int func_ov014_02080344(void *self);
extern int func_01fffe14(void);
extern int func_01fffde0(int index);
extern void func_ov022_020ad2e4(int arg0, int arg1);
extern void func_ov014_020801d0(int this_);
extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202aa9c(void *object);
extern int func_ov014_02080520(int this_);

void *func_ov014_02080464(void *self)
{
    void *next = 0;
    int state;

    if (func_02030670() == 0 && (*(unsigned short *)((char *)self + 0x12) & 2) == 0)
        return 0;

    if (func_ov002_0206b758() != 0 && func_ov014_02080344(self) != 0) {
        func_ov022_020ad2e4(func_01fffde0(func_01fffe14()), 1);
    }

    state = *(signed char *)((char *)self + 0x134);
    if (state != 2) {
        if (state == 3)
            next = (void *)&func_ov014_02080520;
    } else {
        func_ov014_020801d0((int)self);
        if (*(unsigned short *)((char *)self + 0x12) & 4)
            func_ov002_0207c618((short *)((char *)self + 0x2c),
                                *(signed char *)((char *)self + 0x135), 0);
        next = (void *)&func_ov014_02080520;
    }

    if (*(unsigned short *)((char *)self + 0x12) & 4)
        func_0202aa9c((char *)self + 0x2c);
    return next;
}
