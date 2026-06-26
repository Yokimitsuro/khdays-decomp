extern int func_01ffa724();
extern int func_0203c634();

struct Vec3 {
    unsigned int a, b, c;
};

struct Big {
    char pad17a[0x17a];
    unsigned char f17a : 1;   /* +0x17a bit0 */
    char pad17b[0x17c - 0x17b];
    unsigned char f17c : 1;   /* +0x17c bit0 */
    char pad17d[0x1c7 - 0x17d];
    unsigned char f1c7;       /* +0x1c7 */
};

struct Inner {
    struct Big *p0;           /* +0x00 */
    unsigned char *p4;        /* +0x04 */
    char pad8[0x18 - 0x08];
    struct Vec3 dst;          /* +0x18 */
    struct Vec3 src;          /* +0x24 */
};

struct Obj {
    char pad0[4];
    struct Inner *inner;      /* +0x04 */
    char pad8[0x20 - 0x08];
    signed char b20;          /* +0x20 */
};

void func_ov134_020ccff8(struct Obj *o) {
    struct Inner *in = o->inner;
    struct Big *q;

    in->dst = in->src;
    func_01ffa724(0xb00, &in->src, &in->src);

    if (in->p4[0xad] != 0)
        return;

    q = in->p0;
    if (q->f17a == 0 && q->f17c == 0)
        return;

    q->f1c7 = 2;
    func_0203c634(o, (int)o->b20, 0);
}
