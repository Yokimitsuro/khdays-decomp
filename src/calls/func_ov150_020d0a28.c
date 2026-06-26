extern int func_0203c634();

struct Inner {
    unsigned char *ptr0;
    char pad4[0x40];
    unsigned char *ptr44;
};

struct Obj {
    char pad0[4];
    struct Inner *inner;
    char pad8[0x18];
    signed char b20;
};

void func_ov150_020d0a28(struct Obj *obj) {
    struct Inner *inner = obj->inner;
    if (inner->ptr44[0] != 0) {
        return;
    }
    inner->ptr0[0x1c7] = 2;
    func_0203c634(obj, obj->b20, 0);
}
