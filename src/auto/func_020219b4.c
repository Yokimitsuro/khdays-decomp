int *func_020219b4(int *r0, int r1)
{
    int idx = r0[0x49];
    int *p = (int *)((char *)r0 + idx * 0x48);
    p[8] = r1;
    return p;
}
