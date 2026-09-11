struct T { int a, b, c; };

struct Xform {
    int m0[4];
    int m10[3];
    int f1c;
    int f20;
    int f24;
    unsigned char flags;
};

struct Obj84 {
    char pad[0x74];
    struct T t;
    int f80;
};

extern void func_0203c960(struct Xform *o);
extern void func_0203ca9c(struct Xform *p, int v);
extern void func_0203ca30(struct Xform *dst, struct T *src);
extern void func_0203bc78(void *self, int region);

void func_ov107_020c65d8(void *self, int region)
{
    struct Obj84 *p = *(struct Obj84 **)((char *)self + 0x84);
    struct Xform *xf = (struct Xform *)((char *)self + 0x30);

    if (p == 0) {
        return;
    }
    func_0203c960(xf);
    func_0203ca9c(xf, p->f80 * 2);
    func_0203ca30(xf, &p->t);
    func_0203bc78(self, region);
}
