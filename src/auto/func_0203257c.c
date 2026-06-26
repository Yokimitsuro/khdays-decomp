struct Pair {
    int a;
    int b;
};

struct S {
    char pad0[0x10];
    struct Pair p;
    char pad1[0x8c - 0x18];
};

void func_0203257c(struct S *base, int index, struct Pair *src) {
    if (index < 0) return;
    base[index].p = *src;
}
