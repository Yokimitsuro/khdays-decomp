struct A {
    signed char b[0x1c8];
};

struct B {
    struct A *a;
};

struct C {
    char pad[0x214];
    struct B *b;
};

int func_ov248_020cd068(struct C *p) {
    struct A *a = p->b->a;
    if (a->b[0x1c7] == -1) {
        a->b[0x1c7] = 0xd;
        return 1;
    }
    return 0;
}
