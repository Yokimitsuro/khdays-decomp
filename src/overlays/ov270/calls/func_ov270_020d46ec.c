extern int func_02023eb4();
extern int func_0203c634();

struct sub {
    int *f0;
    int *f4;
    char gap8[0x2c];
    int f34;
};

struct top {
    char gap0[4];
    struct sub *f4;
    char gap8[0x18];
    signed char b20;
};

void func_ov270_020d46ec(struct top *a) {
    struct sub *s = a->f4;
    int *p;
    int lo, hi, diff;

    if (*(unsigned char *)((char *)s->f4 + 0xad) != 0)
        return;

    p = s->f0;
    lo = p[0x224 / 4];
    hi = p[0x228 / 4];
    diff = hi - lo;
    if (diff < 0)
        diff = -diff;
    diff = diff + 1;
    s->f34 = lo + func_02023eb4(diff);

    *(unsigned char *)((char *)s->f0 + 0x1c7) = 2;

    func_0203c634(a, a->b20, 0);
}
