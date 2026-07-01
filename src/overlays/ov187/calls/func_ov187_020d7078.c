typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int func_0203c634();

union F {
    u16 w;
    struct {
        u16 lo : 8;
        u16 hi : 8;
    } bf;
};

struct D {
    char pad0[8];
    unsigned int f8 : 8;
};

struct C {
    char pad0[0x60];
    union F f60;
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

void func_ov187_020d7078(struct A *a)
{
    struct B *b = a->b;
    struct D *d;

    b->p0->f60.w = (u16)((b->p0->f60.w & ~0xff00) | (((b->p0->f60.bf.hi | 0xce) & 0xff) << 8));

    b->p0->f1ae = b->p0->f1ae | 1;

    d = b->p0->f388;
    d->f8 = d->f8 & ~1;

    func_0203c634(a, a->f20, 0);
}
