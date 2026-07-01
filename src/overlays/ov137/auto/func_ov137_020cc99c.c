struct Sub {
    signed char pad[0x1c6];
    signed char b1c6;
    signed char b1c7;
};

struct Mid {
    struct Sub *sub;
};

struct Obj {
    char pad[0x214];
    struct Mid *mid;
};

int func_ov137_020cc99c(struct Obj *obj) {
    struct Sub *s = obj->mid->sub;
    int v = s->b1c6;
    if (v == 6 || v == 7) {
        return 0;
    }
    if (s->b1c7 != -1) {
        return 0;
    }
    s->b1c7 = 8;
    return 1;
}
