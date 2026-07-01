struct Obj {
    char pad[0x24];
    void (*fn)(struct Obj *, void *, int);
};

struct Buf {
    short a;
    char b;
    char c;
    short rest[17];
};

void func_ov268_020d3b64(struct Obj *obj) {
    struct Buf buf = {0};
    buf.b = 0;
    if (obj->fn != 0) {
        obj->fn(obj, &buf, 0x26);
    }
}
