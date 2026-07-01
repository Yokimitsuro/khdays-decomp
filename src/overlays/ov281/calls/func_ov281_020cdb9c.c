extern int func_0203c634();

struct A {
    char pad0[4];
    struct B *b;
    char pad8[0x18];
    signed char f20;
};

struct B {
    unsigned char *p0;
    struct C *c;
};

struct C {
    unsigned char f0[0xad];
    unsigned char fad;
};

void func_ov281_020cdb9c(struct A *a)
{
    struct B *b = a->b;
    if (b->c->fad != 0)
        return;
    b->p0[0x1c7] = 2;
    func_0203c634(a, a->f20, 0);
}
