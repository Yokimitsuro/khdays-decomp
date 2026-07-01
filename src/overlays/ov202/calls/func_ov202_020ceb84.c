extern int func_0203bc78();

struct S11 { int a[11]; };

struct Src {
    char pad[0x30];
    struct S11 d;       /* 0x30 */
};

struct Mid {
    char pad[0x384];
    struct Src *q;      /* 0x384 -> pointer to Src */
};

struct Outer {
    char pad0[0x30];
    struct S11 dst;     /* 0x30 .. 0x5b */
    char pad1[0x84 - 0x5c];
    struct Mid **p;     /* 0x84 */
};

void func_ov202_020ceb84(struct Outer *self, int arg1)
{
    self->dst = self->p[0]->q->d;
    *(int *)((char *)self + 0x4c) = 0xa00;
    *(int *)((char *)self + 0x50) = 0xa00;
    *(int *)((char *)self + 0x54) = 0xa00;
    func_0203bc78(self, arg1);
}
