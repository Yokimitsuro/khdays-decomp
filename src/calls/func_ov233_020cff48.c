extern int func_0203c634();

struct H {
    char pad0[0x60];
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct B {
    struct H *h;
    char pad4[0x48];
    int counter;
};

struct T {
    char pad0[0x2c];
    int inc;
};

struct A {
    struct T *t;
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov233_020cff48(struct A *a) {
    struct B *b = a->b;
    b->counter += a->t->inc;
    if (b->counter < 0xd48)
        return;
    b->h->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)((char *)b->h + 0x60);
        unsigned short v = *p;
        unsigned int x = ((((unsigned int)v << 16) >> 24) | 0x80);
        *p = (unsigned short)((v & ~0xff00) | ((x << 24) >> 16));
    }
    *(unsigned char *)((char *)b->h + 0x1c7) = 0;
    func_0203c634(a, a->f20, 0);
}
