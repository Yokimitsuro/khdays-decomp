extern int func_0203c634();

struct D {
    char pad0[8];
    unsigned int f8 : 8;
};

struct C {
    char pad0[0x60];
    unsigned short f60;
    char pad62[0x14c];
    unsigned short f1ae;
    char pad1b0[0x1d8];
    struct D *f388;
};

struct B {
    struct C *p0;
};

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov186_020d1748(struct A *a)
{
    struct B *b = a->b;
    struct C *c;
    struct D *d;
    unsigned int x;

    c = b->p0;
    x = c->f60;
    c->f60 = (x & ~0xff00) | (((((x << 16) >> 24) | 0x86) << 24) >> 16);

    c = b->p0;
    c->f1ae = c->f1ae | 1;

    d = b->p0->f388;
    d->f8 = d->f8 & ~1;

    func_0203c634(a, a->f20, 0);
}
