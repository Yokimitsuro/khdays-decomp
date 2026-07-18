/* ⚠ Written with STRUCT TYPES and named fields, not pointer casts, and with `c = b->p0`
 * reloaded before each hw60 block. That is not cosmetic: the cast-based version is
 * byte-for-byte the same size but schedules the vec3 ldm at the END, while the ROM (and
 * this form) hoists it above the hw60 work. House style copied from ov149_020cfd84. */
struct Vec3 { int x, y, z; };
extern const struct Vec3 data_02041dc8;
extern void func_0203c634();
extern void func_ov197_020ce380(void);

struct D { char pad0[8]; unsigned int f8 : 8; };
struct C { char pad0[0x60]; unsigned short f60; char pad62[0x326]; struct D *f388; };
struct B { struct C *p0; char pad4[4]; struct Vec3 v8; };
struct A { char pad0[4]; struct B *b; char pad8[0x18]; signed char f20; };

void func_ov197_020ce2c4(struct A *a) {
    struct B *b = a->b;
    struct C *c;
    struct D *d;
    unsigned int x;

    *(int *)((char *)b->p0 + 0x38c) = 0;

    c = b->p0;
    x = c->f60;
    c->f60 = (x & ~0xff00) | (((((x << 16) >> 24) | 0x80) << 24) >> 16);

    c = b->p0;
    x = c->f60;
    c->f60 = (x & ~0xff00) |
             (((unsigned int)(unsigned short)(((x << 16) >> 24) & ~1) << 24) >> 16);

    d = b->p0->f388;
    d->f8 = d->f8 & ~1;

    b->v8 = data_02041dc8;

    func_0203c634(a, a->f20, func_ov197_020ce380);
}
