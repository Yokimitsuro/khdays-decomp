extern int *func_ov107_020cab14();
extern int func_01ff8a7c();
extern void func_0203c634();

void func_ov141_020cce98(int *a)
{
    int local;
    int *b;
    int *c;
    int *r7;
    int x;

    b = (int *)a[1];
    r7 = func_ov107_020cab14(((int **)b)[0], &local);
    b[1] = (int)r7;
    if (r7 == 0)
        return;

    c = ((int **)b)[0];
    x = func_01ff8a7c(local);
    local = x - (c[0x20] + r7[0x20]);
    if (local > ((int **)b)[0][0xb6])
        return;

    b[0xd] = b[0xd] - ((int *)a[0])[0xb];
    if (b[0xd] >= 0)
        return;

    *((char *)((int **)b)[0] + 0x1c7) = 4;
    func_0203c634(a, *(signed char *)((char *)a + 0x20), 0);
}
