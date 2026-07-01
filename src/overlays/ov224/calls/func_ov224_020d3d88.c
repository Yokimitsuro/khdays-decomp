extern int func_0203c634();

struct C {
    char pad0[0x60];
    unsigned short lo : 8;
    unsigned short hi : 8;
    char pad62[0x165];
    unsigned char f1c7;
};

struct E {
    char pad0[0x2c];
    int f2c;
};

struct B {
    struct C *p0;
    char pad4[0x58];
    int f5c;
};

struct A {
    struct E *f0;
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov224_020d3d88(struct A *a)
{
    struct B *b = a->b;

    b->f5c += a->f0->f2c;
    if (b->f5c < 3400)
        return;

    b->p0->hi |= (unsigned char)0x80;
    b->p0->hi &= ~1;

    b->p0->f1c7 = 0;

    func_0203c634(a, a->f20, 0);
}
