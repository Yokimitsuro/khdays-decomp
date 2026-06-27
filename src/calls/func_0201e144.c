extern int func_0201e16c(void *p);

struct S {
    int x0;
    int x4;
    int x8;
    int xc;
};

void func_0201e144(struct S *p, int a, int b)
{
    p->x0 = func_0201e16c(p);
    p->x4 = a;
    p->xc = b;
    p->x8 = 0;
}
