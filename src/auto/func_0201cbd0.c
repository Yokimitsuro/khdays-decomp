struct Inner {
    int dummy[83];
    int field_14c;
};

struct Outer {
    struct Inner *ptr;
};

void func_0201cbd0(struct Outer *p) {
    struct Inner *inner = p->ptr;
    if (inner) {
        inner->field_14c = 0;
        p->ptr = 0;
    }
}
