extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

struct X {
    int f_0;
    int f_4;
    int f_8;
    int f_c;
    char _10[8];
    unsigned int flags;
};

void func_02035fb0(struct X *p, int a1, int a2, int a3, int a4) {
    MI_CpuFill8(p, 0, 0x1c);
    p->f_0 = a1;
    p->f_8 = a2;
    p->f_c = a3;
    p->f_4 = a4;
    p->flags &= ~1;
    p->flags &= ~2;
    p->flags &= ~4;
}
