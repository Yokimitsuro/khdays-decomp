struct S { int a; int b; };

void func_02009024(struct S *p)
{
    volatile struct S local;
    p->a = 0;
    local.a = 0;
    local.b = 0;
    p->b = 0;
}
