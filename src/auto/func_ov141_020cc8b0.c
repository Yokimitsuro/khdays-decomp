struct Inner {
    signed char pad[0x1c7];
    signed char flag;
};

struct Outer {
    struct Inner *inner;
};

struct Root {
    char pad[0x214];
    struct Outer *outer;
};

int func_ov141_020cc8b0(struct Root *root) {
    struct Inner *inner = root->outer->inner;
    if (inner->flag == -1) {
        inner->flag = 8;
        return 1;
    }
    return 0;
}
