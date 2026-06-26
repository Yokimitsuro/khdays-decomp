int func_020326a8(int r0, int r1)
{
    int *p;
    if (r1 < 0)
        return r0;
    p = (int *)(r0 + 0x7c + r1 * 0x8c);
    return *p |= 2;
}
