extern int func_0203c634();
extern int func_ov138_020d2a9c();

struct Vec3 { int x, y, z; };
extern const struct Vec3 data_02041dc8;

struct D {
    char pad0[8];
    unsigned int f8 : 8;
};

struct C {
    char pad0[0x60];
    unsigned short f60;
    char pad62[0x326];
    struct D *f388;
};

struct B {
    struct C *p0;
    char pad4[4];
    struct Vec3 v8;
};

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov138_020d29ec(struct A *a)
{
    struct B *b = a->b;
    struct C *c;
    struct D *d;
    unsigned int x;


    c = b->p0;
    x = c->f60;
    c->f60 = (x & ~0xff00) |
             (((unsigned int)(unsigned short)(((x << 16) >> 24) & ~1) << 24) >> 16);

    c = b->p0;
    x = c->f60;
    c->f60 = (x & ~0xff00) | (((((x << 16) >> 24) | 0x82) << 24) >> 16);

    d = b->p0->f388;
    d->f8 = d->f8 & ~1;

    b->v8 = data_02041dc8;

    func_0203c634(a, a->f20, func_ov138_020d2a9c);
}
