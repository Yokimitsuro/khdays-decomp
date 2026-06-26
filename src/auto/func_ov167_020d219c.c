struct Vec3 { int x, y, z; };

struct Inner {
    struct Vec3 *dst;
    int pad[2];
    struct Vec3 src;
};

struct Outer {
    int pad;
    struct Inner *inner;
};

void func_ov167_020d219c(struct Outer *a) {
    struct Inner *p = a->inner;
    struct Vec3 *dst = p->dst;
    *(struct Vec3 *)((char *)dst + 0xf0) = p->src;
}
