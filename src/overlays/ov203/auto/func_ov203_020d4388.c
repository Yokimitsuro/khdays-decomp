struct Inner {
    char pad[0x1c6];
    signed char field_1c6;
    signed char field_1c7;
};

struct Mid {
    struct Inner *inner;
};

struct Outer {
    struct Mid *mid;
};

int func_ov203_020d4388(struct Outer *a) {
    struct Mid *mid = *(struct Mid **)((char *)a + 0x214);
    struct Inner *inner = mid->inner;
    signed char c = inner->field_1c6;
    if (!(c != 7 && c != 8)) {
        return 0;
    }
    if (inner->field_1c7 == -1) {
        inner->field_1c7 = 10;
        return 1;
    }
    return 0;
}
