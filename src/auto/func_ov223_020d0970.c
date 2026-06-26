struct A {
    char pad[0x1c6];
    signed char b1c6;
    signed char b1c7;
};

struct B {
    char pad[0x214];
    struct A **pp;
};

int func_ov223_020d0970(struct B *x) {
    struct A *a = *x->pp;
    if (a->b1c6 != 14) {
        a->b1c7 = 14;
        return 1;
    }
    return 0;
}
