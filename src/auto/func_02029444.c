void func_02029444(int *p)
{
    int v = p[0x38 / 4];
    p[0xc / 4] = p[0x2c / 4] - v;
    p[0x10 / 4] = p[0x34 / 4] - v;
    p[0x14 / 4] = p[0x2c / 4] + v;
    p[0x18 / 4] = p[0x34 / 4] + v;
}
