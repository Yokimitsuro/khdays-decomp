extern int func_01ffa724();
extern int func_0203c634();

struct C {
    char pad0[0x17a];
    unsigned char f17a0 : 1;
    unsigned char f17a_rest : 7;
    unsigned char pad17b;
    unsigned char f17c0 : 1;
    unsigned char f17c_rest : 7;
    char pad17d[0x4a];
    unsigned char f1c7;
};

struct V {
    int a;
    int b;
    int c;
};

struct B {
    struct C *p0;
    char pad4[0x14];
    struct V at20;
    struct V at2c;
    char pad30[0x18];
    unsigned char *f48;
};

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

void func_ov162_020cfbb0(struct A *a)
{
    struct B *b = a->b;
    struct C *c;

    b->at20 = b->at2c;

    func_01ffa724(0xb00, &b->at2c, &b->at2c);

    if (*b->f48 != 0) {
        return;
    }

    c = b->p0;
    if (!c->f17a0) {
        if (!c->f17c0) {
            return;
        }
    }

    c->f1c7 = 2;
    func_0203c634(a, a->f20, 0);
}
