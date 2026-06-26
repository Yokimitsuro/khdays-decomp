extern int func_0203c634();

struct B {
    char *p0;
    char pad[8];
    unsigned char *p1;
};

struct A {
    char f0[4];
    struct B *f4;
    char pad8[0x18];
    signed char f20;
};

int func_ov184_020d2fd8(struct A *a) {
    struct B *b = a->f4;
    if (*b->p1 == 0) {
        b->p0[0x1c7] = 2;
        return func_0203c634(a, a->f20, 0);
    }
}
