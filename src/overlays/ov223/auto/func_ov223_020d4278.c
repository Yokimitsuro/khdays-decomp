/* Broadcasts an empty 46-byte kind-0 message through the actor's +0x24 hook when one is set. */
struct Obj {
    char pad[0x24];
    void (*fn)(struct Obj *, void *, int);
};

struct Buf {
    short a;
    char b;
    char c;
    short rest[21];
};

void func_ov223_020d4278(struct Obj *obj) {
    struct Buf buf = {0};
    buf.b = 0;
    if (obj->fn != 0) {
        obj->fn(obj, &buf, 0x2e);
    }
}
