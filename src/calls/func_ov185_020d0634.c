extern int func_02023eb4();
extern int func_0203c634();

struct B {
    int *p0;                /* 0x00 */
    char pad04[0x40 - 0x04];
    int f40;                /* 0x40 */
    char pad44[0x48 - 0x44];
    unsigned char *p48;     /* 0x48 */
};

struct A {
    char f0[4];
    struct B *f4;           /* 0x04 */
    char pad8[0x20 - 8];
    signed char f20;        /* 0x20 */
};

void func_ov185_020d0634(struct A *a) {
    struct B *b = a->f4;
    int lo, hi, d;
    if (*b->p48 != 0) {
        return;
    }
    lo = b->p0[0x224 / 4];
    hi = b->p0[0x228 / 4];
    d = hi - lo;
    if (d < 0) {
        d = -d;
    }
    b->f40 = lo + func_02023eb4(d + 1);
    *((unsigned char *)b->p0 + 0x1c7) = 2;
    func_0203c634(a, a->f20, 0);
}
