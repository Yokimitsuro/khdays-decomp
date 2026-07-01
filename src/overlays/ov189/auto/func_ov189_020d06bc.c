struct S {
    char pad[0x1c6];
    signed char b1c6;
    signed char b1c7;
};

struct U {
    struct S *p;
};

struct T {
    char pad[0x214];
    struct U *u;
};

int func_ov189_020d06bc(struct T *t) {
    struct S *s = t->u->p;
    if (s->b1c6 != 0xa) {
        s->b1c7 = 0xa;
        return 1;
    }
    return 0;
}
