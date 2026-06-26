extern int func_01ffa724();
extern int func_0203c634();

struct C {
    char pad0[0x60];
    unsigned short lo8 : 8;
    unsigned short hi8 : 8;
    char pad62[0x118];
    unsigned char f17a0 : 1;
    unsigned char f17a_rest : 7;
    unsigned char pad17b;
    unsigned char f17c0 : 1;
    unsigned char f17c_rest : 7;
    char pad17d[0x4a];
    unsigned char f1c7;
};

struct E {
    char pad0[0xad];
    unsigned char fad;
};

struct V {
    int a;
    int b;
    int c;
};

struct B {
    struct C *p0;
    struct E *f4;
    char pad8[0x18];
    struct V at20;
    struct V at2c;
    char pad38[0x20];
    int f58;
    char pad5c[0x2c];
    int f88;
};

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov171_020cddb4(struct A *a)
{
    struct B *b = a->b;

    b->at20 = b->at2c;

    func_01ffa724(0xb00, &b->at2c, &b->at2c);

    if (b->f88 == 0 && b->at20.b < 0x20) {
        b->p0->hi8 = b->p0->hi8 & ~0x40;
    }

    if (b->f88 == 0 && !b->p0->f17a0) {
        if (!b->p0->f17c0) {
            return;
        }
    }

    if (b->f4->fad != 0) {
        return;
    }

    if (b->f58 > 0) {
        b->p0->f1c7 = 11;
        func_0203c634(a, a->f20, 0);
    } else {
        b->p0->f1c7 = 5;
        func_0203c634(a, a->f20, 0);
    }
}
