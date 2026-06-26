extern int VEC_Subtract();
extern int func_020050b4();
extern int func_01ff8d18();
extern int func_01ffa724();
extern int MTX_RotY33_();
extern int MTX_MultVec33();
extern int func_0203c634();
extern short data_0203d210[];

struct sub {
    int f0;       /* +0x00 */
    int pad04;    /* +0x04 */
    int f8;       /* +0x08 */
    char pad0c[0x80 - 0x0c];
    int f80;      /* +0x80 */
    char pad84[0x190 - 0x84];
    char f190[1]; /* +0x190 */
    char pad191[0x1c7 - 0x191];
    unsigned char f1c7; /* +0x1c7 */
    char pad1c8[0x3fc - 0x1c8];
    int f3fc;     /* +0x3fc */
};

struct mid {
    struct sub *f0;   /* +0x00 */
    int pad04;        /* +0x04 */
    int f8;           /* +0x08 */
    char pad0c[0x14 - 0x0c];
    char f14[1];      /* +0x14 */
    char pad15[0x58 - 0x15];
    int f58;          /* +0x58 */
    char pad5c[0x78 - 0x5c];
    int f78;          /* +0x78 */
};

struct top {
    char pad0[0x04];
    struct mid *f4;   /* +0x04 */
    char pad08[0x20 - 0x08];
    signed char f20;  /* +0x20 */
};

void func_ov221_020d3e24(struct top *a)
{
    struct mid *r4 = a->f4;
    int s24[3];
    int s0[9];
    int diff;

    struct sub *sub0;

    VEC_Subtract((char *)r4->f0 + 0x190, r4->f8, s24);
    r4->f58 = func_020050b4(s24[0], s24[2]);
    sub0 = r4->f0;
    diff = func_01ff8d18(s24, s24) - sub0->f80;

    if (r4->f78 != 0) {
        func_01ffa724(0x100, s24, r4->f14);
    } else {
        long long p = (long long)r4->f58 * 0x28be60db9391LL + 0x80000000000LL;
        int h = (int)(p >> 32);
        int idx = (int)((unsigned)h << 4 >> 16) >> 4;
        MTX_RotY33_(s0, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(r4->f0->f3fc + 0x2c, s0, r4->f14);
    }

    if (diff < 0x2000) {
        r4->f0->f1c7 = 2;
        func_0203c634(a, a->f20, 0);
    }
}
