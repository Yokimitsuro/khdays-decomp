extern int func_0203c650();
extern int func_ov107_020cb100();
extern int func_ov107_020c7ca4();

struct Blk {
    int data[11];
};

struct P398 {
    char pad[0x10];
    struct Blk blk;        /* 0x10 */
};

struct P394 {
    char pad[4];
    struct Blk blk;        /* 0x04 */
};

struct Elem {
    int a;
    int b;
};

struct Obj {
    char pad0[0x3c];
    int f3c;               /* 0x3c */
    char pad40[0x1c4 - 0x40];
    unsigned char f1c4;    /* 0x1c4 */
    char pad1c5;           /* 0x1c5 */
    signed char f1c6;      /* 0x1c6 */
    signed char f1c7;      /* 0x1c7 */
    char pad1c8[0x388 - 0x1c8];
    struct P398 **f388;    /* 0x388 */
    char pad38c[0x394 - 0x38c];
    struct P394 *f394;     /* 0x394 */
    struct P398 *f398;     /* 0x398 */
    struct Elem *f39c;     /* 0x39c */
    int f3a0[2];           /* 0x3a0 */
    int f3a8;              /* 0x3a8 */
};

void func_ov166_020cc624(struct Obj *a) {
    int i;

    if (a->f1c4 & 0xa) {
        if (a->f1c7 == -1) {
            signed char v = a->f1c6;
            if (v != 0 && v != 1 && v != 3 && v != 0xc) {
                a->f1c7 = 0xc;
            }
        }
    }

    if (a->f1c6 != 8 && a->f39c->b != 0) {
        func_0203c650(a->f3c);
        a->f39c->b = 0;
    }

    if (a->f1c6 != 9) {
        for (i = 0; i < 2; i++) {
            if (a->f3a0[i] != 0) {
                func_ov107_020cb100(a->f3a0[i]);
                a->f3a0[i] = 0;
            }
        }
    }

    if (a->f1c6 != 8 && a->f3a8 != 0) {
        func_ov107_020cb100(a->f3a8);
        a->f3a8 = 0;
    }

    a->f398->blk = a->f394->blk;
    (*a->f388)->blk = a->f398->blk;

    func_ov107_020c7ca4(a);
}
