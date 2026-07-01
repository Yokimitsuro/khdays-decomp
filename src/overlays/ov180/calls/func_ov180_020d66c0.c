extern int func_0203c634();

struct Inner {
    char *p0;
    char *p1;
};

struct Obj {
    char pad0[4];
    struct Inner *inner;
    char pad1[0x20 - 8];
    signed char b20;
};

void func_ov180_020d66c0(struct Obj *obj) {
    struct Inner *inner = obj->inner;
    if (*(unsigned char *)(inner->p1 + 0xad) != 0) {
        return;
    }
    *(char *)(inner->p0 + 0x1c7) = 0;
    func_0203c634(obj, obj->b20);
}
