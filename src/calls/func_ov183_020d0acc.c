extern int FX_Inv();
extern int func_02023eb4();
extern int func_0203c634();

void func_ov183_020d0acc(int *s)
{
    int *a = (int *)s[0];
    int *b = (int *)s[1];
    int r, d, lo, hi;
    int *c;

    *(int *)((char *)b + 0x1c) = *(int *)((char *)b + 0x1c) + *(int *)((char *)a + 0x2c);
    r = FX_Inv(*(int *)((char *)b + 0x1c), 0x555);
    if (r > 0x1000)
        r = 0x1000;
    *(int *)((char *)b[0] + 0x394) = r;

    if (*(unsigned char *)(*(int *)((char *)b + 0xc)) != 0)
        return;

    c = (int *)b[0];
    lo = *(int *)((char *)c + 0x224);
    hi = *(int *)((char *)c + 0x228);
    d = hi - lo;
    if (d < 0)
        d = -d;
    d = d + 1;
    *(int *)((char *)b + 0x74) = lo + func_02023eb4(d);

    *(signed char *)((char *)b[0] + 0x1c7) = 2;
    func_0203c634(s, *(signed char *)((char *)s + 0x20), 0);
}
