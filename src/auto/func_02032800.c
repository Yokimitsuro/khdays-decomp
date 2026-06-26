int *func_02032800(int *r0, int r1, int r2)
{
    if (r1 < 0)
        return r0;
    r0 = (int *)((char *)r0 + r1 * 0x8c);
    r0[0x1c] = r2 & 0xf;
    return r0;
}
