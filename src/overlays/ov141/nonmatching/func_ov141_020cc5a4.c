extern int func_0203c650();
extern int func_ov107_020c7ca4();
extern int func_ov107_020cb100();

struct Blk {
    int data[11];
};

struct P398 {
    char pad[4];
    struct Blk blk;        /* 0x04 */
};

struct P388 {
    char pad[0x10];
    struct Blk blk;        /* 0x10 */
};

struct Sub {
    char pad0[0xc];
    int m0c;               /* 0x0c */
    char pad1[0x14 - 0x10];
    int m14;               /* 0x14 */
    char pad2[0x1c - 0x18];
    int m1c;               /* 0x1c */
    char pad3[0x24 - 0x20];
    int m24;               /* 0x24 */
};

struct Obj {
    char pad0[0x3c];
    int f3c;               /* 0x3c */
    char pad40[0x1c6 - 0x40];
    signed char f1c6;      /* 0x1c6 */
    char pad1c7[0x388 - 0x1c7];
    struct P388 **f388;    /* 0x388 */
    struct P388 *f38c;     /* 0x38c */
    struct Sub *f390;      /* 0x390 */
    char pad394[0x398 - 0x394];
    struct P398 *f398;     /* 0x398 */
    char pad39c[0x3d0 - 0x39c];
    int f3d0;              /* 0x3d0 */
};

void func_ov141_020cc5a4(struct Obj *a) {
    if (a->f1c6 != 5) {
        if (a->f390->m0c != 0) {
            func_0203c650(a->f3c);
            a->f390->m0c = 0;
        }
        if (a->f390->m14 != 0) {
            func_0203c650(a->f3c);
            a->f390->m14 = 0;
        }
        if (a->f390->m1c != 0) {
            func_0203c650(a->f3c);
            a->f390->m1c = 0;
        }
        if (a->f3d0 != 0) {
            func_ov107_020cb100();
            a->f3d0 = 0;
        }
    }

    if (a->f1c6 != 6 && a->f390->m24 != 0) {
        func_0203c650(a->f3c);
        a->f390->m24 = 0;
    }

    (*a->f388)->blk = a->f398->blk;
    a->f38c->blk = a->f398->blk;

    func_ov107_020c7ca4(a);
}
