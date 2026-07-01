extern int func_0203c634();

struct Inner {
    unsigned char *field_0;
    unsigned char *field_4;
};

struct Obj {
    int field_0;
    struct Inner *field_4;
};

void func_ov245_020cd924(struct Obj *a) {
    struct Inner *inner = a->field_4;
    if (inner->field_4[0xad] != 0) {
        return;
    }
    inner->field_0[0x1c7] = 4;
    func_0203c634(a, *(signed char *)((char *)a + 0x20), 0);
}
