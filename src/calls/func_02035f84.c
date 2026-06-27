extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

struct X {
    char _0[0x18];
    unsigned int flags;
};

void func_02035f84(struct X *p) {
    MI_CpuFill8(p, 0, 0x1c);
    p->flags &= ~1;
    p->flags &= ~2;
    p->flags |= 4;
}
