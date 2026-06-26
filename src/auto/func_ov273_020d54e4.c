struct Buf {
    short a;
    char b;
    char rest[33];
};

struct S {
    char pad[0x24];
    void (*fn)(struct S *, void *, int);
};

void func_ov273_020d54e4(struct S *a) {
    struct Buf buf = {0};
    buf.b = 0;
    if (a->fn) {
        a->fn(a, &buf, 0x24);
    }
}
