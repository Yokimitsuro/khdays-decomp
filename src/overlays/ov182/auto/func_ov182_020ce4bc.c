struct Inner {
    unsigned char pad[0x17a];
    unsigned char bf17a : 1;
    unsigned char pad17a[0x1c6 - 0x17a - 1];
    signed char b1c6;
    signed char b1c7;
};

struct Mid {
    struct Inner *inner;
};

struct Obj {
    char pad[0x214];
    struct Mid *mid;
};

int func_ov182_020ce4bc(struct Obj *obj) {
    struct Inner *p = obj->mid->inner;
    int a = *((signed char *)p + 0x1c6);
    int b;
    if (a == 0xc) {
        *((signed char *)p + 0x1c7) = 0;
        return 1;
    }
    b = *((signed char *)p + 0x1c7);
    if (b != 0xb && a != 0xb && p->bf17a) {
        if (!(a != 2 && a != 4 && a != 7 && a != 8))
            *((signed char *)p + 0x1c7) = 0xb;
    }
    return 0;
}
