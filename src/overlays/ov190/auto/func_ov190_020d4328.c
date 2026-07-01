struct Obj {
    signed char b[0x1c8];
};

struct Outer {
    struct Obj *obj;
};

struct Root {
    char pad[0x214];
    struct Outer *outer;
};

int func_ov190_020d4328(struct Root *root) {
    struct Obj *obj = root->outer->obj;
    if (obj->b[0x1c7] == -1) {
        obj->b[0x1c7] = 0xb;
        return 1;
    }
    return 0;
}
