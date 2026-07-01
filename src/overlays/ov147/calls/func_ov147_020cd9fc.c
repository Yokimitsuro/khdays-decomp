extern int func_0203c634();

struct A {
    char pad0[4];
    char **p;
    char pad8[0x18];
    signed char b;
};

int func_ov147_020cd9fc(struct A *a) {
    (*a->p)[0x1c7] = 0;
    return func_0203c634(a, a->b);
}
