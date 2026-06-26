struct Inner {
    char pad[0x60];
    unsigned short field60 : 8;
};

struct Mid {
    char pad[0x3ac];
    struct Inner *p3ac[1];
};

struct Base {
    struct Mid *p0;
};

struct Outer {
    char pad[4];
    struct Base *p4;
};

int func_ov168_020d4320(struct Outer *a) {
    struct Base *b = a->p4;
    int i;
    for (i = 0; i < 1; i++) {
        struct Mid *m = b->p0;
        if (!(m->p3ac[i]->field60 & 1)) {
            return 1;
        }
    }
    return 0;
}
