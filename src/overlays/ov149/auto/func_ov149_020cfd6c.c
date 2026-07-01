struct Vec3 {
    int x;
    int y;
    int z;
};

struct Src {
    int *base;
    int pad;
    struct Vec3 data;
};

struct Outer {
    int pad0;
    struct Src *src;
};

void func_ov149_020cfd6c(struct Outer *p) {
    struct Src *s = p->src;
    *(struct Vec3 *)((char *)s->base + 0xf0) = s->data;
}
