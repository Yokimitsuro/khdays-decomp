extern void func_0201231c(void *p, int a);
extern void func_02011e74(void *p);
extern void func_02012480(void *p, int b);

struct S {
    char _0[0x34];
    int x34;
    int x38;
};

void func_02012444(struct S *p, int b, int c)
{
    p->x34 = c;
    p->x38 = -1;
    func_0201231c((char *)p + 0x3c, 1);
    func_02011e74(p);
    func_02012480(p, b);
}
