extern void func_0201d0e0(void *p);
extern void func_0201e144(void *p, int a, int b);

struct S {
    char _0[0x110];
    int flags;
    char _114[0x150 - 0x114];
    int x150;
};

void func_0201d088(struct S *p, int a)
{
    if (((p->flags << 30) >> 31) == 0) {
        func_0201d0e0(p);
        return;
    }
    if (a == 0) {
        func_0201d0e0(p);
        return;
    }
    func_0201e144((char *)p + 0xe8, 0, a);
    p->flags |= 8;
    p->x150 = 0;
}
