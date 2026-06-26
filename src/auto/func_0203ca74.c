struct Vec3 { int x, y, z; };

struct Obj {
    char pad[0x1c];
    struct Vec3 v;
    unsigned char flags;
};

void func_0203ca74(struct Obj *o, struct Vec3 *src) {
    o->v = *src;
    o->flags &= ~1;
    o->flags &= ~2;
}
