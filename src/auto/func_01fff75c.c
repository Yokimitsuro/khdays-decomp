int func_01fff75c(unsigned short *r0, int r1)
{
    if (*r0 & 4)
        return ((int *)r0)[0xd4 / 4];
    return ((int *)((char *)r0 + (r1 << 2)))[0xc / 4];
}
