extern int func_ov107_020c5af8();
extern int func_0203c634();

struct D {
    char pad0[8];
    unsigned int f8 : 8;
};

struct C {
    char pad0[0x60];
    unsigned short lo8 : 8;
    unsigned short hi8 : 8;
    char pad62[0x165];
    unsigned char f1c7;
    char pad1c8[0x1c0];
    struct D *f388;
};

struct B {
    struct C *p0;
    char pad4[0x40];
    int f44;
};

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov131_020ceabc(struct A *a)
{
    struct B *b = a->b;
    struct C *c;
    struct D *d;

    c = b->p0;
    c->hi8 = c->hi8 & ~1;

    c = b->p0;
    c->hi8 = c->hi8 | 0x86;

    d = b->p0->f388;
    d->f8 = d->f8 & ~1;

    func_ov107_020c5af8(b->p0, b->f44);

    b->p0->f1c7 = 0;

    func_0203c634(a, a->f20, 0);
}
