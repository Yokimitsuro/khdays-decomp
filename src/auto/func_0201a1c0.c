struct Inner {
    char pad[0x34];
    short f34;
    short pad36;
    short f38;
};

struct Outer {
    struct Inner *volatile inner;
};

void func_0201a1c0(struct Outer *a, short val) {
    if (a->inner == 0) return;
    a->inner->f34 = 1;
    a->inner->f38 = val;
}
